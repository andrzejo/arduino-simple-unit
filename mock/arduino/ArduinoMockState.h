#ifndef TEST_MOCK_ARDUINOMOCKSTATE_H
#define TEST_MOCK_ARDUINOMOCKSTATE_H

#include <string>
#include <iostream>
#include <list>
#include "stdint.h";

class MockException : public std::exception {
private:
    std::string msg;
public:
    const std::string &getMsg() const {
        return msg;
    }

    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        return msg.c_str();
    }

public:
    explicit MockException(std::string msg) : msg(std::move(msg)) {
    }
};

typedef struct InterruptDefinition {
    uint8_t pin;

    void (*func)();

    int mode;
};

class ArduinoMockState {
#define MAX_PINS 99
private:
    static int pinStates[MAX_PINS];
    static uint8_t pinModes[MAX_PINS];
    static unsigned long millis;
    static unsigned long delay;
    static std::list<InterruptDefinition> interrupts;

    static void validatePin(uint8_t pin);

public:
    static void setPinState(uint8_t pin, int state);

    static void resetPins();

    static int getPinState(uint8_t pin);

    static void setPinMode(uint8_t pin, uint8_t mode);

    static void attachInterrupt(uint8_t interruptNum, void (*userFunc)(), int mode);

    static void interrupt(uint8_t pin, int mode);

    static int getPinMode(uint8_t pin);

    static void setMillis(int mill);

    static unsigned long getMillis();

    static void setDelay(unsigned long delay);

    static unsigned long getDelay();
};


#endif //TEST_MOCK_ARDUINOMOCKSTATE_H
