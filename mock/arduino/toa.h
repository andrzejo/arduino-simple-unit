#ifndef TEST_MOCK_TOA_H
#define TEST_MOCK_TOA_H

#include <cstdint>

class NtoA {
public:
    static std::string longToString(long value, uint8_t base);
    static std::string doubleToString(double value, uint8_t precision);
};


extern char *itoa(int value, char *buffer, int base);

extern char *utoa(unsigned int value, char *buffer, int base);

extern char *ltoa(long value, char *buffer, int base);

extern char *ultoa(unsigned long value, char *buffer, int base);

extern char *dtostrf(double val, int8_t char_num, uint8_t precision, char *chr_buffer);

#endif //TEST_MOCK_TOA_H
