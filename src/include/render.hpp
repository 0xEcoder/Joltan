#ifndef RENDER_H
#define RENDER_H

// Platform-specific includes
#if defined(_WIN32) || defined(_WIN64)
    #include "external/win32/include/GL/glew.h"

#elif defined(__APPLE__) && defined(__MACH__)
    // macOS (you’ll probably want OpenGL headers like this)
    #include <GL/glew.h>

#elif defined(__linux__)
    #include <GL/glew.h>

#else
    #error "Unsupported platform"
#endif

// Common includes
#include "../external/universal/glm/glm/glm.hpp"
#include "../external/universal/glm/glm/gtc/matrix_transform.hpp"
#include "../external/universal/glm/glm/gtc/type_ptr.hpp"

// Functions
void render_init(void);
void render_draw(float aspect, const glm::mat4& model);

// Globals
extern GLuint shader;
extern GLuint VAO, VBO;
extern GLuint MVP_loc;

#endif // RENDER_H