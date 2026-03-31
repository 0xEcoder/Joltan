#ifndef RENDER_H
#define RENDER_H

void render_init(void);
void render_draw(float aspect);

GLuint shader;
GLuint VAO, VBO;
GLuint MVP_loc;

#endif
