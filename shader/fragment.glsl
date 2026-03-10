#version 430 core

in vec4 vp;
in vec4 vel;

out vec4 FragColor;

void main() {
  FragColor = vec4(0.1f + 0.8f * normalize(abs(vel.xy)), 0.1f + 0.8f * sin(length(vel.xy) * 50.0f), 1.0f);
}
