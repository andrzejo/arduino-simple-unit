#ifndef TEST_RUNNER_CALLHANDLER_H
#define TEST_RUNNER_CALLHANDLER_H

#include <list>
#include "TestCase.h"

namespace asu {

    class CallHandler {
    public:
        CallHandler(std::list<TestCase::MethodCall> &methods, TestCase::MethodCall method) {
            methods.push_back(method);
        }
    };

}

#endif //TEST_RUNNER_CALLHANDLER_H
