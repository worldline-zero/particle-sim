#include "../inc/particle.h"

void particle_vertex_data(unsigned int *vao, unsigned int *vbo) {
  //struct vec4 pos[3] = { (struct vec4)VEC4(0.0f, 0.0f, 0.0f, 1.0f), (struct vec4)VEC4(1.0f, 0.0f, 0.0f, 1.0f), (struct vec4)VEC4(0.0f, 1.0f, 0.0f, 1.0f) };
  struct vec4 pos = VEC4(0.0f, 0.0f, 0.0f, 1.0f);
  //float pos[] = {
  //  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f };
  glGenBuffers(1, vao);
  glGenBuffers(1, vbo);
  glBindVertexArray(*vao);
  glBindBuffer(GL_ARRAY_BUFFER, *vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(struct vec4), &pos, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(struct vec4), (void*)0);
  glBindVertexArray(0);
}

void draw_particle(struct particle p, unsigned int vao, unsigned int program) {
  glUseProgram(program);
  glUniform4fv(glGetUniformLocation(program, "p.position"), 1, (float*)&p.position);
  glUniform4fv(glGetUniformLocation(program, "p.velocity"), 1, (float*)&p.velocity);
  glBindVertexArray(vao);
  glDrawArrays(GL_POINTS, 0, 1);
  glBindVertexArray(0);
  glUseProgram(0);
}

struct particle generate_particle() {
  float random1 = (rand() % 1000) / 500.0f;
  float random2 = (rand() % 1000) / 500.0f;
  struct vec4 start = VEC4(-1.0f, -1.0f, 0.0f, 0.0f);
  struct vec4 offset = VEC4(random1, random2, 0.0f, 0.0f);
  struct particle p = PARTICLE(vector_add(start, offset), (struct vec4)VEC4((((rand() % 1000) / 500.0f) - 1.0f) * 0.0066, (((rand() % 1000) / 500.0f) - 1.0f) * 0.0066, 0.0f, 0.0f));
  return p;
}
