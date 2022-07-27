#include <iostream>
#include <sstream>
#include <map>
#include <list>
#include <string>
#include <exception>
#include "runner/Test.h"
#include "runner/CallHandler.h"
#include "runner/TestCase.h"
#include "runner/TestRunner.h"
#include "runner/Printer.h"
#include "runner/ExceptionHandler.h"

namespace asu {

#define TESTING_ASU

#define TOKENIZE(x, y) x ## y
#define TOKENIZE_R(x, y) TOKENIZE(x, y)

#define METHOD_CALL(_methods_list) \
CallHandler TOKENIZE_R(_methods_list, __LINE__) = CallHandler(_methods_list, TOKENIZE_R(&__##_methods_list, __LINE__)); \
static void TOKENIZE_R(__##_methods_list, __LINE__)()

#define BEFORE_EACH METHOD_CALL(beforeEach)
#define AFTER_EACH METHOD_CALL(afterEach)
#define BEFORE_ALL METHOD_CALL(beforeAll)
#define AFTER_ALL METHOD_CALL(afterAll)

#define TEST(_name) \
    Test __##_name = Test(tests, #_name, &_name); \
    static void _name(TestCase &__testCase, const std::string &__testName)

#define DISABLED_TEST(_name) \
    Test __##_name = Test(tests, #_name, &_name, true); \
    static void _name(TestCase &__testCase, const std::string &__testName)

#define RUN_TESTS(className)                      \
int main(int argc, char** argv) {                 \
    std::set_terminate(ExceptionHandler::handle); \
    className __##className = className();        \
    std::string __##exec = std::string(argv[0]);                  \
    return TestRunner::run(__##className, #className, __##exec);  \
};

#define assertEqual(expected, actual) \
    assertEqualWithMessage(expected, actual, "")

#define assertEqualWithMessage(expected, actual, message) \
    {                                 \
    __testCase.incrementAssertionCounter();          \
    std::ostringstream __expOss;                     \
    std::ostringstream __actOss;                     \
    __expOss << (expected);                          \
    __actOss << (actual);               \
    std::string __expStr = __expOss.str();                                 \
    std::string __actStr = __actOss.str();                                 \
    if(__expStr != __actStr) {                      \
        __testCase.assertionFailed(__testName, __expStr, __actStr, std::string(message), __FILE__, __LINE__);   \
    } \
    }
}