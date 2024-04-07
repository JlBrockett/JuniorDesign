#ifndef customDigital.h
#define customDigital_h
#include "Arduino.h"

class customDigital {
  public:
  static int customDigitalRead(int pin);
  static void customDigitalWrite(int pin, int val);
}


#endif