#include "include/findbinary.hpp"

#include <stdexcept>

#if defined(_WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <unistd.h>
#include <limits.h>
#include <libgen.h>
#elif defined(__APPLE__)
#include <unistd.h>
#include <limits.h>
#include <libgen.h>
#include <mach-o/dyld.h>
#endif

std::string getBinaryDir() {
#if defined(_WIN32)
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    std::string fullPath(path);
    size_t pos = fullPath.find_last_of("\\/");
    return fullPath.substr(0, pos);

#elif defined(__linux__)
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    if (count == -1) throw std::runtime_error("Cannot get binary path");
    result[count] = '\0';
    return std::string(dirname(result));

#elif defined(__APPLE__)
    char path[PATH_MAX];
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) != 0)
        throw std::runtime_error("Buffer too small");

    return std::string(dirname(path));

#else
    throw std::runtime_error("Unsupported platform");
#endif
}