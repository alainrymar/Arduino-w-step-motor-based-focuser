// Drive Stepper motor using A4988 stepper motor driver
// inspired from iknowvations.in
// Step motor control for Telescope manual focuser
// Arduino UNO based
// 4 Buttons, 1 joystick with central clic, OLED 128/32 I2c
// Alain Rymar
//*********************************************************


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// first define the pins
const int DirPin = 4;    // this pin defines direction CW or CCW
const int StepPin = 5;   // pulse this pin to move one step
const int Button1 = 8;  // Button 1 Slow Speed
const int Button2 = 9;  // Button 2 Medium Speed
const int Button3 = 10; // Button 3 Fast Speed
const int Button4 = 11; // Button 4 Very Slow Speed
const int JoyUp = 3;    // Joystick Up
const int JoyDown = 13; // Joystick Down
const int Sleep = 7;    // Motor Sleep, engage and dis-engage Motor. Allow Manual focus if dis-engaged
const int Clic = 12;    // Joystick Clic
// Define Variables
int SPR = 1600;    // Steps per revolution, Rotation Speed
int Speed;
int buttonState;        // ButtonState variable
int Motor;              // Motor engaged or not
String MotorSpeed = "";

void setup()
{
  // Make pins as Outputs
  pinMode(StepPin, OUTPUT);
  pinMode(DirPin, OUTPUT);
  pinMode(Button1, INPUT); //Speed 800 (steps per 360°)
  pinMode(Button2, INPUT); //Speed 1600
  pinMode(Button3, INPUT); //Speed 400
  pinMode(Button4, INPUT); //Speed 3200
  pinMode(JoyUp, INPUT);
  pinMode(JoyDown, INPUT);
  pinMode(A0,OUTPUT);      // MS1
  pinMode(A1,OUTPUT);      // MS2
  pinMode(A2,OUTPUT);      // MS3
  pinMode(Sleep, OUTPUT);  // Sleep motor drive pin control
  pinMode(Clic, INPUT);    // Jokstick Clic, engage and dis-engage motor
  //Set MSx port on a4988 to Slow: 1600 steps to 360 motor turn
  digitalWrite(A0,HIGH);  //Default retation 1600 step per 360°
  digitalWrite(A1,HIGH);
  digitalWrite(A2,LOW);
  digitalWrite(StepPin, LOW);
  digitalWrite(Sleep, LOW);  //Motor not engaged at boot
  Motor = 0;    //Motor not engaged

  //Setup OLED Screen
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(1000); // Pause for 2 seconds
  // Clear the buffer
  display.clearDisplay();
  display.display();
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Focuser Motor Control"));
  display.setCursor(17,20);
  display.println(F("Dev by Alain Rymar"));
  display.display();
  delay(1000);
  display.clearDisplay();
  display.display();
  display.setCursor(0,0);
  display.println(F("Focus speed: SLOW"));
  display.setCursor(0,15);
  display.println(F("Clic JoyStick to engage motors"));
  display.display();
  
}
// Program Loop
void loop()
{
Serial.begin(115200);
//Serial.println("Start Button Check");
buttonState = digitalRead(Button1);     // read Button 1
if (buttonState == 1){
//Serial.print("Button1: ");
//Serial.println(buttonState);
     Speed800();
     SPR=800;
     MotorSpeed = "MEDIUM";
     delay(500);
     display.clearDisplay();
     display.display();
     if (Motor == 0) {
      display.setCursor(0,10);
      display.println(F("Motor NOT Engaged"));
      }
     if (Motor == 1) {
      display.setCursor(0,10);
      display.println(F("Motor Engaged"));
     }
     display.setCursor(10,20);
     display.print(F("Speed: "));
     display.println(MotorSpeed);
     display.display();

}
buttonState = digitalRead(Button2);    // read Button 2
if (buttonState == 1){
//Serial.print("Button2: ");
//Serial.println(buttonState);
     Speed1600();
     SPR=1600;
     MotorSpeed = "SLOW";
     delay(500);
     display.clearDisplay();
     display.display();
     if (Motor == 0) {
      display.setCursor(0,10);
      display.println(F("Motor NOT Engaged"));
      }
     if (Motor == 1) {
      display.setCursor(0,10);
      display.println(F("Motor Engaged"));
     }
     display.setCursor(10,20);
     display.print(F("Speed: "));
     display.println(MotorSpeed);
     display.display();
}

buttonState = digitalRead(Button3);   // read Button 3
if (buttonState == 1){
//Serial.print("Button3: ");
//Serial.println(buttonState);
     Speed400();
     SPR=400;
     MotorSpeed = "FAST";
     delay(500);
     display.clearDisplay();
     display.display();
     if (Motor == 0) {
      display.setCursor(0,10);
      display.println(F("Motor NOT Engaged"));
      }
     if (Motor == 1) {
      display.setCursor(0,10);
      display.println(F("Motor Engaged"));
     }
     display.setCursor(10,20);
     display.print(F("Speed: "));
     display.println(MotorSpeed);
     display.display();
}

buttonState = digitalRead(Button4);   // read Button 4
if (buttonState == 1){
//Serial.print("Button4: ");
//Serial.println(buttonState);
     Speed3200();
     SPR=3200;
     MotorSpeed = "VERY SLOW";
     delay(500);
     display.clearDisplay();
     display.display();
     if (Motor == 0) {
      display.setCursor(0,10);
      display.println(F("Motor NOT Engaged"));
      }
     if (Motor == 1) {
      display.setCursor(0,10);
      display.println(F("Motor Engaged"));
     }
     display.setCursor(10,20);
     display.print(F("Speed: "));
     display.println(MotorSpeed);
     display.display();
}

buttonState = digitalRead(JoyUp);   // read JoyStick UP
if (buttonState == 1){
//Serial.print("JoyUp: ");
//Serial.println(buttonState);
FocusIn(SPR);        // Focus In
delay(10);
}

buttonState = digitalRead(JoyDown);  // read JoyStick Down
if (buttonState == 1){
//Serial.print("JoyDown: ");
//Serial.println(buttonState);
delay(10);
FocusOut(SPR);       // Focus Out
}

buttonState = digitalRead(Clic);  //engage motors or not on Joystick Clic
if (buttonState == 1){
  Serial.print("Clic: ");
  Serial.println(buttonState);
  delay(1000);
  if (Motor == 0){                //Check if Motor is engaged, 0 = Not engaged, 1 = Engaged
     Motor = 1;
     //Serial.print("Motor = ");
     //Serial.println(Motor);
     //delay(500);
     display.clearDisplay();
       if (SPR == 400) {MotorSpeed = "FAST";}
       if (SPR == 800) {MotorSpeed = "MEDIUM";}
       if (SPR == 1600) {MotorSpeed = "SLOW";}
       if (SPR == 3200) {MotorSpeed = "VERY SLOW";}
     display.setCursor(0,10);
     display.println(F("                       "));
     display.setCursor(10,25);
     display.println(F("                         "));
     display.display();
     display.setCursor(0,10);
     display.println(F("Motor Engaged"));
     display.setCursor(10,20);
     display.print(F("Speed: "));
     display.println(MotorSpeed);
     display.display();
     digitalWrite(Sleep, HIGH);   //Engage Step Motor
  }
else if (Motor == 1) {           //Check if Motor is engaged, 0 = Not engaged, 1 = Engaged
  Serial.print("Clic: ");
  Serial.println(buttonState);
  delay(1000);
  Motor = 0;
  //Serial.print("Motor = ");
  //Serial.println(Motor);
  //delay(500);
  display.clearDisplay();
       if (SPR == 400) {MotorSpeed = "FAST";}
       if (SPR == 800) {MotorSpeed = "MEDIUM";}
       if (SPR == 1600) {MotorSpeed = "SLOW";}
       if (SPR == 3200) {MotorSpeed = "VERY SLOW";}
     display.setCursor(0,10);
     display.println(F("                       "));
     display.setCursor(10,25);
     display.println(F("                         "));
     display.display();
     display.setCursor(0,10);
     display.println(F("Motor NOT Engaged"));
     display.setCursor(10,20);
     display.print(F("Speed: "));
     display.println(MotorSpeed);
     display.display();
  digitalWrite(Sleep, LOW);    // Disengage Step Motor
  }
//delay(250);
}    //end of Clic
}    // end of Loop

void FocusIn(int Speed){
    // rotate shaft clockwise
    digitalWrite(DirPin, HIGH);   // defines the direction to clockwise
    digitalWrite(StepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(StepPin, LOW);
    delayMicroseconds(1000);
    }

void FocusOut(int Speed){
  // Now rotate shaft counterclockwise
    digitalWrite(DirPin, LOW);
    digitalWrite(StepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(StepPin, LOW);
    delayMicroseconds(1000);
    }

void Speed200() {   //Speed 200
    //Set MSx port on a4988 (MS1/MS2/MS3) to H/L/L: 200 steps to 360 motor turn
  digitalWrite(A0,LOW);
  digitalWrite(A1,LOW);
  digitalWrite(A2,LOW);
}
void Speed400() {   //Speed 400
    //Set MSx port on a4988 (MS1/MS2/MS3) to L/H/L: 400 steps to 360 motor turn
  digitalWrite(A0,HIGH);
  digitalWrite(A1,LOW);
  digitalWrite(A2,LOW);
}
void Speed800() {   //Speed 800
    //Set MSx port on a4988 (MS1/MS2/MS3) to L/H/L: 800 steps to 360 motor turn
  digitalWrite(A0,LOW);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,LOW);
}
void Speed1600() {   //Speed 1600
    //Set MSx port on a4988 (MS1/MS2/MS3) to H/H/L: 1600 steps to 360 motor turn
  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,LOW);
}
void Speed3200() {   //Speed 3200
    //Set MSx port on a4988 (MS1/MS2/MS3) to H/H/H: 3200 steps to 360 motor turn
  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,HIGH);
}
