#version 430

#extension GL_ARB_gpu_shader_int64 : require

layout (local_size_x = 1000, local_size_y = 1, local_size_z = 1) in;
layout (rgba32f, binding = 0) uniform image2D image_out;

struct particle {
  vec4 position;
  vec4 velocity;
};

layout (std430, binding = 2) volatile buffer ssbo_data {
  particle particles[];
};

uniform int n_particles;

uniform vec4 cursor;
uniform float pressed;

#define G 0.00000066743

void main() {
  vec4 direction = vec4(0.0f);
  for (int i = 0; i<particles.length(); i++) {
    vec4 diff = - (particles[gl_GlobalInvocationID.x].position - particles[i].position);
    direction = direction + diff; // * max(0.01f, length(diff));
      //vec4(
      //    clamp(mix(1.0f, 0.05f, diff.x), 0.01f, 1.0f),
      //    clamp(mix(1.0f, 0.05f, diff.y), 0.01f, 1.0f),
      //    0.0f, 0.0f
      //    );
  }
  //particles[gl_GlobalInvocationID.x].velocity -= abs(exp(20 - 1000.0f*length(direction))) * direction * 0.0000001f ;
  vec4 cursor_dir = cursor - particles[gl_GlobalInvocationID.x].position;

  particles[gl_GlobalInvocationID.x].velocity += ((direction / 3000.0f) + (8.0f / max(length(cursor_dir), 1.0f)) * cursor_dir * pressed) /  10000.0f;
  particles[gl_GlobalInvocationID.x].velocity *= 0.998f;
  particles[gl_GlobalInvocationID.x].position += particles[gl_GlobalInvocationID.x].velocity;
  //particles[gl_GlobalInvocationID.x].position = clamp(particles[gl_GlobalInvocationID.x].position, vec4(-1.0f/0.4f, -1.0f/0.4f, 0.0f, 0.0f), vec4(1.0f/0.4f, 1.0f/0.4f, 0.0f, 0.0f));
}
