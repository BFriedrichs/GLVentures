#ifndef INTERACTION_H
#define INTERACTION_H

#include "structs.h"


enum EVENT_TYPE { cursor, keyboard };
enum EVENT_NAME { mouseup, mousedown, mousemove, click };

class Event {
public:
  Event(EVENT_NAME eventName, EVENT_TYPE type): eventName(eventName), type(type) {};
  ~Event() {};
  EVENT_NAME eventName;
  EVENT_TYPE type;
};

class CursorEvent: public Event {
public:
  CursorEvent(EVENT_NAME eventName, int globalX, int globalY): Event(eventName, EVENT_TYPE::cursor), global{globalX, globalY} {};
  CursorEvent(EVENT_NAME eventName, Point global): Event(eventName, EVENT_TYPE::cursor), global{global.x, global.y} {};
  Point global;
};

class KeyboardEvent: public Event{
public:
  KeyboardEvent(EVENT_NAME eventName, char key): Event(eventName, EVENT_TYPE::keyboard), key(key) {};
  char key;
};

typedef void (*event_callback_t)(Event&);

#endif