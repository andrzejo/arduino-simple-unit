#ifndef TEST_MOCK_ARDUINO_H
#define TEST_MOCK_ARDUINO_H

#include <string>
#include <utility>
#include <cstdint>
#include "HardwareSerial.h"

#define PROGMEM

#include "Serial.h"
#include "pins_arduino.h"

#undef F
#define F(s) (s)
#define PSTR(s) (s)

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

#define CHANGE 1
#define FALLING 2
#define RISING 3

#define NOT_AN_INTERRUPT -1

#define digitalPinToInterrupt(p)  (p)

extern unsigned long millis();

extern void delay(unsigned long);

extern int digitalRead(uint8_t pin);

extern int analogRead(uint8_t pin);

extern void pinMode(uint8_t pin, uint8_t mode);

extern void attachInterrupt(uint8_t interruptNum, void (*userFunc)(), int mode);

typedef bool boolean;
typedef uint8_t byte;

extern HardwareSerial Serial1;
extern HardwareSerial Serial2;
extern HardwareSerial Serial3;

#endif //TEST_MOCK_ARDUINO_H
