#ifndef RECT_H
#define RECT_H

#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <cstring>
#include <iostream>

#include "mixins.h"
#include "drawable.h"
#include "movable.h"

class Rect: public Drawable, public Movable {

friend class Movable;

public:
  Rect();
  Rect(int x, int y, int width, int height);
  ~Rect();

  virtual int getX() { return this->x; };
  virtual int getY() { return this->y; };
  int getWidth() { return this->width; };
  int getHeight() { return this->height; };

  virtual void setX(int x);
  virtual void setY(int y);
  void setWidth(int width);
  void setHeight(int height);

  virtual void setPosition(int x, int y);
  void setSize(int width, int height);

  void setRect(int x, int y, int width, int height);

  void setBorderRadius(int borderRadius);

  virtual void render();
protected:
  virtual std::vector<std::string> getShaderMixins() { return std::vector<std::string> { MIXIN_COLOR, MIXIN_ALPHA, MIXIN_BORDER_RADIUS }; };

  float vectors[20];
  int x, y, width, height;

  GLint sizeLocation = 0;
  GLint borderRadiusLocation = 0;
  int borderRadius = 0;

  virtual int getVectorSize() { return 12; }
};

#endif