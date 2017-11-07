#ifndef RECT_H
#define RECT_H

#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <cstring>
#include <iostream>

#include "drawable.h"

class Rect: public Drawable {
public:
  Rect();
  Rect(int x, int y, int width, int height);
  ~Rect();

  int getX() { return this->x; };
  int getY() { return this->y; };
  int getWidth() { return this->width; };
  int getHeight() { return this->height; };

  void setX(int x);
  void setY(int y);
  void setWidth(int width);
  void setHeight(int height);

  void setPosition(int x, int y);
  void setSize(int width, int height);

  void setRect(int x, int y, int width, int height);

  virtual void render();
  virtual int getVectorSize() { return 12; }
protected:
  float vectors[20];
  int x, y, width, height;
};

#endif