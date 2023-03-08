#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h> // GLFW helper library
#include "util/getFileContents.h"
#include "util/shader.h"
#include "vertex/vao.h"
#include "log/log.h"

void glfw_error_callback(int error, const char *description)
{
  gl_log_err("GLFW ERROR: code %i msg: %s\n", error, description);
}

/*
 * 3-dimensional points are defined in the X, Y, Z pattern.
 * 2-dimensional points are defined in the X, Y pattern.
 *
 *       0.0f, 0.5f, 0.0f   ->  /\
 *                             /  \
 *                            /    \
 *  -0.5f,  -0.5f, 0.0f  ->  /______\  <-  0.5f, -0.5f, 0.0f
 */
float *createPoints()
{
  // TODO: clean this function up, maybe create a utility for appending to array?
  static float sideA[] = {
      -0.5f, -0.5f, 0.0f,
      -0.5f, 0.5f, 0.0f,
      -0.25f, -0.5f, 0.0f,
      -0.25f, 0.5f, 0.0f,
      -0.5f, 0.5f, 0.0f,
      -0.25f, -0.5f, 0.0f};

  //  static float sideB[] = {
  //      -0.25f, 0.5f, 0.0f,
  //      -0.5f, 0.5f, 0.0f,
  //      -0.25f, -0.5f, 0.0f};

  //  memcpy(sideA, sideB, 9 * sizeof(float)); // floats are 4 bytes
  //  int i;
  //  for (i = 0; i < 18; i++) {
  //    char coordinate[] = {'X', 'Y', 'Z'};
  //    printf("(%d)%c: %f\n", i, coordinate[i % 3], sideA[i]);
  //  }
  return sideA;
}

GLFWAPI GLFWwindow *startGlfwAndCreateWindow(int x, int y)
{
  assert(restart_gl_log());
  // start GL context and O/S window using the GLFW helper library
  gl_log("starting GLFW\n%s\n", glfwGetVersionString());
  // register the error call-back function that we wrote, above
  glfwSetErrorCallback(glfw_error_callback);

  if (!glfwInit())
  {
    fprintf(stderr, "ERROR: could not start GLFW3\n");
    return NULL;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SAMPLES, 4); // anti-aliasing

  GLFWmonitor *mon = glfwGetPrimaryMonitor();
  GLFWwindow *window = glfwCreateWindow(x, y, "Hello Triangle", NULL, NULL);
  if (!window)
  {
    fprintf(stderr, "ERROR: could not open window with GLFW3\n");
    glfwTerminate();
    return NULL;
  }
  glfwMakeContextCurrent(window);

  // start GLEW extension handler
  glewExperimental = GL_TRUE;
  glewInit();
  log_gl_params();

  const GLubyte *renderer = glGetString(GL_RENDERER);
  const GLubyte *version = glGetString(GL_VERSION);
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);

  return window;
}

void updateFpsCounter(GLFWwindow *window, double previous_seconds)
{
  static int frame_count;
  double current_seconds = glfwGetTime();
  double elapsed_seconds = current_seconds - previous_seconds;
  if (elapsed_seconds > 0.25)
  {
    previous_seconds = current_seconds;
    double fps = (double)frame_count / elapsed_seconds;
    char tmp[128];
    sprintf(tmp, "opengl @ fps: %.2f", fps);
    glfwSetWindowTitle(window, tmp);
    frame_count = 0;
  }
  frame_count++;
}

bool is_valid(GLuint programId)
{
  glValidateProgram(programId);
  int params = -1;
  glGetProgramiv(programId, GL_VALIDATE_STATUS, &params);
  printf("program %i GL_VALIDATE_STATUS = %i\n", programId, params);
  if (GL_TRUE != params)
  {
    print_program_info_log(programId);
    return false;
  }
  return true;
}

int main()
{
  GLFWwindow *window = startGlfwAndCreateWindow(640, 480);
  if (!window)
  {
    return 1;
  }

  // tell GL to only draw onto a pixel if the shape is closer to the viewer
  glEnable(GL_DEPTH_TEST); // enable depth-testing
  glDepthFunc(GL_LESS);    // depth-testing interprets a smaller value as "closer"

  /* _____________________________Define triangle vertices_____________________________ */
  float *points = createPoints();

  /* _____________________________Create vertex buffer object__________________________ */
  GLuint vbo = 0;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 9 * 2 * sizeof(float), points, GL_STATIC_DRAW);

  /* _____________________________Create vertex array object___________________________ */
  struct VAO vao_a = createVAO();
  bindVBO(vbo);
  setVertexAttributes(0, 3, 0);

  struct VAO vao_b = createVAO();
  bindVBO(vbo);
  setVertexAttributes(0, 3, 0);

  /* _____________________________Create shaders_______________________________________ */
  const char *vertex_shader = getFileContents("src/shaders/vertex_shader.glsl");
  if (vertex_shader == NULL)
  {
    return 1;
  }

  const char *fragment_shader = getFileContents("src/shaders/fragment_shader.glsl");
  if (fragment_shader == NULL)
  {
    return 1;
  }

  /* _____________________________Create shader A_______________________________________ */

  GLuint vs_a = glCreateShader(GL_VERTEX_SHADER); // glCreateShader returns an ID
  glShaderSource(vs_a, 1, &vertex_shader, NULL);
  glCompileShader(vs_a);
  GLuint fs_a = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs_a, 1, &fragment_shader, NULL);
  glCompileShader(fs_a);
  if (checkShaderForErrors(fs_a))
  {
    return 1;
  };

  GLuint shader_programme_a = glCreateProgram();
  glAttachShader(shader_programme_a, fs_a);
  glAttachShader(shader_programme_a, vs_a);
  glLinkProgram(shader_programme_a);

  if (checkForLinkingErrors(shader_programme_a))
  {
    return 1;
  };

  GLint customColor = glGetUniformLocation(shader_programme_a, "inputColour");

  /* _____________________________Create shader B_______________________________________ */
  GLuint fs_b = createFragmentShader("src/shaders/fragment_shader_b.glsl");
  GLuint vs_b = createVertexShader("src/shaders/vertex_shader.glsl");
  GLuint shader_programme_b = createShaderProgram(vs_b ,fs_b);

  /* _____________________________Drawing loop_______________________________________ */
  double glfwStartTime = glfwGetTime();
  // TODO: separate rendering loop into its own function
  while (!glfwWindowShouldClose(window))
  {
    updateFpsCounter(window, glfwStartTime);
    // wipe the drawing surface clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader_programme_a);
    glUniform4f(customColor, 1.0f, 0.0f, 1.0f, 1.0f);
    bindVAO(vao_a);
    // draw points 0-3 from the currently bound VAO with current in-use shader
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(shader_programme_b);
    bindVAO(vao_b);
    glDrawArrays(GL_TRIANGLES, 3, 3);

    // update other events like input handling
    glfwPollEvents();
    // put the stuff we've been drawing onto the display
    glfwSwapBuffers(window);

    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
      glfwSetWindowShouldClose(window, 1);
    }
  }

  // close GL context and any other GLFW resources
  free((char *)vertex_shader);
  free((char *)fragment_shader);
  glfwTerminate();
  return 0;
}
