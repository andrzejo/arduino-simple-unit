#include "ColorFormatter.h"
#include <regex>
#include <utility>

namespace asu {

    const map<string, int> ColorFormatter::colorCodes = {
            {"black",   30},
            {"red",     31},
            {"green",   32},
            {"yellow",  33},
            {"blue",    34},
            {"magenta", 35},
            {"cyan",    36},
            {"white",   36},
            {"reset",   39},
    };

    string ColorFormatter::format(const string &format, map<string, string> &args, string defaultColor) {
        const int defaultCode = colorCodes.count(defaultColor) > 0 ? colorCodes.at(defaultColor) : -1;
        string result = defaultCode > 0 ? codeToAnsi(defaultCode) + format : format;

        for (const auto &arg: args) {
            result = regex_replace(result, regex("\\{" + arg.first + "\\}"), arg.second);
        }

        for (const auto &color: colorCodes) {
            result = replaceColor(result, color.first, color.second);
        }

        const string &resetToColor = defaultCode > 0 ? codeToAnsi(defaultCode) : codeToAnsi(resetColor);
        result = regex_replace(result, regex("</\\w*>"), resetToColor);

        if (defaultCode > 0) {
            return result + codeToAnsi(resetColor);
        } else {
            return result;
        }
    }

    string ColorFormatter::codeToAnsi(int colorCode) {
        return "\033[" + to_string(colorCode) + "m";
    }

    string ColorFormatter::replaceColor(const string &text, const string &colorName, int colorCode) {
        return regex_replace(text, regex("<" + colorName + ">"), codeToAnsi(colorCode));
    }

    ColorFormatter ColorFormatter::forMessage(const string &message) {
        return ColorFormatter(message);
    }

    ColorFormatter ColorFormatter::arg(const string &name, const string &value) {
        args.insert(pair<string, string>(name, value));
        return *this;
    }

    ColorFormatter ColorFormatter::arg(const string &name, int value) {
        arg(name, to_string(value));
        return *this;
    }

    string ColorFormatter::format() {
        return format(message, args, defaultColorName);
    }

    ColorFormatter::ColorFormatter(string message) : message(std::move(message)) {
    }

    ColorFormatter ColorFormatter::defaultColor(const string &color) {
        defaultColorName = color;
        return *this;
    }

}