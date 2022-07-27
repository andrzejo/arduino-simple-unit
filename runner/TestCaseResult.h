#ifndef TEST_RUNNER_TESTCASERESULT_H
#define TEST_RUNNER_TESTCASERESULT_H

#include <list>
#include <string>
#include <map>
#include <fstream>
#include <iostream>

#include "rapidjson/prettywriter.h"
#include "TestCase.h"
#include "Utils.h"

namespace asu {

    using namespace rapidjson;
    using namespace std;

    class TestCaseResult {
    public:
        TestCaseResult(string testCase, string exec) {
            TestCaseResult::testCase = testCase;
            unsigned long index = exec.find_last_of('/');
            TestCaseResult::exec = exec.substr(index + 1);
        }

        typedef struct TestDefinition {
            string testName;
            bool disabled;
            bool success;
            int assertions;
            int failedAssertions;
            list<TestCase::AssertionFailedData> testResult;
            list<string> testMessages;
            list<string> testArtifacts;
        };

    protected:
        string testCase = "";
        string exec = "";
        int skipped = 0;
        int success = 0;
        int failed = 0;
        int lastAssertionsCount = 0;
        int lastFailedAssertionsCount = 0;
        long duration = 0;
        list<TestDefinition> tests = {};

        void writeInt(PrettyWriter<StringBuffer> &writer, const string label, const int value) {
            writer.String(label.c_str(), label.length());
            writer.Int(value);
        }

        void writeString(PrettyWriter<StringBuffer> &writer, const string label, const string &value) {
            writer.String(label.c_str(), label.length());
            writer.String(value.c_str(), value.length());
        }

        void writeBool(PrettyWriter<StringBuffer> &writer, const string label, const bool &value) {
            writer.String(label.c_str(), label.length());
            writer.Bool(value);
        }

        void writeList(PrettyWriter<StringBuffer> &writer, const string label, const list<string> &value) {
            writer.String(label.c_str(), label.length());
            writer.StartArray();
            for (auto s: value) {
                writer.String(s.c_str(), s.length());
            }
            writer.EndArray();
        }

        void writeTestDefinition(PrettyWriter<StringBuffer> &writer, TestDefinition t) {
            writer.StartObject();
            writeString(writer, "name", t.testName);
            writeBool(writer, "success", t.success);
            writeBool(writer, "disabled", t.disabled);
            writeInt(writer, "assertions", t.assertions);
            writeInt(writer, "failedAssertions", t.failedAssertions);
            writeList(writer, "messages", t.testMessages);
            writeList(writer, "artifacts", t.testArtifacts);
            writer.String("failed");
            writer.StartArray();
            for (auto f: t.testResult) {
                writer.StartObject();
                writeString(writer, "expected", f.expected);
                writeString(writer, "actual", f.actual);
                writeString(writer, "message", f.message);
                writeString(writer, "file", f.file);
                writeInt(writer, "line", f.line);
                writer.EndObject();
            }
            writer.EndArray();
            writer.EndObject();
        }

        string reportPath() {
            string testCaseName = std::regex_replace(exec, std::regex("_exe"), "");
            string reportPath = Utils::workingPath() + "/asu-reports";
            Utils::createDir(reportPath);
            return reportPath + "/" + testCaseName + ".json";
        }

    public:
        void onTestFinish(bool success) {
            if (success) {
                TestCaseResult::success++;
            } else {
                TestCaseResult::failed++;
            }
        }

        int getSuccess() {
            return success;
        }

        int getFailed() const {
            return failed;
        }

        int getSkipped() const {
            return skipped;
        }

        void addTest(TestCase &aCase, const TestCase::TestDefinition &definition, bool b) {
            if (definition.disabled) {
                skipped++;
            }
            TestDefinition t = {
                    definition.testName,
                    definition.disabled,
                    b,
                    aCase.getAssertionCounter() - lastAssertionsCount,
                    aCase.getFailedAssertionCounter() - lastFailedAssertionsCount,
                    aCase.getTestResult(definition.testName),
                    aCase.getTestMessages(definition.testName),
                    aCase.getTestArtifacts(definition.testName)
            };
            tests.push_back(t);
            lastAssertionsCount = aCase.getAssertionCounter();
            lastFailedAssertionsCount = aCase.getFailedAssertionCounter();
        }

        void setDuration(long duration) {
            TestCaseResult::duration = duration;
        }

        void save() {
            StringBuffer sb;
            PrettyWriter<StringBuffer> writer(sb);

            writer.StartObject();
            writeString(writer, "testCase", testCase);
            writeString(writer, "exec", exec);
            writeBool(writer, "result", failed == 0);
            writeInt(writer, "success", success);
            writeInt(writer, "failed", failed);
            writeInt(writer, "skipped", skipped);
            writeInt(writer, "duration", duration);
            writer.String("tests");
            writer.StartArray();
            for (auto t: tests) {
                writeTestDefinition(writer, t);
            }
            writer.EndArray();
            writer.EndObject();

            ofstream out(reportPath().c_str());
            out << sb.GetString();
            out.close();
        }
    };
}

#endif //TEST_RUNNER_TESTCASERESULT_H


