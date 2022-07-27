#include <ColorFormatter.h>
#include "unit_setup.h"

using namespace std;
using namespace asu;

class ColorFormatterTest : public TestCase {

    TEST(shoud_format_with_colors) {
        //given
        //language=html
        string format = "Some <blue>{text}</blue>, <yellow>{text}</yellow> with params: <red>{param}</red>.";
        map<string, string> args = {
                {"text",  "colored message"},
                {"param", "i'm param"}
        };

        //when
        const string &formatted = ColorFormatter::format(format, args);

        //then
        assertEqual("Some \033[34mcolored message\033[39m, \033[33mcolored message\033[39m with params: \033[31mi'm param\033[39m.", formatted);
    }

    TEST(shoud_handle_short_closing_tag) {
        //given
        //language=html
        string format = "Some <blue>{text}</>, <yellow>{text}</> with params: <red>{param}</>.";
        map<string, string> args = {
                {"text",  "colored message"},
                {"param", "i'm param"}
        };

        //when
        const string &formatted = ColorFormatter::format(format, args);

        //then
        assertEqual("Some \033[34mcolored message\033[39m, \033[33mcolored message\033[39m with params: \033[31mi'm param\033[39m.", formatted);
    }
};

RUN_TESTS(ColorFormatterTest)