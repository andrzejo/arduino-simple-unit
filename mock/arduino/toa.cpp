#include <cstdint>
#include <string>
#include <bitset>
#include <sstream>
#include <iomanip>
#include <regex>
#include "toa.h"

char *copy_str(const std::string &src, char *buff, int size) {
    unsigned long max = src.length() > (size * 8) ? (size * 8) : src.length();
    src.copy(buff, max);
    buff[max] = 0;
    return buff;
}

char *itoa(int value, char *buffer, int base) {
    std::string s = NtoA::longToString(value, base);
    return copy_str(s, buffer, sizeof(int));
}

char *utoa(unsigned int value, char *buffer, int base) {
    std::string s = NtoA::longToString(value, base);
    return copy_str(s, buffer, sizeof(unsigned int));
}

char *ltoa(long value, char *buffer, int base) {
    std::string s = NtoA::longToString(value, base);
    return copy_str(s, buffer, sizeof(long));
}

char *ultoa(unsigned long value, char *buffer, int base) {
    std::string s = NtoA::longToString(value, base);
    return copy_str(s, buffer, sizeof(unsigned long));
}

char *dtostrf(double val, int8_t char_num, uint8_t precision, char *chr_buffer) {
    const std::string &string = NtoA::doubleToString(val, precision);
    return copy_str(string, chr_buffer, sizeof(double));
}


std::string NtoA::longToString(long value, uint8_t base) {
    if (base == 2) {
        if (value == 0) {
            return "0";
        }
        const std::string &string = std::bitset<64>(value).to_string();
        return regex_replace(string, std::regex("^0+"), "");
    }
    std::stringstream stream;
    switch (base) {
        case 8:
            stream << std::oct;
            break;
        case 16:
            stream << std::hex;
            break;
        default:
            stream << std::dec;
    }
    stream << value;
    return stream.str();
}

std::string NtoA::doubleToString(double value, uint8_t precision) {
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(precision);
    stream << value;
    return stream.str();
}
