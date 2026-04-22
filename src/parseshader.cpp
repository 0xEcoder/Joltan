#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#if defined(_WIN32) || defined(_WIN64)
    #include "external/win32/include/GL/glew.h"
    #include "external/win32/include/GLFW/glfw3.h"
#elif defined(__APPLE__) || defined(__MACH__)
    #include <GL/glew.h>
    #include <GLFW/glfw3.h>
#elif defined(__linux__)
    #include <GL/glew.h>
    #include <GLFW/glfw3.h>
#endif
#include "external/universal/glm/glm/glm.hpp"
#include "external/universal/glm/glm/gtc/matrix_transform.hpp"
#include "external/universal/glm/glm/gtc/type_ptr.hpp"

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
