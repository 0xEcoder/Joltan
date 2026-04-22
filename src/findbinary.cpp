#include "include/findbinary.hpp"

#include <string>
#include <stdexcept>

#if defined(_WIN32)
    #include <windows.h>

#elif defined(__linux__)
    #include <unistd.h>
    #include <limits.h>

#elif defined(__APPLE__)
    #include <mach-o/dyld.h>
    #include <limits.h>
#endif


// -----------------------------
// Get full executable path
// -----------------------------
static std::string getExecutablePath()
{
#if defined(_WIN32)

    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    return std::string(buffer);

#elif defined(__linux__)

    char buffer[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buffer, PATH_MAX);

    if (len == -1)
        throw std::runtime_error("Failed to read /proc/self/exe");

    return std::string(buffer, len);

#elif defined(__APPLE__)

    char buffer[PATH_MAX];
    uint32_t size = sizeof(buffer);

    if (_NSGetExecutablePath(buffer, &size) != 0)
        throw std::runtime_error("Buffer too small for executable path");

    return std::string(buffer);

#else
    throw std::runtime_error("Unsupported platform");
#endif
}


// -----------------------------
// Get binary directory only
// -----------------------------
std::string getBinaryDir()
{
    std::string fullPath = getExecutablePath();

    size_t pos = fullPath.find_last_of("\\/");
    if (pos == std::string::npos)
        return "";

    return fullPath.substr(0, pos);
}