#ifndef INTERACTIONMANAGER_H
#define INTERACTIONMANAGER_H

#include <string>
#include <map>

#include "structs.h"
#include "rect.h"
#include "interaction.h"
#include "interactable.h"

class InteractionManager {
public:
  InteractionManager();

  void on(EVENT_NAME eventName, Interactable* element);
  void off(EVENT_NAME eventName, Interactable* element);

  void handleEvent(Event& event);

  Point getLastCursorPos();
  Point getLastMouseDown();
private:
  std::map<EVENT_NAME, Interactable*> eventListener;

  Point lastMouseDown = {0, 0};
  Point lastCursorPos = {0, 0};
};

#endif