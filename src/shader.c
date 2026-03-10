#include "../inc/shader.h"

unsigned int create_shader(const char *file, GLenum type) {
  unsigned int ID;
  FILE *fp = fopen(file, "rb");
  if (!fp) {
    fprintf(stderr, "failed to open shader source file\n");
    exit(1);
  }

  fseek(fp, 0, SEEK_END);
  size_t fsize = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  char *source;
  source = (char*)malloc(sizeof(char) * fsize);
  if (!source) {
    fclose(fp);
    fprintf(stderr, "shader source buffer alloc failed\n");
    exit(1);
  }

  fread(source, fsize, sizeof(char), fp);

  source = (char*)realloc(source, (fsize + 1) * sizeof(char));
  source[fsize] = '\0';

  fclose(fp);

  ID = glCreateShader(type);
  glShaderSource(ID, 1, (const GLchar * const *)&source, NULL);
  glCompileShader(ID);
  print_errors(ID, GL_COMPILE_STATUS);

  free(source);

  return ID;
}

unsigned int create_program(unsigned int *shaders, unsigned int n) {
  unsigned int ID = glCreateProgram();
  for (int i = 0; i<n; i++) {
    glAttachShader(ID, shaders[i]);
  }
  glLinkProgram(ID);
  print_errors(ID, GL_LINK_STATUS);

  for (int i = 0; i<n; i++) {
    glDeleteShader(shaders[i]);
  }

  return ID;
}

void print_errors(unsigned int ID, GLenum info) {
  int success;
  char infolog[1024];
  if (info == GL_COMPILE_STATUS) {
    glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(ID, 1024, NULL, infolog);
      printf("%s\n", infolog);
      exit(1);
    }
  } else if (info == GL_LINK_STATUS) {
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(ID, 1024, NULL, infolog);
      printf("%s\n", infolog);
      exit(1);
    }
  }
}
