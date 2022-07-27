#ifndef TEST_RUNNER_PRINTER_H
#define TEST_RUNNER_PRINTER_H

#include <string>
#include <ostream>

namespace asu {

    using namespace std;

    class Printer {
    public:
        static void startTest(int testNumber, int testsCount, const string &className, const string &testName,
                              bool disabled);

        static void finishTest(bool success, int testAssertionCount);

        static void assertionFailed(const string &expected, const string &actual, const string &msg, const string &file,
                                    int line);

        static void finish(int success, int failed, int skipped, int i, int i1);

        static void testMessage(const string &testName, const string &message);

        static void finishSkippedTest();
    };
}
#endif //TEST_RUNNER_PRINTER_H
