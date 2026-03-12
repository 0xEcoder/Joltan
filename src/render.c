#include <GL/glew.h>
#include "include/render.h"
#include "include/mats.h"

GLuint shader;
GLuint VAO, VBO;
GLuint MVP_loc;

void render_init(void)
{
    glEnable(GL_DEPTH_TEST);

    /* create shaders */
    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vertSrc, NULL);
    glCompileShader(vert);

    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fragOrange, NULL);
    glCompileShader(frag);

    /* create shader program */
    shader = glCreateProgram();
    glAttachShader(shader, vert);
    glAttachShader(shader, frag);
    glLinkProgram(shader);

    glDeleteShader(vert);
    glDeleteShader(frag);

    /* cache uniform location */
    MVP_loc = glGetUniformLocation(shader, "MVP");

    /* triangle vertices */
    float pyramidVerts[] = {
    // Base (two triangles)
   -0.5f, 0.0f, -0.5f,   0.5f, 0.0f, -0.5f,   0.5f, 0.0f, 0.5f,
   -0.5f, 0.0f, -0.5f,   0.5f, 0.0f, 0.5f,   -0.5f, 0.0f, 0.5f,

    // Side 1
   -0.5f, 0.0f, -0.5f,   0.5f, 0.0f, -0.5f,   0.0f, 0.8f, 0.0f,
    // Side 2
    0.5f, 0.0f, -0.5f,   0.5f, 0.0f, 0.5f,    0.0f, 0.8f, 0.0f,
    // Side 3
    0.5f, 0.0f, 0.5f,   -0.5f, 0.0f, 0.5f,    0.0f, 0.8f, 0.0f,
    // Side 4
   -0.5f, 0.0f, 0.5f,   -0.5f, 0.0f, -0.5f,   0.0f, 0.8f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidVerts), pyramidVerts, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void render_draw(void)
{
    glUseProgram(shader);

    float mvp[16] = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1
    };

    glUniformMatrix4fv(MVP_loc, 1, GL_FALSE, mvp);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 18);
}