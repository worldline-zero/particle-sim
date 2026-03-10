#ifndef PARTICLE_H
#define PARTICLE_H

#include <stdlib.h>

#include "../lib/include/glad/gl.h"
#include "../inc/vector.h"

#define PARTICLE(V1, V2) { .position = V1, .velocity = V2 }

struct particle {
  struct vec4 position;
  struct vec4 velocity;
};

void particle_vertex_data(unsigned int *vao, unsigned int *vbo);

void draw_particle(struct particle p, unsigned int vao, unsigned int program);

void draw_particles(unsigned int vao, unsigned int program, unsigned int count);

struct particle generate_particle();

#endif
