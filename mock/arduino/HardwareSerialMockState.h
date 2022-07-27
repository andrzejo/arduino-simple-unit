#ifndef MOTO_SENS_HARDWARESERIALMOCKSTATE_H
#define MOTO_SENS_HARDWARESERIALMOCKSTATE_H

class HardwareSerialMockState {
private:
    const char *buff;
    int size;
    int index;
public:
    void setStream(const char *streamBuff, int streamSize);

    static HardwareSerialMockState & instance();

    char read();

    int available() const;
};

#endif //MOTO_SENS_HARDWARESERIALMOCKSTATE_H
