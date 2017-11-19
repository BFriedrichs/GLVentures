#ifndef GLYPH_H
#define GLYPH_H

#include "quad.h"
#include "fontHelper.h"

class Glyph: public Quad {
public:
  Glyph(wchar_t c);
  ~Glyph();

  virtual void render();
  letter getLetter();
protected:
  virtual std::string getShaderType() { return "text"; };

  unsigned int texture;
  TextImage* textImage;

  virtual int getVectorSize() { return 20; }
};

#endif