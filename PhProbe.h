#ifndef PHPROBE_H
#define PHPROBE_H

#include <SoftwareSerial.h>
#include <Wire.h>
#define byte uint8_t

class PhProbe {
  
  SoftwareSerial *sensor;
  byte received_from_sensor;
  char data[20];
  float tempPH;
  float pH;
  int rx;
  int tx;
  
  public:
    PhProbe(int, int);
    void begin(int);
    int available();
    void read();
    void command(String command, String parameter);
};

#endif
