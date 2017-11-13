#ifndef TEXT_H
#define TEXT_H

#include "rect.h"
#include "fontHelper.h"

class Text: public Rect {
public:
  Text(int x, int y, const char* text, int fontSize = 16);
  ~Text();

  virtual void render();
private:
  virtual std::vector<std::string> getShaderMixins() { return std::vector<std::string> { MIXIN_ALPHA }; };
  
  TextImage* textImage;
  unsigned int texture;

  virtual int getVectorSize() { return 20; }
};

#endif