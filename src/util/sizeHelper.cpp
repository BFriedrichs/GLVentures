#include "sizeHelper.h"

PointF SizeHelper::sizeToGlobal(Point size) {
  return PointF{(float)(size.x) * 2 / WINDOW_WIDTH, (float)(size.y) * 2 / WINDOW_HEIGHT};
}

PointF SizeHelper::posToGlobal(Point pos) {
  PointF newPos = SizeHelper::sizeToGlobal(pos);
  return PointF{newPos.x - 1, 1 - newPos.y};
}