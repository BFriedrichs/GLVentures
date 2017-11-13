#version 400

in vec3 vp;
in vec2 vertTexCoord;
out vec2 fragTexCoord;

void main() {
  fragTexCoord = vertTexCoord;
  gl_Position = vec4(vp, 1.0);
}