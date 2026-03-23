#include <GL/glew.h>
#include <stdio.h>
#include "include/render.h"
#include "include/camera.h"

GLuint shader;
GLuint VAO, VBO;
GLuint MVP_loc;


void render_init(void)
{
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
        printf("Vertex shader compilation failed:\n%s\n", infoLog);
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

    // ----- Vertex data (pyramid) -----
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind (optional, good practice)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void render_draw(float aspect)   // added aspect parameter
{
    glUseProgram(shader);

    // ----- Build MVP matrix using mats.h -----
    float projection[16], view[16], model[16], mvp[16];

    // Perspective: fov = 45°, aspect = window width/height, near = 0.1, far = 100.0
    perspective(projection, 45.0f, aspect, 0.1f, 100.0f);

    // View: eye at (2,2,2) looking at origin, up = (0,1,0)
    float eye[]    = {2.0f, 2.0f, 2.0f};
    float center[] = {0.0f, 0.0f, 0.0f};
    float up[]     = {0.0f, 1.0f, 0.0f};
    lookAt(view, eye, center, up);

    // Model: identity (no extra transformation)
    identity(model);

    // MVP = projection * view * model   (OpenGL expects column-major)
    multiply(mvp, projection, view);
    multiply(mvp, mvp, model);

    glUniformMatrix4fv(MVP_loc, 1, GL_FALSE, mvp);

    // Draw the pyramid
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 18);   // 6 triangles × 3 vertices = 18

    // Unbind (optional)
    glBindVertexArray(0);
    glUseProgram(0);
}