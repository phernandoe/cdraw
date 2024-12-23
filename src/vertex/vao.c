#include "vao.h"

void bindVAO(struct VAO self){
  glBindVertexArray(self.id);
};

struct VAO createVAO(){
  struct VAO self;
  glGenVertexArrays(1, &self.id);
  bindVAO(self);
  return self;
};

void setVertexAttributes(
    GLuint index,
    GLint size,
    GLsizei stride)
{
  glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, (void*)0);
};

void bindVBO(GLuint VBO){
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
};
