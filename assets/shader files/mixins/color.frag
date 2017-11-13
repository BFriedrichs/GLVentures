uniform vec3 color;

#define COLOR_MIXIN(color) (color = colorMixin(color))

vec4 colorMixin(vec4 _color) {
  return vec4(color, _color.a);
}