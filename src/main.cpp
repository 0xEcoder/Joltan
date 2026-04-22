#if defined(_WIN32) || defined(_WIN64)
    #include "external/win32/include/GL/glew.h"
    #include "external/win32/include/GLFW/glfw3.h"
#elif defined(__APPLE__) || defined(__MACH__)
    // macOS
#elif defined(__linux__)
    // Linux
#endif
#include "external/universal/glm/glm/glm.hpp"
#include "external/universal/glm/glm/gtc/matrix_transform.hpp"
#include "external/universal/glm/glm/gtc/type_ptr.hpp"
#include <iostream>

#include "include/render.hpp"
#include "include/shapes.hpp"
#include "include/GameObject.hpp"
#include "include/parseshader.hpp"

#define TITLE "Joltan ALPHA 0.01"

int main(void) {
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(1280, 720, TITLE, NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW init failed\n" << std::endl;
        return -1;
    }

    glViewport(0, 0, 1280, 720);

    render_init();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    float pyramidVerts[] = {
        // Front
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,

        // Right
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, -0.5f,

        // Back
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        // Left
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,

        // Base (2 triangles)
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
    };
    float planeVerts[] = {
        // first triangle
        -0.5f, 0.0f, -0.5f,
         0.5f, 0.0f, -0.5f,
         0.5f, 0.0f,  0.5f,

        // second triangle
        -0.5f, 0.0f, -0.5f,
         0.5f, 0.0f,  0.5f,
        -0.5f, 0.0f,  0.5f
    };

    init_pyramid(pyramidVerts, sizeof(pyramidVerts));
    init_plane2D(planeVerts, sizeof(planeVerts));
    GameObject Pyramid;
    GameObject Plane2D;
    Plane2D.position.y = -1.0f;
    Pyramid.position.z = -2.0f;
    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Compute aspect ratio from actual framebuffer size
        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        float aspect = (h > 0) ? (float) w / (float) h : 1.0f;

        Pyramid.rotation.y += 0.01f;

        render_draw(aspect, Pyramid.getModelMatrix());
        pyramid();
        


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
