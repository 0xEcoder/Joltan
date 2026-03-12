#include "include/mats.h"
    const char *vertSrc =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
    "    gl_Position = vec4(aPos, 0.0, 1.0);\n"
    "}\n";

    const char *fragOrange =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "    FragColor = vec4(1.0, 0.5, 0.2, 1.0);\n"
    "}\n";