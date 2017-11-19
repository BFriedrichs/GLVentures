#include "textInput.h"

TextInput::TextInput() {
  Text* t = new Text();
  this->text = t;
  this->addChild(t);
}

TextInput::~TextInput() {
  delete this->text;
}

void TextInput::setText(std::wstring text) {
  this->text->setText(text);
}

std::wstring TextInput::getText() {
  return this->text->getText();
}