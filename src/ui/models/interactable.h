#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include "interaction.h"

#include <map>

class Interactable {
public:
  Interactable();
  virtual ~Interactable();
  void on(EVENT_NAME eventName, event_callback_t callback);
  void off(EVENT_NAME eventName);

  void handleEvent(Event& event);
private:
  std::map<EVENT_NAME, event_callback_t> eventListener;
};

#endif