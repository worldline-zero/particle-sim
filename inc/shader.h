#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <stdlib.h>

#include "../lib/include/glad/gl.h"

unsigned int create_shader(const char *file, GLenum type);

unsigned int create_program(unsigned int *shaders, unsigned int n);

void print_errors(unsigned int shader, GLenum info);

#endif
