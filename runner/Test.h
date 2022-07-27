#ifndef TEST_RUNNER_TEST_H
#define TEST_RUNNER_TEST_H

#include <string>
#include <list>
#include <iostream>
#include <regex>
#include "TestCase.h"

namespace asu {

    using namespace std;

    class Test {
    public:
        Test(list<TestCase::TestDefinition> &list, const string &testName,
             TestCase::TestMethod method, bool disabled = false) {
             list.push_back({
                                   testName: testName,
                                   method: method,
                                   disabled: disabled
                           });
        }
    };

}
#endif //TEST_RUNNER_TEST_H
