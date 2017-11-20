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

void InteractionManager::_internalHandleCursorEvent(CursorEvent& event) {
  for(auto const &entry : this->eventListener) {
    if(event.eventName == entry.first) {
      // unhappy about this but currently best way to create the relation
      Rect* rect = dynamic_cast<Rect*>(entry.second);
      bounds_t bounds = rect->getBounds();

      event.local = Point{event.global.x - bounds.x, event.global.y - bounds.y};

      if(bounds.contains(event.global)) {
        if(event.eventName == EVENT_NAME::mousedown || event.eventName == EVENT_NAME::mouseup || event.eventName == EVENT_NAME::click) {
          entry.second->handleEvent(event);
        }
      } else if(event.eventName == EVENT_NAME::mousedownoutside || event.eventName == EVENT_NAME::mouseupoutside) {
        entry.second->handleEvent(event);
      }
    }
  }
}

void InteractionManager::handleEvent(Event& event) {
  switch(event.type) {
    case cursor:
      {
        CursorEvent &ce = (CursorEvent&) event;

        this->_internalHandleCursorEvent(ce);
        
        if(ce.eventName == EVENT_NAME::mousedown || ce.eventName == EVENT_NAME::mouseup) {
          EVENT_NAME outsideName = EVENT_NAME::mousedownoutside;
          if(ce.eventName == EVENT_NAME::mouseup) {
            outsideName = EVENT_NAME::mouseupoutside;
          }

          CursorEvent outsideEvent(outsideName, ce.global);
          this->_internalHandleCursorEvent(outsideEvent);
        }
        

        if(ce.eventName == EVENT_NAME::mouseup && lastMouseDown.x == ce.global.x && lastMouseDown.y == ce.global.y) {
          // create click event
          CursorEvent clickEvent(EVENT_NAME::click, ce.global);
          this->_internalHandleCursorEvent(clickEvent);
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
        KeyboardEvent &ke = (KeyboardEvent&) event;
        
        for(auto const &entry : this->eventListener) {
          if(ke.eventName == entry.first) {
            entry.second->handleEvent(ke);
          }
        }
      }
      break;
    default:
      break;
  }
}