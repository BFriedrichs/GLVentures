#include "text.h"

#include <iostream>
#include "graphics/glyph.h"

Text::Text(int x, int y, std::wstring text): Text(text) {
  this->setPosition(x, y);
}

Text::Text(std::wstring text) {
  this->setText(text);
}

void Text::setText(std::wstring text) {
  if(text != this->text) {
    this->text = text;
    this->removeAllChilds();
  
    int lastWidth = 0;
  
    for(int i = 0; i < this->text.length(); i++) {
      Glyph* g = new Glyph(this->text[i]);
      letter l = g->getLetter();
      g->setX(lastWidth);
      g->setY(16 - l.y);
      lastWidth += l.w;
  
      this->addChild(g);
    }
  }
}

std::wstring Text::getText() {
  return this->text;
}
