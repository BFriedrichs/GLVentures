uniform int borderRadius;
uniform ivec4 size;

#define BORDER_RADIUS_MIXIN(color) (color = borderRadiusMixin(color))
#define M_PI 3.1415926535897932384626433832795

vec4 borderRadiusMixin(vec4 _color) {
  int pad = 1; // antialias 1 pixel

  int normBorderRadius = min(min(borderRadius, abs(size.x) + size.z / 2 - pad * 2), abs(size.y) + size.w / 2 - pad * 2); // normalise border radius if its too large

  vec2 xPos = vec2(size.x + normBorderRadius + pad, size.x + size.z - normBorderRadius - pad);
  vec2 yPos = vec2(size.y + normBorderRadius + pad, size.y + size.w - normBorderRadius - pad);

  vec2 upperLeft = vec2(xPos.x, yPos.y);
  if(gl_FragCoord.x < upperLeft.x && gl_FragCoord.y > upperLeft.y) {
    double dist = sqrt(pow(gl_FragCoord.x - upperLeft.x, 2) + pow(gl_FragCoord.y - upperLeft.y, 2));
    if(dist > normBorderRadius) {
      _color.a = float(1 - ((dist - normBorderRadius) / pad));
    }
  }

  vec2 upperRight = vec2(xPos.y, yPos.y);
  if(gl_FragCoord.x > upperRight.x && gl_FragCoord.y > upperLeft.y) {
    double dist = sqrt(pow(gl_FragCoord.x - upperRight.x, 2) + pow(gl_FragCoord.y - upperRight.y, 2));
    if(dist > normBorderRadius) {
      _color.a = float(1 - ((dist - normBorderRadius) / pad));
    }
  }

  vec2 lowerLeft = vec2(xPos.x, yPos.x);
  if(gl_FragCoord.x < lowerLeft.x && gl_FragCoord.y < lowerLeft.y) {
    double dist = sqrt(pow(gl_FragCoord.x - lowerLeft.x, 2) + pow(gl_FragCoord.y - lowerLeft.y, 2));
    if(dist > normBorderRadius) {
      _color.a = float(1 - ((dist - normBorderRadius) / pad));
    }
  }

  vec2 lowerRight = vec2(xPos.y, yPos.x);
  if(gl_FragCoord.x > lowerRight.x && gl_FragCoord.y < lowerRight.y) {
    double dist = sqrt(pow(gl_FragCoord.x - lowerRight.x, 2) + pow(gl_FragCoord.y - lowerRight.y, 2));
    if(dist > normBorderRadius) {
      _color.a = float(1 - ((dist - normBorderRadius) / pad));
    }
  }

  return _color;
}