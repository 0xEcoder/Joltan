//
// Created by Dashiell on 2026-04-01.
//


#ifndef JOLTAN_PARSESHADER_HPP
#define JOLTAN_PARSESHADER_HPP
#if defined(_WIN32) || defined(_WIN64)
    #include "external/win32/include/GL/glew.h"

#elif defined(__APPLE__) && defined(__MACH__)
    // macOS (you’ll probably want OpenGL headers like this)
  

#elif defined(__linux__)
    

#else
    #error "Unsupported platform"
#endif



std::string readshader(const std::string& filepath);

#endif //JOLTAN_PARSESHADER_HPP
