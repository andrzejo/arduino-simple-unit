#ifndef TEST_MOCK_SERIAL_H
#define TEST_MOCK_SERIAL_H

#include "stddef.h"
#include "WString.h"

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2

class SerialMock {
public:
    void begin(unsigned int rate = 0) {

    }

    size_t print(const String &) {};

    String readString() {};

    size_t available() {};

    size_t print(const char[]) {};

    size_t print(char) {};

    size_t print(unsigned char, int = DEC) {};

    size_t print(int, int = DEC) {};

    size_t print(unsigned int, int = DEC) {};

    size_t print(long, int = DEC) {};

    size_t print(unsigned long, int = DEC) {};

    size_t print(double, int = 2) {};

    size_t println(const String &s) {};

    size_t println(const char[]) {};

    size_t println(char) {};

    size_t println(unsigned char, int = DEC) {};

    size_t println(int, int = DEC) {};

    size_t println(unsigned int, int = DEC) {};

    size_t println(long, int = DEC) {};

    size_t println(unsigned long, int = DEC) {};

    size_t println(double, int = 2) {};

    size_t println() {};
};

extern SerialMock Serial;

#endif //TEST_MOCK_SERIAL_H
