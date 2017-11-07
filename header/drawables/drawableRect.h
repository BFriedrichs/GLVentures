#ifndef DRAWABLERECT_H
#define DRAWABLERECT_H

#include "rect.h"

class DrawableRect: public Rect {
public:
  DrawableRect(int x, int y, int width, int height);
  ~DrawableRect();

  void setColor(const float color[]);
  void setAlpha(const float alpha);

  virtual void render();
private:
  GLint colorLocation = 0;
  GLint alphaLocation = 0;
  float alpha = 0;
  float color[3] = {0, 0, 0};
};
  
#endif