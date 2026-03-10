#include "../inc/vector.h"

struct vec4 vector_add(struct vec4 v1, struct vec4 v2) {
  __m128 v1f = (__m128){v1.x, v1.y, v1.z, v1.w};
  __m128 v2f = (__m128){v2.x, v2.y, v2.z, v1.w};
  __m128 result = _mm_add_ps(v1f, v2f);
  float new[4];
  _mm_storeu_ps(&new[0], result);
  return (struct vec4){ .x = new[0], .y = new[1], .z = new[2], .w = new[3] };
}

struct vec4 vector_sub(struct vec4 v1, struct vec4 v2) {
  __m128 v1f = (__m128){v1.x, v1.y, v1.z, v1.w};
  __m128 v2f = (__m128){v2.x, v2.y, v2.z, v2.w};
  __m128 result = _mm_sub_ps(v1f, v2f);
  float new[4];
  _mm_storeu_ps(&new[0], result);
  return (struct vec4){ .x = new[0], .y = new[1], .z = new[2], .w = new[3] };
}

struct vec4 vector_mul(struct vec4 v1, struct vec4 v2) {
  __m128 v1f = (__m128){v1.x, v1.y, v1.z, v1.w};
  __m128 v2f = (__m128){v2.x, v2.y, v2.z, v2.w};
  __m128 result = _mm_mul_ps(v1f, v2f);
  float new[4];
  _mm_storeu_ps(&new[0], result);
  return (struct vec4){ .x = new[0], .y = new[1], .z = new[2], .w = new[3] };
}

struct vec4 vector_div(struct vec4 v1, struct vec4 v2) {
  __m128 v1f = (__m128){v1.x, v1.y, v1.z, v1.w};
  __m128 v2f = (__m128){v2.x, v2.y, v2.z, v2.w};
  __m128 result = _mm_div_ps(v1f, v2f);
  float new[4];
  _mm_storeu_ps(&new[0], result);
  return (struct vec4){ .x = new[0], .y = new[1], .z = new[2], .w = new[3] };
}

void vector_print(struct vec4 v1) {
  printf("{ %f, %f, %f, %f }\n", v1.x, v1.y, v1.z, v1.w);
}
