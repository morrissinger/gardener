#include<Arduino.h>
#include "PhProbe.h"

PhProbe::PhProbe(int r, int t) {
  rx = r;
  tx = t;
  received_from_sensor = 0;
  tempPH = 7.00;
  pH = 7.00;
}

void PhProbe::begin(int baud_rate) {
    sensor = new SoftwareSerial(rx, tx);
    sensor->begin(9600);
}

int PhProbe::available() {
  return sensor->available();
}

void PhProbe::read() {
   received_from_sensor = sensor->readBytesUntil(13, data, 20);
   data[received_from_sensor] = 0;
   Serial.println(data);

   tempPH = atof(data);
   if (tempPH > 0) {
     pH = tempPH;
   }
}

void PhProbe::command(String command, String parameter) {
  sensor->listen();

  if (command == "CALI") {
    if (parameter == "L") {
      sensor->print("Cal,low,4.00\r");
    } else if (parameter == "M") {
      sensor->print("Cal,mid,7.00\r");
    } else if (parameter == "H") {
      sensor->print("Cal,high,10.00\r");
    } else if (parameter == "?") {
      sensor->print("Cal,?\r");
    } else {
      Serial.println("ERPARA");
    }
  } else if (command == "LEDS") {
    if (parameter == "0") {
      sensor->print("L,0\r");
    } else if (parameter == "1") {
      sensor->print("L,1\r");
    } else {
      Serial.println("ERPARA");
    }
  } else if (command == "READ") {
    sensor->print("R,0\r");
  } else if (command == "MODE") {
    if (parameter == "0") {
      sensor->print("C,0\r");
    } else if (parameter == "1") {
      sensor->print("C,1\r");
    } else {
      Serial.println("ERPARA");
    }
  } else {
    Serial.println("ERCOMM");
  }    
}
