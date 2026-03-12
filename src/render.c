#include <GL/glew.h>
#include "include/render.h"
#include "include/mats.h"

GLuint shader;
GLuint VAO, VBO;

void render_init(void)
{
    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vertSrc, NULL);
    glCompileShader(vert);

    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fragOrange, NULL);
    glCompileShader(frag);

    shader = glCreateProgram();
    glAttachShader(shader, vert);
    glAttachShader(shader, frag);
    glLinkProgram(shader);

    glDeleteShader(vert);
    glDeleteShader(frag);

    float verts[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.0f,  0.5f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void render_draw(void)
{
    glUseProgram(shader);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}