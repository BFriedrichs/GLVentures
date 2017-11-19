#include "interactionManager.h"

InteractionManager::InteractionManager() {};

void InteractionManager::on(std::string eventName, Rect* element) {

}

void InteractionManager::off(std::string eventName, Rect* element) {
  
}

void InteractionManager::handleEvent(Event* event) {
  switch(event->type) {
    case cursor:
      {
        CursorEvent* ce = (CursorEvent *) event;
      }
      break;
    case keyboard:
      {
        KeyboardEvent* ke = (KeyboardEvent *) event;
      }
      break;
    default:
      break;
  }
}