uniform sampler2D tex;

in vec2 fragTexCoord;

vec4 shader() {
  vec4 _tex = texture(tex, fragTexCoord);

  #ifdef ALPHA_MIXIN
    ALPHA_MIXIN(_tex);
  #endif

  return _tex;
}