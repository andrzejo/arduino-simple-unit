#ifndef TEST_RUNNER_TESTCASE_H
#define TEST_RUNNER_TESTCASE_H

#include <list>
#include <string>
#include <map>

namespace asu {

    using namespace std;

    class TestCase {
    public:
        typedef void (*TestMethod)(TestCase &, const string &);

        typedef void (*MethodCall)();

        typedef struct TestDefinition {
            string testName;
            TestMethod method;
            bool disabled;
        };

        typedef struct AssertionFailedData {
            string expected;
            string actual;
            string message;
            string file;
            int line;
        };

    protected:
        int assertionCounter = 0;
        int failedAssertionCounter = 0;
        list<TestDefinition> tests = {};
        list<MethodCall> beforeEach = {};
        list<MethodCall> afterEach = {};
        list<MethodCall> beforeAll = {};
        list<MethodCall> afterAll = {};
        map<string, list<AssertionFailedData>> testResult = {};
        map<string, list<string>> testMessages = {};
        map<string, list<string>> testArtifacts = {};

    public:
        int getAssertionCounter() const {
            return assertionCounter;
        }

        int getFailedAssertionCounter() const {
            return failedAssertionCounter;
        }

        const list<MethodCall> getBeforeEach() const {
            return beforeEach;
        }

        const list<MethodCall> &getAfterEach() const {
            return afterEach;
        }

        const list<MethodCall> &getBeforeAll() const {
            return beforeAll;
        }

        const list<MethodCall> &getAfterAll() const {
            return afterAll;
        }

        const list<TestDefinition> &getTests() const {
            return tests;
        }

        void startTest(const string &name) {
            testResult[name].clear();
        }

        void addTestMessage(const string &name, const string &message) {
            testMessages[name].push_back(message);
        }

        void addTestArtifact(const string &name, const string &path) {
            testArtifacts[name].push_back(path);
        }

        const list<AssertionFailedData> &getTestResult(const string &name) {
            return testResult[name];
        }

        const list<string> &getTestMessages(const string &name) {
            return testMessages[name];
        }

        const list<string> &getTestArtifacts(const string &name) {
            return testArtifacts[name];
        }

        void assertionFailed(const string &name, const string &expected, const string &actual, const string &message,
                             const char *file, int line) {
            failedAssertionCounter++;
            AssertionFailedData data{
                    expected: expected,
                    actual: actual,
                    message: message,
                    file: file,
                    line: line,
            };
            testResult[name].push_back(data);
        }

        void incrementAssertionCounter() {
            assertionCounter++;
        }
    };
}

#endif //TEST_RUNNER_TESTCASE_H
