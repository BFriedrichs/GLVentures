#ifndef TEXTAREA_H
#define TEXTAREA_H

#include <string>
#include <vector>

#include "container.h"
#include "structs.h"
#include "textInput.h"


class TextArea: public Container {
public:
  TextArea(std::wstring text);
  ~TextArea();

  vec2 selectionStart;
  vec2 selectionEnd;

  std::vector<TextInput*> lines;
  std::wstring text;
};


#endif
