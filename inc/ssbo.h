#ifndef SSBO_H
#define SSBO_H

#include <stddef.h>

#include "../lib/include/glad/gl.h"

unsigned int create_ssbo(void *data, size_t bytes, unsigned int n, unsigned int binding_point);

void *get_ssbo_data(unsigned int ssbo);

#endif
