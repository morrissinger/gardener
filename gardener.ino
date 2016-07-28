#include <Wire.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <string>
#include "PhProbe.h"
#include "EcProbe.h"
#include "Pump.h"
#include "Valve.h"

#define pHSensorRX 3
#define pHSensorTX 2

#define eCSensorRX 5
#define eCSensorTX 4

#define usSensorEcho 6
#define usSensorTrigger 7
#define height 32

#define pumpPin 10
#define valvePin 9

PhProbe pHSensor(pHSensorRX, pHSensorTX);
EcProbe eCSensor(eCSensorRX, eCSensorTX);
Pump drainPump(pumpPin);
Valve reservoirValve(valvePin);
LiquidCrystal lcd(0);

char computerdata[20];
byte received_from_computer=0;

void updateDisplay() {
  lcd.setCursor(0, 0);
  lcd.print("pH: ");
  lcd.setCursor(0,1);
  lcd.print("TDS: ");
  lcd.setCursor(0,2);
  lcd.print("cm: ");
  lcd.setCursor(0,3);
  lcd.print("Pump: ");
  lcd.setCursor(10,3);
  lcd.print("Valve: ");
  
  lcd.setCursor(4,0);
  lcd.print("6.5 (good)");
  
  lcd.setCursor(5,1);
  lcd.print("1000 ppm");
  
  lcd.setCursor(4,2);
  lcd.print("25 / 32");
  
  lcd.setCursor(6,3);
  lcd.print("off");
  
  lcd.setCursor(17,3);
  lcd.print("off");
}

void setup() {
  pinMode(pumpPin, OUTPUT);
  pinMode(valvePin, OUTPUT);
  Serial.begin(9600);
  pHSensor.begin(9600);
  eCSensor.begin(9600);
  lcd.begin(20, 4);
  lcd.setBacklight(HIGH);
}

void serialEventRun(void) {
  if (Serial.available()) serialEvent();
}

void serialEvent() {
  received_from_computer = Serial.readBytesUntil(13,computerdata,20);
  computerdata[received_from_computer]=0;
  
  String module = String(computerdata[0]) + String(computerdata[1]);
  String command = String(computerdata[2]) + String(computerdata[3]) + String(computerdata[4]) + String(computerdata[5]);
  String parameter = String(computerdata[6]);
  
  if (module == "PH") {
    pHSensor.command(command, parameter);
  } else if (module == "EC") {
    eCSensor.command(command, parameter);
  } else if (module == "PM") {
    drainPump.command(command, parameter);
  } else if (module == "VL") {
    reservoirValve.command(command, parameter);
  } else {
    Serial.println("ERMODU");
  }
}    

void loop(){
  if(pHSensor.available() > 0) {
    pHSensor.read();
  }  
  if(eCSensor.available() > 0) {
    eCSensor.read();
  }  
  updateDisplay();
}      




   


  

