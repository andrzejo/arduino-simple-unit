#include "unit_setup.h"

using namespace asu;

class TestCaseTest : public TestCase {
    static int counter;

    BEFORE_EACH {
        counter += 10;
    }

    BEFORE_ALL {
        counter += 20;
    }

    TEST(shoud_call_before) {
        assertEqual(30, counter)
    }

    AFTER_EACH {
        counter -= 1;
    };

    AFTER_ALL {
        counter -= 10;
    };
};

int TestCaseTest::counter = 0;

RUN_TESTS(TestCaseTest)