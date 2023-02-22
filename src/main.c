#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>    // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include "util/getFileContents.h"

/*
 * 3-dimensional points are defined in the X, Y, Z pattern.
 * 2-dimensional points are defined in the X, Y pattern.
 *
 *     0.5f, -0.5f, 0.0f  ->  /\
 *                           /  \
 *                          /    \
 *  0.0f,  0.5f, 0.0f  ->  /______\  <-  -0.5f, -0.5f, 0.0f
 */
float *createPoints()
{
  static float points[] = {
      0.0f, 0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      -0.5f, -0.5f, 0.0f};

  return points;
}

GLFWAPI GLFWwindow *startGlfwAndCreateWindow(int x, int y)
{
  if (!glfwInit())
  {
    fprintf(stderr, "ERROR: could not start GLFW3\n");
    return NULL;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

  const GLubyte *renderer = glGetString(GL_RENDERER);
  const GLubyte *version = glGetString(GL_VERSION);
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);

  return window;
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
  glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

  /* _____________________________Create vertex array object___________________________ */
  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

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

  GLuint vs = glCreateShader(GL_VERTEX_SHADER); // glCreateShader returns an ID
  glShaderSource(vs, 1, &vertex_shader, NULL);
  glCompileShader(vs);
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragment_shader, NULL);
  glCompileShader(fs);

  GLuint shader_programme = glCreateProgram();
  glAttachShader(shader_programme, fs);
  glAttachShader(shader_programme, vs);
  glLinkProgram(shader_programme);

  while (!glfwWindowShouldClose(window))
  {
    // wipe the drawing surface clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader_programme);
    glBindVertexArray(vao);
    // draw points 0-3 from the currently bound VAO with current in-use shader
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // update other events like input handling
    glfwPollEvents();
    // put the stuff we've been drawing onto the display
    glfwSwapBuffers(window);
  }

  // close GL context and any other GLFW resources
  free((char *)vertex_shader);
  free((char *)fragment_shader);
  glfwTerminate();
  return 0;
}
