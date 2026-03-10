#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/include/glad/gl.h"

#include <GLFW/glfw3.h>

#include "../inc/shader.h"
#include "../inc/window.h"
#include "../inc/vector.h"
#include "../inc/ssbo.h"
#include "../inc/particle.h"

unsigned int TOTAL_PARTICLES = 10000;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

extern struct vec4 cursor;

int main(int argc, char **argv) {

  if (argc > 1) {
    TOTAL_PARTICLES = atoi(argv[1]);
    if (TOTAL_PARTICLES % 1000 != 0) {
      printf("Particle count must be multiple of 1000\n");
      return 0;
    }
  } else {
    printf("Usage: particle-sim <COUNT>\n");
    return 0;
  }

  printf("Tip: try clicking with your mouse to manipulate the particles!\n");

  if (!glfwInit()) {
    fprintf(stderr, "failed to initialise GLFW\n");
    exit(1);
  }

  if (argc > 1) {
    TOTAL_PARTICLES = atoi(argv[1]);
  }

  GLFWwindow *window = make_window(SCREEN_WIDTH, SCREEN_HEIGHT, VISIBLE);
  make_opengl_context();
  set_viewport(window, 800, 600);
  
  unsigned int basic_shaders[2] = {
    create_shader("./shader/vertex.glsl", GL_VERTEX_SHADER),
    create_shader("./shader/fragment.glsl", GL_FRAGMENT_SHADER)
  };

  unsigned int basic_program = create_program(basic_shaders, 2);

  unsigned int update_shader = create_shader("./shader/gravity.glsl", GL_COMPUTE_SHADER);
  unsigned int update_program = create_program(&update_shader, 1);
  
  struct particle *particles = (struct particle*)malloc(TOTAL_PARTICLES * sizeof(struct particle));
  if (!particles) {
    fprintf(stderr, "alloc fail: particles could not be allocated\n");
    exit(1);
  }

  memset(particles, 0x00, sizeof(struct particle) * TOTAL_PARTICLES);

  for (int i = 0; i<TOTAL_PARTICLES; i++) {
    particles[i] = generate_particle();
  }
  unsigned int particle_ssbo = create_ssbo((void*)particles, sizeof(struct particle), TOTAL_PARTICLES, 2);

  unsigned int p_vao, p_vbo;
  particle_vertex_data(&p_vao, &p_vbo);

  glUseProgram(update_program);
  glUniform1i(glGetUniformLocation(update_program, "n_particles"), TOTAL_PARTICLES);
  glUniform4fv(glGetUniformLocation(update_program, "cursor"), 1, (float*)&cursor);
  glUniform1f(glGetUniformLocation(update_program, "pressed"), 0.0f);
  glUseProgram(0);

  while (!glfwWindowShouldClose(window)) {

    glClearColor(8.0f/255.0f, 8.0f/255.0f, 8.0f/255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //for (int i = 0; i<TOTAL_PARTICLES; i++) {
    //  draw_particle(particles[i], p_vao, basic_program);
    //}

    draw_particles(p_vao, basic_program, TOTAL_PARTICLES);

    glUseProgram(update_program);
    glUniform4fv(glGetUniformLocation(update_program, "cursor"), 1, (float*)&cursor);
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
      glUniform1f(glGetUniformLocation(update_program, "pressed"), 1.0f);
    } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
      glUniform1f(glGetUniformLocation(update_program, "pressed"), -1.0f);
    } else {
      glUniform1f(glGetUniformLocation(update_program, "pressed"), 0.0f);
    }

    glDispatchCompute(TOTAL_PARTICLES/1000, 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

    particles = get_ssbo_data(particle_ssbo);

    volatile char c; 
    if (c == 'C') {
      exit(1);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();

  }

  free(particles);


  return 0;
}
