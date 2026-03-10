#version 430

#extension GL_ARB_gpu_shader_int64 : require

layout (local_size_x = 1000, local_size_y = 1, local_size_z = 1) in;
layout (rgba32f, binding = 0) uniform image2D image_out;

struct particle {
  vec4 position;
  vec4 velocity;
};

layout (std430, binding = 2) volatile buffer particle_buffer_in {
  particle particles[];
};

uniform int n_particles;

uniform vec4 cursor;
uniform float pressed;

void main() {
  vec4 direction = vec4(0.0f);
  for (int i = 0; i<particles.length(); i++) {
    vec4 diff = - (particles[gl_GlobalInvocationID.x].position - particles[i].position);
    direction = direction + diff;
  }
  vec4 cursor_dir = cursor - particles[gl_GlobalInvocationID.x].position;

  particles[gl_GlobalInvocationID.x].velocity += ((direction / n_particles) + (8.0f / max(length(cursor_dir), 1.0f)) * cursor_dir * pressed) /  10000.0f;
  particles[gl_GlobalInvocationID.x].velocity *= 0.999f; // a bit of inertia
  particles[gl_GlobalInvocationID.x].position += particles[gl_GlobalInvocationID.x].velocity;
}
