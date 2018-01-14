#include "textArea.h"

TextArea::TextArea(std::wstring text) {
  this->text = text;
  int lineCount = 1;
  int y = 0;

  for(int i = 0; i < lineCount; i++) {
    TextInput* input = new TextInput(text);
    this->addChild(input);
    this->lines.push_back(input);

    input->setY(y);
    y += 40;
  }
}

TextArea::~TextArea() {

}