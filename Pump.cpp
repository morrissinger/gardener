#include<Arduino.h>
#include "Pump.h"

Pump::Pump(int p) {
  pin = p;
  pinMode(pin, OUTPUT);
}

void Pump::command(String command, String parameter) {
  if (command == "STRT") {
    digitalWrite(pin, HIGH);
    Serial.println("OK");
  } else if (command == "STOP") {
    digitalWrite(pin, LOW);
    Serial.println("OK");
  } else {
    Serial.println("ERCOMM");
  }    
}
