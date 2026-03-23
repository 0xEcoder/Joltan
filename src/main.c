#include <GL/glew.h>    // must be first
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/mats.h"
#include "include/render.h"

int main(void)
{
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Pyramid Demo", NULL, NULL);
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

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Compute aspect ratio from actual framebuffer size
        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        float aspect = (h > 0) ? (float)w / (float)h : 1.0f;

        render_draw(aspect);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
