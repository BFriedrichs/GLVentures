#ifndef FOCUSABLE_H
#define FOCUSABLE_H

#include "interactable.h"

class Focusable: public virtual Interactable {
public:
  Focusable();
  ~Focusable();
  void setFocused(bool isFocused);
  void toggleFocus();
  bool isFocused();

  virtual void focusChanged(bool isFocused);

  static void onFocus(Event& e, Interactable* instance);
  static void onUnFocus(Event& e, Interactable* instance);
private:
  bool _isFocused = false;

  using Interactable::on;
  using Interactable::off;
};

#endif