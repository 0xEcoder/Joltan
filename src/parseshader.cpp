#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "include/parseshader.hpp"

#include "../../../../../Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/v1/iosfwd"
#include "../../../../../Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/v1/string"

std::string readshader(const std::string& filepath)
{
    std::ifstream file(filepath);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file: " << filepath << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();  // read entire file into buffer

    return buffer.str();     // return as string
}
