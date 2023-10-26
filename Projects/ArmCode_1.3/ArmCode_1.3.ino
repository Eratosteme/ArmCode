/*
------------------------- ArmCode_1.3 ----------------------------
Stronk code for Stronk robot ᕙ(⇀‸↼‶)ᕗ ᕙ(⇀‸↼‶)ᕗ ᕙ(⇀‸↼‶)ᕗ
Stronk team too !   you can be jealous 
*/

// step motor librry
#include <Stepper.h>

//graphical library to use da screen
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

// ------------- Stuf for da motor -------------------
const int stepsPerRevolution = 2038;  // change this to fit the number of steps per revolution
// for your motor
Stepper myStepper(stepsPerRevolution, 2, 13, 15, 12);
int stepCount = 0;         // number of steps the motor has taken
const int deceleration =5;
int speed = 10;
int speedActuelle=0;

// ------------- Stuf for da screen ------------------ (Sry Enzo if i wasn't realy going fast but being class is a necesssity (づ｡◕‿‿◕｡)づ)
// pinouts from https://github.com/Xinyuan-LilyGO/TTGO-T-Display
#define TFT_MOSI 19
#define TFT_SCLK 18
#define TFT_CS 5
#define TFT_DC 16
#define TFT_RST 23
#define TFT_BL 4
// constructor for data object named tft (spoiler : it's the screen )
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void setup() {
  // initialize the serial port:
  Serial.begin(9600);
  myStepper.setSpeed(10);
  pinMode(0, INPUT_PULLUP);
  pinMode(35, INPUT_PULLUP);
  Serial.print(F("Hello! ST77xx TFT Test"));
  pinMode(TFT_BL, OUTPUT);      // TTGO T-Display enable Backlight pin 4
  digitalWrite(TFT_BL, HIGH);   // T-Display turn on Backlight
  tft.init(135, 240);           // Initialize ST7789 240x135
  Serial.println(F("Initialized"));
  tft.fillScreen(ST77XX_BLACK);
}

void loop() {
  
  tftPrintTest();
  // step one step:
  while (stepCount < 10){
  myStepper.step(speed);
  Serial.print("steps:");
  Serial.println(stepCount);
  stepCount++;
  delay(500);}
  if (stepCount==10){readButtons();}

}

void readButtons(){
  if (digitalRead(0) == 0){
speedActuelle = speed;
tft.fillScreen(ST77XX_BLACK);
  }
  if (digitalRead(35) == 0){
speedActuelle = -speed;
tft.fillScreen(ST77XX_BLACK);
  }
  myStepper.step(speedActuelle);
  if(speedActuelle > 0){speedActuelle = speedActuelle - deceleration;}
  if(speedActuelle < 0){speedActuelle = speedActuelle + deceleration;}
  if((speedActuelle > 0) && (speedActuelle<deceleration)){speedActuelle = 0;}
  delay(500);
}
void tftPrintTest() {
  tft.setTextWrap(false);
  
  tft.setCursor(5, 40);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(3);
  tft.println("-(O_O)-");
  tft.println(" ");
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(1);
  tft.println("<- ClockWise");
  tft.setTextColor(ST77XX_GREEN);
  tft.println("CounterClockWise ->");
  tft.println(" ");
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(1);
  tft.println("Current Direction :");
  if((speedActuelle<1)&&(speedActuelle>-1)){tft.print(" --Aucune--");tft.println("Moteur à l'arrêt");}
  if(speedActuelle>0){tft.println(" Clockwise");tft.println(" ");tft.println("vitesse : ");tft.print(speedActuelle);}
  if(speedActuelle<0){tft.println(" Counter-Clockwise");tft.println(" ");tft.println("vitesse : ");tft.print(speedActuelle);}
  delay(0);
  
}
