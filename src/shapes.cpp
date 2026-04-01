#include <GL/glew.h>
#include "include/render.hpp"
#include "include/camera.hpp"
#include "include/shapes.hpp"

// TRIANGLES
void init_pyramid(float *verts, size_t size) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, verts, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
}

void draw_pyramid() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 18);
}
