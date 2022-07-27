#ifndef MOTO_SENS_UTILS_H
#define MOTO_SENS_UTILS_H

#include <string>

class Utils {
public:
    static std::string workingPath();

    static std::string resourcePrefix();

    static void createDir(std::string path);
};


#endif //MOTO_SENS_UTILS_H
