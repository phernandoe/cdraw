#include "vbo.h"

struct VBO createVBO(){
  struct VBO self;
  glGenBuffers(1, &self.id);
  bindVBO(self);
  return self;
};

void bindVBO(struct VBO self){
  glBindBuffer(GL_ARRAY_BUFFER, self.id);
};
