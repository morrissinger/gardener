#ifndef VALVE_H
#define VALVE_H

#define byte uint8_t

class Valve {
  int pin;
  
  public:
    Valve(int);
    void command(String command, String parameter);
};

#endif
