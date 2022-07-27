#ifndef TEST_MOCK_ARDUINO_SIMPLE_UNIT_H
#define TEST_MOCK_ARDUINO_SIMPLE_UNIT_H

#ifdef TESTING_ASU

#define TESTABLE(class_name) \
private: \
    friend class class_name##Test; \
    friend class class_name##TestAccess; \

#else

#define TESTABLE(class_name)

#endif

#endif //TEST_MOCK_ARDUINO_SIMPLE_UNIT_H
