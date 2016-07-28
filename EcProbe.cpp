#include<Arduino.h>
#include "EcProbe.h"

EcProbe::EcProbe(int r, int t) {
  rx = r;
  tx = t;
  received_from_sensor = 0;
  tempEC = 1000;
  ec = 1000;
}

void EcProbe::begin(int baud_rate) {
    sensor = new SoftwareSerial(rx, tx);
    sensor->begin(9600);
}

int EcProbe::available() {
  return sensor->available();
}

void EcProbe::read() {
   received_from_sensor = sensor->readBytesUntil(13, data, 48);
   data[received_from_sensor] = 0;
   Serial.println(data);

    tempEC = atof(strtok(data, ","));
    tempEC = atof(strtok(NULL, ","));

    if (tempEC > 0) {
      ec = (int)tempEC;
      Serial.println(ec);
    }
}

void EcProbe::command(String command, String parameter) {
  sensor->listen();

  if (command == "READ") {
    sensor->print("R,0\r");
  } else if (command == "MODE") {
    if (parameter == "0") {
      sensor->print("C,0\r");
    } else if (parameter == "1") {
      sensor->print("C,1\r");
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
  }  else if (command == "TYPE") {
    if (parameter == "0") {
      sensor->print("K,0.1");
    } else if (parameter == "1") {
      sensor->print("K,1.0");
    } else if (parameter == "2") {
      sensor->print("K,10.0");
    } else {
      Serial.println("ERPARA");
    }
  } else if (command == "CALI") {
    if (parameter == "D") {
      sensor->print("Cal,dry");
    } else if (parameter == "L") {
      sensor->print("Cal,low,84");
    } else if (parameter == "H") {
      sensor->print("Cal,high,1413");
    } else if (parameter == "?") {
      sensor->print("Cal,?");
    } else {
      Serial.println("ERPARA");
    }
  } else {
    Serial.println("ERCOMM");
  }  
}
