#ifndef TEST_RUNNER_TESTRUNNER_H
#define TEST_RUNNER_TESTRUNNER_H

#include <algorithm>
#include <chrono>
#include "TestCase.h"
#include "Printer.h"
#include "TestCaseResult.h"

namespace asu {

    using namespace std;
    using namespace std::chrono;

    class TestRunner {
    private:
        static bool runTest(int testNumber, int testsCount, TestCase &test, const string &className,
                            const string &testName, TestCase::TestMethod method, bool disabled) {
            Printer::startTest(testNumber, testsCount, className, testName, disabled);
            if (disabled) {
                Printer::finishSkippedTest();
                return true;
            }
            test.startTest(testName);
            runSetupMethods(test.getBeforeEach());
            const int beforeTestAssertionsCount = test.getAssertionCounter();
            method(test, testName);
            const int testAssertionCount = test.getAssertionCounter() - beforeTestAssertionsCount;
            runSetupMethods(test.getAfterEach());
            const list<TestCase::AssertionFailedData> &list = test.getTestResult(testName);
            bool success = list.empty();
            Printer::finishTest(success, testAssertionCount);
            for (auto const &data : test.getTestMessages(testName)) {
                Printer::testMessage(testName, data);
            }
            for (auto const &data : list) {
                Printer::assertionFailed(data.expected, data.actual, data.message, data.file, data.line);
            }
            return success;
        }

        static void runSetupMethods(const list<TestCase::MethodCall> methods) {
            for (auto const &method : methods) {
                (*method)();
            }
        }

        static milliseconds now() {
            return duration_cast<milliseconds>(system_clock::now().time_since_epoch());
        }

    public:
        static int run(TestCase &test, string testCaseClass, string exec) {
            milliseconds ms = now();
            TestCaseResult result(testCaseClass, exec);
            int number = 1;
            runSetupMethods(test.getBeforeAll());
            const list<TestCase::TestDefinition> &tests = test.getTests();
            for (auto const &t : tests) {
                bool isSuccess = runTest(number, tests.size(), test, testCaseClass, t.testName, t.method, t.disabled);
                result.addTest(test, t, isSuccess);
                result.onTestFinish(isSuccess);
                number++;
            }
            runSetupMethods(test.getAfterAll());
            Printer::finish(result.getSuccess(), result.getFailed(), result.getSkipped(), test.getAssertionCounter(),
                            test.getFailedAssertionCounter());
            result.setDuration((now() - ms).count());
            result.save();
            return result.getFailed();
        }

    };
}
#endif //TEST_RUNNER_TESTRUNNER_H
