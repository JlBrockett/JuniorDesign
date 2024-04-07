#include "Arduino.h"
#include "customDigtial.h"

int customDigital::customDigitalRead(int pin) {
  if (pin >= 0 && pin <= 7) { // PORTD: Digital pins 0 to 7
    return (PIND & (1 << pin)) ? HIGH : LOW;
  }
  else if (pin >= 8 && pin <= 13) { // PORTB: Digital pins 8 to 13
    return (PINB & (1 << (pin - 8))) ? HIGH : LOW;
  }
  else if (pin >= 14 && pin <= 19) { // PORTC: Analog pins A0 (14) to A5 (19) as digital
    return (PINC & (1 << (pin - 14))) ? HIGH : LOW;
  }
  return -1; // Return -1 if the pin number is out of range
}

void customDigital::customDigitalWrite(int pin, int val) {
  if (pin >= 0 && pin <= 7) { // PORTD: Digital pins 0 to 7
    if (val == HIGH) {
      PORTD |= (1 << pin); // Set pin high
    } else {
      PORTD &= ~(1 << pin); // Set pin low
    }
  } else if (pin >= 8 && pin <= 13) { // PORTB: Digital pins 8 to 13
    if (val == HIGH) {
      PORTB |= (1 << (pin - 8)); // Set pin high
    } else {
      PORTB &= ~(1 << (pin - 8)); // Set pin low
    }
  } else if (pin >= 14 && pin <= 19) { // PORTC: Analog pins A0 (14) to A5 (19) as digital
    if (val == HIGH) {
      PORTC |= (1 << (pin - 14)); // Set pin high
    } else {
      PORTC &= ~(1 << (pin - 14)); // Set pin low
    }
  }
}