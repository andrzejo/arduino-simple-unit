#include "unit_setup.h"
#include <DisplayImageExporter.h>
#include "mock/arduino/WString.h"

using namespace std;
using namespace asu;

class DisplayImageExporterTest : public TestCase {

    TEST(should_upscale_byte) {
        //given
        uint8_t input = 19; //10011
        DisplayImageExporter exporter;

        //when
        uint16_t output = exporter.upscaleByte(input);

        //then
        assertEqual("1100001111", String(output, 2).c_str())
    }

};

RUN_TESTS(DisplayImageExporterTest)