#include <Arduino.h>
#include "ArduinoMockState.h"

const uint16_t port_to_mode_PGM[] = {};
const uint16_t port_to_input_PGM[] = {};
const uint16_t port_to_output_PGM[] = {};

const uint8_t digital_pin_to_port_PGM[] = {};
const uint8_t digital_pin_to_bit_mask_PGM[] = {};
const uint8_t digital_pin_to_timer_PGM[] = {};

HardwareSerial Serial1;
HardwareSerial Serial2;
HardwareSerial Serial3;

unsigned long millis() {
    return ArduinoMockState::getMillis();
}

void delay(unsigned long delay) {
    ArduinoMockState::setDelay(delay);
}

int digitalRead(uint8_t pin) {
    return ArduinoMockState::getPinState(pin);
}

int analogRead(uint8_t pin) {
    return ArduinoMockState::getPinState(pin);
}

void pinMode(uint8_t pin, uint8_t mode) {
    ArduinoMockState::setPinMode(pin, mode);
}

void attachInterrupt(uint8_t interruptNum, void (*userFunc)(), int mode) {
    ArduinoMockState::attachInterrupt(interruptNum, userFunc, mode);
}