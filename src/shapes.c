#include <GL/glew.h>
#include "include/render.h"
#include "include/camera.h"
#include "include/shapes.h"

// TRIANGLES
void init_pyramid(float *verts, size_t size)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, verts, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void draw_pyramid()
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 18);
}
