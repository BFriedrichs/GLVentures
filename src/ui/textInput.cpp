#include "textInput.h"

#include <GLFW/glfw3.h>

TextInput::TextInput() {
  this->textElement = new Text();
  this->addChild(this->textElement);

  this->cursor = new Quad(0, 0, 2, 16);
  this->addChild(this->cursor);

  this->focusChanged(false);
}

TextInput::TextInput(std::wstring text): TextInput() {
  this->setText(text);
}

TextInput::~TextInput() {
  this->off(EVENT_NAME::keydown);

  delete this->textElement;
  delete this->cursor;
}

void TextInput::setText(std::wstring text) {
  this->cursor->setPosition(0, 0);
  this->textElement->setText(text);
  this->cursor->setPosition(this->getBounds().width - 7, 2);
}

void TextInput::focusChanged(bool isFocused) {
  if(isFocused) {
    this->cursor->setAlpha(1);
    this->on(EVENT_NAME::keydown, (event_callback_t) TextInput::onInput);
  } else {
    this->cursor->setAlpha(0);
    this->off(EVENT_NAME::keydown);
  }
}

std::wstring TextInput::getText() {
  return this->textElement->getText();
}

void TextInput::onInput(Event& e, Interactable* instance) {
  std::cout << "input" << std::endl;
  TextInput* i = dynamic_cast<TextInput*>(instance);

  if(i->isFocused()) {
    KeyboardEvent& ke = (KeyboardEvent&) e;
    
  
    switch(ke.key) {
      case GLFW_KEY_BACKSPACE:
        i->setText(i->textElement->getText().substr(0, i->textElement->getText().size() - 1));
        break;
      case GLFW_KEY_ENTER:
        break;
      case GLFW_KEY_TAB:
        break;
      default: 
        if(ke.action == -1) {
          i->setText(i->textElement->getText() + ke.key);
        }
        break;
    }
  }
}