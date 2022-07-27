#include <iostream>
#include "Printer.h"
#include "ColorFormatter.h"

namespace asu {

    void Printer::startTest(int testNumber, int testsCount, const string &className, const string &testName,
                            bool disabled) {
        cout.setf(ios::unitbuf);
        cerr.setf(ios::unitbuf);
        string message = "[<yellow>{no}</>/<yellow>{count}</>] {label} <blue>{class}::{name}</>... ";

        cout << ColorFormatter::forMessage(message)
                .arg("label", disabled ? "<yellow>Skipped test</>" : "Running test")
                .arg("class", className)
                .arg("name", testName)
                .arg("no", testNumber)
                .arg("count", testsCount)
                .format();
    }

    void Printer::finishTest(bool success, int testAssertionCount) {
        const string message = success ? "[<green>OK</>]" : "[<red>FAIL</>]";
        cout << ColorFormatter::forMessage(message).format();
        if (success && testAssertionCount == 0) {
            cout << ColorFormatter::forMessage(" <yellow>Warn</>: <cyan>This test did not perform any assertions!</>")
                    .format();
        }
        cout << endl;
    }

    void Printer::finishSkippedTest() {
        const string message = "[<yellow>SKIPPED</>]";
        cout << ColorFormatter::forMessage(message).format();
        cout << endl;
    }

    void Printer::finish(int success, int failed, int skipped, int totalAssertions, int failedAssertions) {
        string result = (failed == 0) ? "<green>SUCCESSFUL.</green>" : "<red>FAILED.</red>";

        string message = "Test case " + result +
                         " Stats: executed [<blue>{executed}</>], success [<green>{success}</>],"
                         " failed [<red>{failed}</>], skipped: [<yellow>{skipped}</>]."
                         " Assertions: total [<blue>{assertions_total}</>], failed [<red>{assertions_failed}</>].";

        cout << ColorFormatter::forMessage(message)
                .arg("executed", success + failed - skipped)
                .arg("success", success - skipped)
                .arg("failed", failed)
                .arg("skipped", skipped)
                .arg("assertions_total", totalAssertions)
                .arg("assertions_failed", failedAssertions)
                .format()
             << endl;
    }

    void Printer::assertionFailed(const string &expected, const string &actual, const string &msg, const string &file,
                                  int line) {
        const char *message = "Unit test assert that expected [<green>{expected}</>] == [<blue>{actual}</>]"
                              " failed at {file}:{line}";
        cout << ColorFormatter::forMessage(message)
                .defaultColor("red")
                .arg("expected", expected)
                .arg("actual", actual)
                .arg("file", file)
                .arg("line", line)
                .format()
             << endl;

        if (msg.length()) {
            cout << ColorFormatter::forMessage("<blue>{msg}</>")
                    .arg("msg", msg)
                    .format()
                 << endl;
        }
    }

    void Printer::testMessage(const string &testName, const string &message) {
        const char *msg = " ---> <blue>test message</>: <yellow>{msg}</>";
        cout << ColorFormatter::forMessage(msg)
                .arg("test", testName)
                .arg("msg", message)
                .format()
             << endl;
    }
}