#version 430 core

layout (location = 0) in vec4 position;

struct particle {
  vec4 position;
  vec4 velocity;
};

out vec4 vp;
out vec4 vel;

uniform particle p;

void main() {
  vp = (position + p.position) * 0.4f;
  vel = p.velocity;
  gl_Position = vp;
}
