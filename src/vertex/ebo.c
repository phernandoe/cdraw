#include "ebo.h"

struct EBO createEBO(){
  struct EBO self;
  glGenBuffers(1, &self.id);
  bindEBO(self);
  return self;
};

void bindEBO(struct EBO self){
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self.id);
};
