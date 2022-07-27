#ifndef TEST_MOCK_HARDWARESERIAL_H
#define TEST_MOCK_HARDWARESERIAL_H

#include "HardwareSerialMockState.h"

class HardwareSerial {
private:
    HardwareSerialMockState &mock;
public:
    HardwareSerial() : mock(HardwareSerialMockState::instance()) {}

    void begin(uint8_t baud) {

    }

    int available() {
        return mock.available();
    }

    char read() {
        return mock.read();
    }

};

#endif //TEST_MOCK_HARDWARESERIAL_H
