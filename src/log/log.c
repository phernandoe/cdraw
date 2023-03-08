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

void log_gl_params()
{
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
  const char *names[] = {
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

  // integers - only works if the order is 0-10 integer return types
  for (int i = 0; i < 10; i++)
  {
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

int checkShaderForErrors(GLuint shaderId)
{
  // check for compile errors
  int params = -1;
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &params);
  if (GL_TRUE != params)
  {
    fprintf(stderr, "ERROR: GL shader index %i did not compile\n", shaderId);
    int max_length = 2048;
    int actual_length = 0;
    char shader_log[2048];
    glGetShaderInfoLog(shaderId, max_length, &actual_length, shader_log);
    printf("shader info log for GL index %u:\n%s\n", shaderId, shader_log);
    return 1;
  }
  return 0;
}

void print_program_info_log(GLuint programId)
{
  int max_length = 2048;
  int actual_length = 0;
  char program_log[2048];
  glGetProgramInfoLog(programId, max_length, &actual_length, program_log);
  printf("program info log for GL index %u:\n%s", programId, program_log);
}

int checkForLinkingErrors(GLuint shaderProgramId)
{
  // check if link was successful
  int params = -1;
  glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &params);
  if (GL_TRUE != params)
  {
    fprintf(stderr,
            "ERROR: could not link shader programme GL index %u\n",
            shaderProgramId);
    print_program_info_log(shaderProgramId);
    return 1;
  }
  return 0;
}

const char *GL_type_to_string(GLenum type)
{
  switch (type)
  {
  case GL_BOOL:
    return "bool";
  case GL_INT:
    return "int";
  case GL_FLOAT:
    return "float";
  case GL_FLOAT_VEC2:
    return "vec2";
  case GL_FLOAT_VEC3:
    return "vec3";
  case GL_FLOAT_VEC4:
    return "vec4";
  case GL_FLOAT_MAT2:
    return "mat2";
  case GL_FLOAT_MAT3:
    return "mat3";
  case GL_FLOAT_MAT4:
    return "mat4";
  case GL_SAMPLER_2D:
    return "sampler2D";
  case GL_SAMPLER_3D:
    return "sampler3D";
  case GL_SAMPLER_CUBE:
    return "samplerCube";
  case GL_SAMPLER_2D_SHADOW:
    return "sampler2DShadow";
  default:
    break;
  }
  return "other";
}

void print_all(GLuint programId)
{
  printf("--------------------\nshader programme %i info:\n", programId);
  int params = -1;
  glGetProgramiv(programId, GL_LINK_STATUS, &params);
  printf("GL_LINK_STATUS = %i\n", params);

  glGetProgramiv(programId, GL_ATTACHED_SHADERS, &params);
  printf("GL_ATTACHED_SHADERS = %i\n", params);

  glGetProgramiv(programId, GL_ACTIVE_ATTRIBUTES, &params);
  printf("GL_ACTIVE_ATTRIBUTES = %i\n", params);
  for (int i = 0; i < params; i++)
  {
    char name[64];
    int max_length = 64;
    int actual_length = 0;
    int size = 0;
    GLenum type;
    glGetActiveAttrib(
        programId,
        i,
        max_length,
        &actual_length,
        &size,
        &type,
        name);
    if (size > 1)
    {
      for (int j = 0; j < size; j++)
      {
        char long_name[64];
        sprintf(long_name, "%s[%i]", name, j);
        int location = glGetAttribLocation(programId, long_name);
        printf("  %i) type:%s name:%s location:%i\n",
               i, GL_type_to_string(type), long_name, location);
      }
    }
    else
    {
      int location = glGetAttribLocation(programId, name);
      printf("  %i) type:%s name:%s location:%i\n",
             i, GL_type_to_string(type), name, location);
    }
  }

  glGetProgramiv(programId, GL_ACTIVE_UNIFORMS, &params);
  printf("GL_ACTIVE_UNIFORMS = %i\n", params);
  for (int i = 0; i < params; i++)
  {
    char name[64];
    int max_length = 64;
    int actual_length = 0;
    int size = 0;
    GLenum type;
    glGetActiveUniform(
        programId,
        i,
        max_length,
        &actual_length,
        &size,
        &type,
        name);
    if (size > 1)
    {
      for (int j = 0; j < size; j++)
      {
        char long_name[64];
        sprintf(long_name, "%s[%i]", name, j);
        int location = glGetUniformLocation(programId, long_name);
        printf("  %i) type:%s name:%s location:%i\n",
               i, GL_type_to_string(type), long_name, location);
      }
    }
    else
    {
      int location = glGetUniformLocation(programId, name);
      printf("  %i) type:%s name:%s location:%i\n",
             i, GL_type_to_string(type), name, location);
    }
  }

  print_program_info_log(programId);
}