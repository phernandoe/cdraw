#include "log.h"

bool restart_gl_log()
{
  FILE *file = fopen(GL_LOG_FILE, "w");
  if (!file)
  {
    fprintf(stderr,
            "ERROR: could not open GL_LOG_FILE log file %s for writing\n",
            GL_LOG_FILE);
    return false;
  }
  time_t now = time(NULL);
  char *date = ctime(&now);
  fprintf(file, "GL_LOG_FILE log. local time %s\n", date);
  fclose(file);
  return true;
}

bool gl_log(const char *message, ...)
{
  va_list argptr;
  FILE *file = fopen(GL_LOG_FILE, "a");
  if (!file)
  {
    fprintf(
        stderr,
        "ERROR: could not open GL_LOG_FILE %s file for appending\n",
        GL_LOG_FILE);
    return false;
  }
  va_start(argptr, message);
  vfprintf(file, message, argptr);
  va_end(argptr);
  fclose(file);
  return true;
}

bool gl_log_err(const char *message, ...)
{
  va_list argptr;
  FILE *file = fopen(GL_LOG_FILE, "a");
  if (!file)
  {
    fprintf(stderr,
            "ERROR: could not open GL_LOG_FILE %s file for appending\n",
            GL_LOG_FILE);
    return false;
  }
  va_start(argptr, message);
  vfprintf(file, message, argptr);
  va_end(argptr);
  va_start(argptr, message);
  vfprintf(stderr, message, argptr);
  va_end(argptr);
  fclose(file);
  return true;
}

void log_gl_params() {
  GLenum params[] = {
    GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
    GL_MAX_CUBE_MAP_TEXTURE_SIZE,
    GL_MAX_DRAW_BUFFERS,
    GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
    GL_MAX_TEXTURE_IMAGE_UNITS,
    GL_MAX_TEXTURE_SIZE,
    GL_MAX_VARYING_FLOATS,
    GL_MAX_VERTEX_ATTRIBS,
    GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
    GL_MAX_VERTEX_UNIFORM_COMPONENTS,
    GL_MAX_VIEWPORT_DIMS,
    GL_STEREO,
  };
  const char* names[] = {
    "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
    "GL_MAX_CUBE_MAP_TEXTURE_SIZE",
    "GL_MAX_DRAW_BUFFERS",
    "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
    "GL_MAX_TEXTURE_IMAGE_UNITS",
    "GL_MAX_TEXTURE_SIZE",
    "GL_MAX_VARYING_FLOATS",
    "GL_MAX_VERTEX_ATTRIBS",
    "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
    "GL_MAX_VERTEX_UNIFORM_COMPONENTS",
    "GL_MAX_VIEWPORT_DIMS",
    "GL_STEREO",
  };
  gl_log("GL Context Params:\n");
  char msg[256];
  // integers - only works if the order is 0-10 integer return types
  for (int i = 0; i < 10; i++) {
    GLint v = 1;
    glGetIntegerv(params[i], &v); // this is giving the seg fault
    gl_log("%s %i\n", names[i], v);
  }
  // others
  GLint v[2];
  v[0] = v[1] = 0;
  glGetIntegerv(params[10], v);
  gl_log("%s %i %i\n", names[10], v[0], v[1]);

  GLboolean s = 0;
  glGetBooleanv(params[11], &s);
  gl_log("%s %u\n", names[11], (unsigned int)s);
  
  gl_log("-----------------------------\n");
}