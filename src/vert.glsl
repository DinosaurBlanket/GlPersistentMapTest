#version 410

in  vec3 pos;
in  vec4 color;
out vec4 colorThrough;

void main() {
  colorThrough = color;
  gl_Position = vec4(pos, 1.0);
}
