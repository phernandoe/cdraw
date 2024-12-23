#include "shader.h"

GLuint createVertexShader(char *filePath)
{
  const char *source = getFileContents(filePath);
  if (source == NULL)
  {
    return 1;
  }

  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &source, NULL);
  glCompileShader(vs);
  return vs;
}
GLuint createFragmentShader(char *filePath)
{
  const char *source = getFileContents(filePath);
  if (source == NULL)
  {
    return 1;
  }

  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &source, NULL);
  glCompileShader(fs);
  return fs;
}

GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader)
{
  GLuint p = glCreateProgram();
  glAttachShader(p, fragmentShader);
  glAttachShader(p, vertexShader);
  glLinkProgram(p);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  return p;
}

GLuint compileShaderFromPath(char *vertexShaderFilePath, char *fragmentShaderFilePath)
{
  GLuint vs = createVertexShader(vertexShaderFilePath);
  GLuint fs = createFragmentShader(fragmentShaderFilePath);
  return createShaderProgram(vs, fs);
}
