#include <iostream>
#include <fstream>
#include <sstream>

#include "include/parseshader.hpp"

Material load_material(const char* path)
{
    Material mat;

    std::ifstream file(path);
    std::string line;

    std::string vert, frag;

    while (std::getline(file, line))
    {
        if (line.find("shader_vert") != std::string::npos)
            vert = line.substr(line.find("=") + 2);

        if (line.find("shader_frag") != std::string::npos)
            frag = line.substr(line.find("=") + 2);
    }

    mat.shader = create_shader_program(vert.c_str(), frag.c_str());

    return mat;
}

