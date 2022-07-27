#include <sys/param.h>
#include <sys/stat.h>
#include <unistd.h>
#include "Utils.h"

std::string Utils::workingPath() {
    char temp[MAXPATHLEN];
    return (getcwd(temp, sizeof(temp)) ? std::string(temp) : std::string(""));
}

std::string Utils::resourcePrefix() {
    const char *prefix = std::getenv("ASU_TEST_RESOURCE_PREFIX");
    return prefix ? std::string(prefix) : "";
}

void Utils::createDir(std::string path) {
    struct stat st = {0};
    if (stat(path.c_str(), &st) == -1) {
        mkdir(path.c_str(), 0700);
    }
}
