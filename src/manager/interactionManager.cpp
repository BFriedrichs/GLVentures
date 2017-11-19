#include "interactionManager.h"

#include <iostream>

InteractionManager::InteractionManager() {};

void InteractionManager::on(EVENT_NAME eventName, Interactable* element) {
  this->eventListener.insert(std::pair<EVENT_NAME, Interactable*>(eventName, element));
}

void InteractionManager::off(EVENT_NAME eventName, Interactable* element) {
  
}

Point InteractionManager::getLastCursorPos() {
  return this->lastCursorPos;
}

Point InteractionManager::getLastMouseDown() {
  return this->lastMouseDown;
}

void InteractionManager::handleEvent(Event& event) {
  switch(event.type) {
    case cursor:
      {
        CursorEvent &ce = (CursorEvent&) event;

        CursorEvent* clickEvent = NULL;
        if(ce.eventName == EVENT_NAME::mouseup && lastMouseDown.x == ce.global.x && lastMouseDown.y == ce.global.x) {
          // create click event
          clickEvent = new CursorEvent(EVENT_NAME::click, ce.global.x, ce.global.x);
        }

        for(auto const &entry : this->eventListener) {
          if(ce.eventName == entry.first) {
            // unhappy about this but currently best way to create the relation
            Rect* rect = dynamic_cast<Rect*>(entry.second);
            bounds_t bounds = rect->getBounds();

            if(bounds.contains(ce.global)) {
              entry.second->handleEvent(ce);

              if(clickEvent != NULL) {
                entry.second->handleEvent(*clickEvent);
              }
            }
          }
        }

        if(clickEvent != NULL) {
          //delete clickEvent;
        }

        if(ce.eventName == EVENT_NAME::mousedown) {
          lastMouseDown = ce.global;
        }

        if(ce.eventName == EVENT_NAME::mousemove) {
          lastCursorPos = ce.global;
        }
      }
      break;
    case keyboard:
      {

      }
      break;
    default:
      break;
  }
}