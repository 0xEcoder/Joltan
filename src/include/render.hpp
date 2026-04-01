#ifndef RENDER_H
#define RENDER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void render_init(void);
void render_draw(float aspect, const glm::mat4& model);

extern GLuint shader;
extern GLuint VAO, VBO;
extern GLuint MVP_loc;

#endif
