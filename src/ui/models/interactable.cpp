#include "interactable.h"

#include "applicationStore.h"

Interactable::Interactable() {
  
};

Interactable::~Interactable() {

}

void Interactable::on(EVENT_NAME eventName, event_callback_t callback) {
  _STORE->interactionManager->on(eventName, this);
  this->eventListener.insert(std::pair<EVENT_NAME, event_callback_t>(eventName, callback));
}

void Interactable::off(EVENT_NAME eventName) {
  _STORE->interactionManager->off(eventName, this);
  auto it = this->eventListener.find(eventName);
  if(it != this->eventListener.end()) {
    this->eventListener.erase(it);
  }
}

void Interactable::handleEvent(Event& event) {
  auto c = this->eventListener.find(event.eventName);
  if(c != this->eventListener.end()) {
    c->second(event, this);
  }
}