#include "focusable.h"

Focusable::Focusable() {
  this->on(EVENT_NAME::mousedown, (event_callback_t) Focusable::onFocus);
  this->on(EVENT_NAME::mousedownoutside, (event_callback_t) Focusable::onUnFocus);
}

Focusable::~Focusable() {
  this->off(EVENT_NAME::mousedown);
  this->off(EVENT_NAME::mousedownoutside);
}

void Focusable::setFocused(bool isFocused) {
  std::cout << "click" << std::endl;
  if(this->_isFocused != isFocused) {
    this->_isFocused = isFocused;
    this->focusChanged(isFocused);
  }
}

void Focusable::toggleFocus() {
  this->setFocused(!this->_isFocused);
}

bool Focusable::isFocused() {
  return this->_isFocused;
}

void Focusable::focusChanged(bool isFocused) { }

void Focusable::onFocus(Event& e, Interactable* instance) {
  Focusable* i = dynamic_cast<Focusable*>(instance);
  i->setFocused(true);
}

void Focusable::onUnFocus(Event& e, Interactable* instance) {
  Focusable* i = dynamic_cast<Focusable*>(instance);
  i->setFocused(false);
}