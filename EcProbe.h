#ifndef ECPROBE_H
#define ECPROBE_H

#include <SoftwareSerial.h>
#include <Wire.h>
#define byte uint8_t

class EcProbe {
  
  SoftwareSerial *sensor;
  byte received_from_sensor;
  char data[48];
  float tempEC;
  float ec;
  int rx;
  int tx;
  
  public:
    EcProbe(int, int);
    void begin(int);
    int available();
    void read();
    void command(String command, String parameter);
};

#endif
