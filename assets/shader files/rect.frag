vec4 shader() {
  vec4 __outputColor = vec4(1.0f, 1.0f, 1.0f , 1.0f);

  #ifdef COLOR_MIXIN
    COLOR_MIXIN(__outputColor);
  #endif

  #ifdef BORDER_RADIUS_MIXIN
    BORDER_RADIUS_MIXIN(__outputColor);
  #endif

  #ifdef ALPHA_MIXIN
    ALPHA_MIXIN(__outputColor);
  #endif

  return __outputColor;
}