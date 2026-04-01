#include <GL/glew.h>    // must be first
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/camera.h"
#include "include/render.h"
#include "include/shapes.h"
#define TITLE "Joltan ALPHA 0.01"

int main(void)
{
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, TITLE, NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        printf("GLEW init failed\n");
        return -1;
    }

    glViewport(0, 0, 1280, 720);

    render_init();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    float pyramidVerts[] = {
        // Front
        0.0f,  0.5f,  0.0f,
       -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,

       // Right
        0.0f,  0.5f,  0.0f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f, -0.5f,

       // Back
        0.0f,  0.5f,  0.0f,
        0.5f, -0.5f, -0.5f,
       -0.5f, -0.5f, -0.5f,

       // Left
        0.0f,  0.5f,  0.0f,
       -0.5f, -0.5f, -0.5f,
       -0.5f, -0.5f,  0.5f,

       // Base (2 triangles)
       -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f, -0.5f,

       -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f, -0.5f,
       -0.5f, -0.5f, -0.5f,
   };

    init_pyramid(pyramidVerts, sizeof(pyramidVerts));
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Compute aspect ratio from actual framebuffer size
        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        float aspect = (h > 0) ? (float)w / (float)h : 1.0f;

        render_draw(aspect);

        draw_pyramid();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
