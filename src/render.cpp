#include <GL/glew.h>
#include <iostream>
#include "include/render.hpp"
#include "include/camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLuint shader;
GLuint VAO, VBO;
GLuint MVP_loc;


void render_init(void) {
    glEnable(GL_DEPTH_TEST);

    // ----- Vertex shader -----
    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vertSrc, NULL);
    glCompileShader(vert);

    GLint success;
    char infoLog[512];
    glGetShaderiv(vert, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vert, sizeof(infoLog), NULL, infoLog);
        std::cout << "Vertex shader compilation failed:\n%s\n" << infoLog << std::endl;
    }

    // ----- Fragment shader -----
    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fragOrange, NULL);
    glCompileShader(frag);

    glGetShaderiv(frag, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(frag, sizeof(infoLog), NULL, infoLog);
        printf("Fragment shader compilation failed:\n%s\n", infoLog);
    }

    // ----- Shader program -----
    shader = glCreateProgram();
    glAttachShader(shader, vert);
    glAttachShader(shader, frag);
    glLinkProgram(shader);

    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader, sizeof(infoLog), NULL, infoLog);
        printf("Shader linking failed:\n%s\n", infoLog);
    }

    glDeleteShader(vert);
    glDeleteShader(frag);

    // Cache uniform location and check
    MVP_loc = glGetUniformLocation(shader, "MVP");
    if (MVP_loc == -1) {
        printf("Warning: Uniform 'MVP' not found in shader.\n");
    }
}

void render_draw(float aspect, const glm::mat4& model)
{
    glUseProgram(shader);

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