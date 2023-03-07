#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdarg.h>
#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#define GL_LOG_FILE "gl.log"

bool restart_gl_log();
bool gl_log(const char* message, ...);
bool gl_log_err(const char* message, ...);
void log_gl_params();
void print_programme_info_log(GLuint programme);
int checkShaderForErrors(GLuint shaderId);
int checkForLinkingErrors(GLuint shaderId);
void print_all(GLuint programme);