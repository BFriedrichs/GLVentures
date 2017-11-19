#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include <string>

#include "text.h"
#include "container.h"

class TextInput: public Container {
public:
  TextInput();
  ~TextInput();

  void setText(std::wstring text);
  std::wstring getText();
private:
  Text* text;

  int cursorIndex = 0;
};

#endif
