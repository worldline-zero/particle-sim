#include "../inc/window.h"
#include "../inc/vector.h"

extern struct vec4 cursor; // cba to make an extra vector type

struct vec4 cursor = (struct vec4)VEC4(0.0f, 0.0f, 0.0f, 0.0f);

int width, height;

static void framebuffer_size_callback(GLFWwindow *window, int w, int h) {
  glViewport(0, 0, w, h);
}

static void cursor_pos_callback(GLFWwindow *w, double xpos, double ypos) {
  printf("%f, %f\n", cursor.x, cursor.y);
  cursor.x = ((float)xpos/(float)width) * 2.0f - 1.0f;
  cursor.y = 1.0f - ((float)ypos/(float)height) * 2.0f;
}


void make_opengl_context() {
  if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
    fprintf(stderr, "failed to load OpenGL\n");
    exit(1);
  }
}

GLFWwindow *make_window(int w, int h, visible_t v) {

  if (v == INVISIBLE) {
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  }

  width = w, height = h;

  GLFWwindow *window = glfwCreateWindow(w, h, "", NULL, NULL);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  glfwSetCursorPosCallback(window, cursor_pos_callback);

  glfwMakeContextCurrent(window);

  return window;

}

void set_viewport(GLFWwindow *window, int w, int h) {
  glViewport(0, 0, w, h);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}
