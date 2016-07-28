#include<Arduino.h>
#include "Valve.h"

Valve::Valve(int p) {
  pin = p;
  pinMode(pin, OUTPUT);
}

void Valve::command(String command, String parameter) {
  if (command == "OPEN") {
    digitalWrite(pin, HIGH);
    Serial.println("OK");
  } else if (command == "CLOS") {
    digitalWrite(pin, LOW);
    Serial.println("OK");
  } else {
    Serial.println("ERCOMM");
  }    
}
