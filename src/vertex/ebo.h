#include "vertex.h"
#ifndef EBO_H
#define EBO_H

struct EBO
{
  GLuint id;
};

struct EBO createEBO();

void bindEBO(struct EBO);

#endif
