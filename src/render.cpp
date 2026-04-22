#if defined(_WIN32) || defined(_WIN64)
    #include "external/win32/include/GL/glew.h"
#elif defined(__APPLE__) || defined(__MACH__)
    // macOS
#elif defined(__linux__)
    // Linux
#endif
#include "external/universal/glm/glm/glm.hpp"
#include "external/universal/glm/glm/gtc/matrix_transform.hpp"
#include "external/universal/glm/glm/gtc/type_ptr.hpp"
#include <iostream>
#include <string>

#include "include/render.hpp"
#include "include/parseshader.hpp"

#define BASE_FRAG_FILE "/shaders/fragments/base.frag"
#define BASE_VERT_FILE "/shaders/verts/base.vert"

// ----- Globals -----
GLuint shader;
GLuint VAO, VBO;
GLuint MVP_loc;

// Example vertex shader (make sure this exists somewhere)

// ----- Init -----
void render_init(void)
{
    glEnable(GL_DEPTH_TEST);
    std::string basefrag = getBinaryDir() + BASE_FRAG_FILE;
    std::string basevert = getBinaryDir() + BASE_VERT_FILE;
    // Load fragment shader from file
    std::string fragStr = readshader(basefrag);
    std::string vertStr = readshader(basevert);

    if (fragStr.empty())
    {
        std::cerr << "ERROR: Fragment shader file failed to load.\n";
        return;
    }
    if (vertStr.empty())
    {
        std::cerr << "ERROR: Fragment shader file failed to load.\n";
        return;
    }
    const char* fragSrc = fragStr.c_str();
    const char* vertSrc = vertStr.c_str();


    // ----- Vertex shader -----
    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vertSrc, NULL);
    glCompileShader(vert);

    GLint success;
    char infoLog[512];

    glGetShaderiv(vert, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vert, sizeof(infoLog), NULL, infoLog);
        std::cerr << "Vertex shader compilation failed:\n" << infoLog << std::endl;
    }

    // ----- Fragment shader -----
    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fragSrc, NULL);
    glCompileShader(frag);

    glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(frag, sizeof(infoLog), NULL, infoLog);
        std::cerr << "Fragment shader compilation failed:\n" << infoLog << std::endl;
    }

    // ----- Shader program -----
    shader = glCreateProgram();
    glAttachShader(shader, vert);
    glAttachShader(shader, frag);
    glLinkProgram(shader);

    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader, sizeof(infoLog), NULL, infoLog);
        std::cerr << "Shader linking failed:\n" << infoLog << std::endl;
    }

    // Cleanup
    glDeleteShader(vert);
    glDeleteShader(frag);

    // Get uniform location
    MVP_loc = glGetUniformLocation(shader, "MVP");
    if (MVP_loc == -1)
    {
        std::cerr << "Warning: Uniform 'MVP' not found.\n";
    }
}


// ----- Draw -----
void render_draw(float aspect, const glm::mat4& model)
{
    glUseProgram(shader);

    glm::vec3 objectColor(1.0f, 1.0f, 1.0f); // any color
    glm::vec3 lightPos(2.0f, 4.0f, 2.0f);
    glm::vec3 viewPos(2.0f, 2.0f, 2.0f);

    glUniform3fv(glGetUniformLocation(shader, "color"), 1, glm::value_ptr(objectColor));
    glUniform3fv(glGetUniformLocation(shader, "lightPos"), 1, glm::value_ptr(lightPos));
    glUniform3fv(glGetUniformLocation(shader, "viewPos"), 1, glm::value_ptr(viewPos));

    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        aspect,
        0.1f,
        100.0f
    );

    glm::mat4 view = glm::lookAt(
        glm::vec3(2.0f, 2.0f, 2.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    glm::mat4 mvp = projection * view * model;

    glUniformMatrix4fv(
        MVP_loc,
        1,
        GL_FALSE,
        glm::value_ptr(mvp)
    );
}