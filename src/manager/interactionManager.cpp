#include "interactionManager.h"

#include <iostream>

InteractionManager::InteractionManager() {};

void InteractionManager::on(EVENT_NAME eventName, Interactable* element) {
  auto it = this->eventListener.find(eventName);
  if(it != this->eventListener.end()) {
    it->second.push_back(element);
  } else {
    std::vector<Interactable*> v;
    v.push_back(element);
    this->eventListener.insert(std::pair<EVENT_NAME, std::vector<Interactable*>>(eventName, v));
  }
}

void InteractionManager::off(EVENT_NAME eventName, Interactable* element) {
  auto it = this->eventListener.find(eventName);

  if(it != this->eventListener.end()) {
    std::vector<Interactable*> interactables = it->second;
    auto itVec = std::find(interactables.begin(), interactables.end(), element);
    if(itVec != interactables.end()) {
      interactables.erase(itVec);
    }
  }
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
      
      for(auto const& currEntry: entry.second) {
         // unhappy about this but currently best way to create the relation
        Rect* rect = dynamic_cast<Rect*>(currEntry);
        bounds_t bounds = rect->getBounds();

        event.local = Point{event.global.x - bounds.x, event.global.y - bounds.y};

        if(bounds.contains(event.global)) {
          if(event.eventName == EVENT_NAME::mousedown || event.eventName == EVENT_NAME::mouseup || event.eventName == EVENT_NAME::click) {
            currEntry->handleEvent(event);
          }
        } else if(event.eventName == EVENT_NAME::mousedownoutside || event.eventName == EVENT_NAME::mouseupoutside) {
          currEntry->handleEvent(event);
        }
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
            for(auto const& currEntry: entry.second) {
              currEntry->handleEvent(ke);
            }
          }
        }
      }
      break;
    default:
      break;
  }
}