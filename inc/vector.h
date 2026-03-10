#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <xmmintrin.h>

#define VEC4(X, Y, Z, W) { .x = X, .y = Y, .z = Z, .w = W }

struct vec4 {
  float x;
  float y;
  float z;
  float w;
};

struct vec4 vector_add(struct vec4 v1, struct vec4 v2);

struct vec4 vector_sub(struct vec4 v1, struct vec4 v2);

struct vec4 vector_mul(struct vec4 v1, struct vec4 v2);

struct vec4 vector_div(struct vec4 v1, struct vec4 v2);

void vector_print(struct vec4 v1);

#endif
