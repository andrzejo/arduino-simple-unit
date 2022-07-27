#include "ArduinoMockState.h"

int ArduinoMockState::pinStates[] = {};
uint8_t ArduinoMockState::pinModes[] = {};
unsigned long ArduinoMockState::millis = 0;
unsigned long ArduinoMockState::delay = 0;
std::list<InterruptDefinition> ArduinoMockState::interrupts = {};

void ArduinoMockState::validatePin(uint8_t pin) {
    if (pin < 0 || pin >= MAX_PINS) {
        throw MockException("Invalid pin number " + std::to_string(pin) + ".");
    }
}

void ArduinoMockState::setPinState(uint8_t pin, int state) {
    validatePin(pin);
    pinStates[pin] = state;
}

int ArduinoMockState::getPinState(uint8_t pin) {
    validatePin(pin);
    return pinStates[pin];
}

void ArduinoMockState::setPinMode(uint8_t pin, uint8_t mode) {
    validatePin(pin);
    pinModes[pin] = mode;
}

int ArduinoMockState::getPinMode(uint8_t pin) {
    validatePin(pin);
    return pinModes[pin];
}

void ArduinoMockState::attachInterrupt(uint8_t pin, void (*userFunc)(), int mode) {
    validatePin(pin);
    interrupts.push_back({pin, userFunc, mode});
}

void ArduinoMockState::resetPins() {
    for (auto &p: pinStates) {
        p = 0;
    }
}

void ArduinoMockState::setMillis(int millis) {
    ArduinoMockState::millis = millis;
}

unsigned long ArduinoMockState::getMillis() {
    return millis;
}

void ArduinoMockState::setDelay(unsigned long delay) {
    ArduinoMockState::delay = delay;
}

unsigned long ArduinoMockState::getDelay() {
    return delay;
}

void ArduinoMockState::interrupt(uint8_t pin, int mode) {
    for (auto &i: interrupts) {
        if (i.pin == pin && i.mode == mode) {
            i.func();
        }
    }
}
