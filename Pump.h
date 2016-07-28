#ifndef PUMP_H
#define PUMP_H

#define byte uint8_t

class Pump {
  int pin;
  
  public:
    Pump(int);
    void command(String command, String parameter);
};

#endif
