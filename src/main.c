#include <math.h>
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
  int gridMultiplier = 7;
  int squareSizeInPixels = 50;
  int gridDimensions = gridMultiplier * gridMultiplier;
  int squaresPerVertex = sqrt(gridDimensions);
  int numberOfSquares = gridDimensions;
  float squareSize = (float)squaresPerVertex / numberOfSquares;
  int totalSquares = numberOfSquares;

  int resolution = squareSizeInPixels * squaresPerVertex;
  GLFWwindow *window = startGlfwAndCreateWindow(resolution, resolution);
  if (!window) return 1;

  // tell GL to only draw onto a pixel if the shape is closer to the viewer
  glEnable(GL_DEPTH_TEST); // enable depth-testing
  glDepthFunc(GL_LESS);    // depth-testing interprets a smaller value as "closer"

  GLfloat vertices[] = {
      // positions                    // colors
      squareSize,  squareSize,  0.0f, 1.0f, 0.5f, 0.0f,
      squareSize,  -squareSize, 0.0f, 0.0f, 1.0f, 0.0f,
      -squareSize, -squareSize, 0.0f, 0.0f, 0.5f, 1.0f,
      -squareSize, squareSize,  0.0f, 1.0f, 1.0f, 0.0f
  };
  GLuint indices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };

  GLfloat translations[totalSquares * 3]; // 3 dimensions

  int counter = 0;
  int squareIndex = 0;
  printf("numberOfSquares: %i\n", numberOfSquares);
  printf("squaresPerVertex: %i\n", squaresPerVertex);
  printf("squareSize: %f\n", squareSize);

  float xGap = -1.0f - squareSize;

  for (int row = 0; row < squaresPerVertex; row++) {
    xGap+= squareSize * 2;
    float yGap = -1.0f - squareSize;
    for (int column = 0; column < squaresPerVertex; column++) {

        yGap+= squareSize * 2;

        printf("#%i translation[%i] = x: %f, y:%f\n", counter, squareIndex, xGap, yGap);

        translations[squareIndex] = xGap;
        translations[squareIndex + 1] = yGap;
        translations[squareIndex + 2] = 0.0f;

        squareIndex+=3;
        counter++;
    }
  }

  struct VAO vao = createVAO();

  /* _____________________________Create buffers ______________________________________ */
  GLuint instanceVbo = 0;
  glGenBuffers(1, &instanceVbo);
  bindVBO(instanceVbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(translations), translations, GL_STATIC_DRAW);

  GLuint vbo = 0;
  glGenBuffers(1, &vbo);
  bindVBO(vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  GLuint ebo = 0;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  setVertexAttributes(0, 3, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  setVertexAttributes(1, 3, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glEnableVertexAttribArray(2);
  bindVBO(instanceVbo);
  setVertexAttributes(2, 3, 3 * sizeof(float), (void*)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glVertexAttribDivisor(2, 1);

  /* _____________________________Create buffers (end) ________________________________ */

  GLuint shader = compileShaderFromPath(
      "src/shaders/grid.vert",
      "src/shaders/default.frag"
  );
  glUseProgram(shader);

  if (checkForLinkingErrors(shader)) return 1;

  /* _____________________________Drawing loop_______________________________________ */
  double glfwStartTime = glfwGetTime();
  while (!glfwWindowShouldClose(window))
  {
    updateFpsCounter(window, glfwStartTime);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    bindVAO(vao);
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, numberOfSquares);
    glBindVertexArray(0);

    glfwPollEvents();
    glfwSwapBuffers(window);

    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
      glfwSetWindowShouldClose(window, 1);
    }
  }

  glfwTerminate();
  return 0;
}
