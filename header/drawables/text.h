#ifndef TEXT_H
#define TEXT_H

#include "rect.h"
#include "fontHelper.h"

class Text: public Rect {
public:
  Text(int x, int y, const char* text);
  ~Text();

  virtual void render();
  virtual int getVectorSize() { return 20; }
private:
  TextImage* textImage;
  unsigned int texture;
};

#endif