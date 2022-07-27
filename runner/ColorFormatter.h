#ifndef TEST_RUNNER_COLORFORMATTER_H
#define TEST_RUNNER_COLORFORMATTER_H

#include <ostream>
#include <map>

namespace asu {
    using namespace std;

    class ColorFormatter {
    private:
        explicit ColorFormatter(string message);

        static const map<string, int> colorCodes;

        static const int resetColor = 39;

        map<string, string> args = {};
        const string message;

        string defaultColorName = "";

        static string codeToAnsi(int colorCode);

        static string replaceColor(const string &text, const string &colorName, int colorCode);

    public:
        static string format(const string &format, map<string, string> &args, string defaultColor = "");

        static ColorFormatter forMessage(const string &message);

        ColorFormatter arg(const string &name, const string &value);

        ColorFormatter arg(const string &name, int value);

        ColorFormatter defaultColor(const string &color);

        string format();
    };
}

#endif //TEST_RUNNER_COLORFORMATTER_H
