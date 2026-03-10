#ifndef WINDOW_H
#define WINDOW_H

#include <stdio.h>
#include <stdlib.h>

#include "../lib/include/glad/gl.h"

#include <GLFW/glfw3.h>

typedef enum {
  VISIBLE,
  INVISIBLE
} visible_t;

GLFWwindow *make_window(int w, int h, visible_t v);

void make_opengl_context();

void set_viewport(GLFWwindow *window, int w, int h);

#endif
