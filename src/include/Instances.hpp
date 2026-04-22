#ifndef JOLTAN_INSTANCES_HPP
#define JOLTAN_INSTANCES_HPP

#include "render.hpp"
#include "GameObject.hpp"

#include <vector>
#include <iostream>
#include <string>

#include "include/parseshader.hpp"
#include "include/findbinary.hpp"

#define BASE_FRAG_FILE "/shaders/fragments/base.frag"
#define BASE_VERT_FILE "/shaders/verts/base.vert"

#if defined(_WIN32) || defined(_WIN64)
    #include "../external/win32/include/GL/glew.h"
    #include "../external/win32/include/GLFW/glfw3.h"
#elif defined(__APPLE__) && defined(__MACH__)
    #include <GL/glew.h>
    #include <GLFW/glfw3.h>
#elif defined(__linux__)
    #include <GL/glew.h>
    #include <GLFW/glfw3.h>
#else
    #error "Unsupported platform"
#endif

struct Component {
    GameObject* owner = nullptr;

    virtual void init() {}
    virtual void update(float dt) {}
    virtual void render() {}

    virtual ~Component() = default;
};

struct MeshRender : Component
{
    std::vector<float> verts;

    GLuint shader = 0;
    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint MVP_loc = 0;

    GLFWwindow* window = nullptr;

    int w = 0, h = 0;
    float aspect = 1.0f;

    void init() override
    {
        // window size
        if (window)
        {
            glfwGetFramebufferSize(window, &w, &h);
            aspect = (h > 0) ? (float)w / (float)h : 1.0f;
        }

        glEnable(GL_DEPTH_TEST);

        // ===== SHADER LOAD =====
        std::string fragStr = readshader(getBinaryDir() + BASE_FRAG_FILE);
        std::string vertStr = readshader(getBinaryDir() + BASE_VERT_FILE);

        const char* fragSrc = fragStr.c_str();
        const char* vertSrc = vertStr.c_str();

        GLuint vert = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vert, 1, &vertSrc, NULL);
        glCompileShader(vert);

        GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(frag, 1, &fragSrc, NULL);
        glCompileShader(frag);

        shader = glCreateProgram();
        glAttachShader(shader, vert);
        glAttachShader(shader, frag);
        glLinkProgram(shader);

        glDeleteShader(vert);
        glDeleteShader(frag);

        MVP_loc = glGetUniformLocation(shader, "MVP");

        // ===== VAO / VBO (IMPORTANT FIX) =====
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,
            verts.size() * sizeof(float),
            verts.data(),
            GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
    }

    void update(float dt) override
    {
        // optional logic here
    }

    void render() override
    {
        glUseProgram(shader);

        glm::mat4 model = owner->getModelMatrix();

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

        glUniformMatrix4fv(MVP_loc, 1, GL_FALSE, glm::value_ptr(mvp));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, verts.size() / 3);
    }
};

#endif