uniform float alpha;

#define ALPHA_MIXIN(color) (color = alphaMixin(color))

vec4 alphaMixin(vec4 _color) {
  return vec4(_color.rgb, _color.a * alpha);
}