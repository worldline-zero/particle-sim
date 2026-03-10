#include "../inc/ssbo.h"

unsigned int create_ssbo(void *data, size_t bytes, unsigned int n, unsigned int binding_point) {

  unsigned int ssbo;

  glGenBuffers(1, &ssbo);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
  glBufferData(GL_SHADER_STORAGE_BUFFER, bytes * n, data, GL_DYNAMIC_DRAW);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding_point, ssbo);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

  return ssbo;

}

void *get_ssbo_data(unsigned int ssbo) {

  glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
  void *ptr = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_WRITE);
  glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

  return ptr;

}
