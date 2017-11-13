out vec4 __outputColor;

void main() {
  __outputColor = shader();

  #ifdef COLOR_MIXIN
    COLOR_MIXIN(__outputColor);
  #endif

  #ifdef ALPHA_MIXIN
    ALPHA_MIXIN(__outputColor);
  #endif

  #ifdef BORDER_RADIUS_MIXIN
    BORDER_RADIUS_MIXIN(__outputColor);
  #endif
}