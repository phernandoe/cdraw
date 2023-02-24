#include "vertex.h"
#ifndef VAO_H
#define VAO_H

struct VAO
{
  GLuint id;
};

void bindVAO(struct VAO);

struct VAO createVAO();

void setVertexAttributes(
  GLuint index,
  GLint size,
  GLsizei stride
);

void bindVBO(GLuint VBO);

#endif