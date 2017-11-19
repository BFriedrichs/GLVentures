#ifndef QUAD_H
#define QUAD_H

#include <GL/glew.h>
#include <OpenGL/gl.h>

#include "drawable.h"
#include "rect.h"

class Quad: public Drawable, public Rect {
public:
  Quad();
  Quad(int x, int y, int width, int height);
  ~Quad();

  void setBorderRadius(int borderRadius);

  virtual void render();
  virtual void setRect(int x, int y, int width, int height);
  virtual void calcGlobalBounds();
protected:
  virtual std::string getShaderType() { return "rect"; };

  GLint sizeLocation = 0;
  GLint borderRadiusLocation = 0;
  int borderRadius = 0;

  virtual int getVectorSize() { return 12; }
  float vectors[20];
  void setVectors();
};

#endif