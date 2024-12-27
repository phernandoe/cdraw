#include "vertex.h"
#ifndef VBO_H
#define VBO_H

struct VBO
{
  GLuint id;
};

struct VBO createVBO();

void bindVBO(struct VBO);

#endif
