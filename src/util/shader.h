#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "getFileContents.h"
#include "../log/log.h"

GLuint createVertexShader(char *filePath);
GLuint createFragmentShader(char *filePath);
GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader);
GLuint compileShaderFromPath(char *vertexShaderFilePath, char *fragmentShaderFilePath);
