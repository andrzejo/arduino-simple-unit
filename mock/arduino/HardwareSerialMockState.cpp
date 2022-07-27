#include "HardwareSerialMockState.h"

void HardwareSerialMockState::setStream(const char *streamBuff, int streamSize) {
    this->buff = streamBuff;
    this->size = streamSize;
    this->index = 0;
}

HardwareSerialMockState &HardwareSerialMockState::instance() {
    static HardwareSerialMockState inst;
    return inst;
}

char HardwareSerialMockState::read() {
    if (index >= size) {
        return 0;
    }
    return buff[index++];
}

int HardwareSerialMockState::available() const {
    return size - index;
}
