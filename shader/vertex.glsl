#version 430 core

layout (location = 0) in vec4 position;

struct particle {
  vec4 position;
  vec4 velocity;
};

layout (std430, binding = 2) volatile buffer particle_data {
  particle particles[];
};

out vec4 vp;
out vec4 vel;

uniform particle p;

void main() {
  vp = (position + particles[gl_InstanceID].position) * 0.4f;
  vel = particles[gl_InstanceID].velocity;
  gl_Position = vp;
}
