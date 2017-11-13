uniform sampler2D tex;

in vec2 fragTexCoord;

vec4 shader() {
  return texture(tex, fragTexCoord);
}