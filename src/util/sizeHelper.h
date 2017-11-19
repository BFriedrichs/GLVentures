#ifndef SIZEHELPER_H
#define SIZEHELPER_H

#include "structs.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768


class SizeHelper {
public:
  static PointF sizeToGlobal(Point size);
  static PointF posToGlobal(Point pos);
private:
  SizeHelper() {};
};


#endif
