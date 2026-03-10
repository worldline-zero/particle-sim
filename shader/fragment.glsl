#version 430 core

in vec4 vp;
in vec4 vel;

out vec4 FragColor;

void main() {
  vec3 color = vec3(length(vel));
  FragColor = vec4(color * 50.0f, 1.0f);
}
