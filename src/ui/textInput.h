#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include <string>

#include "focusable.h"
#include "text.h"
#include "container.h"
#include "graphics/quad.h"

class TextInput: public Container, public Focusable {
  using Container::Interactable;

public:
  TextInput();
  ~TextInput();

  void setText(std::wstring text);
  std::wstring getText();
  
  virtual void focusChanged(bool isFocused);
private:
  Text* textElement;
  Quad* cursor;

  static void onInput(Event& e, Interactable* instance);

  int cursorIndex = 0;
};

#endif
