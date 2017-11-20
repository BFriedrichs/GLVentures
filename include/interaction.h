#ifndef INTERACTION_H
#define INTERACTION_H

#include "structs.h"
#include "interactable.h"

enum EVENT_TYPE { cursor, keyboard };
enum EVENT_NAME { __default, mouseup, mousedown, mousemove, mousedownoutside, mouseupoutside, click, keydown, keyup };

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
  CursorEvent(EVENT_NAME eventName, Point global, Point local): Event(eventName, EVENT_TYPE::cursor), global{global.x, global.y}, local{local.x, local.y} {};
  CursorEvent(EVENT_NAME eventName, Point global): Event(eventName, EVENT_TYPE::cursor), global{global.x, global.y} {};
  Point global;
  Point local;
};

class KeyboardEvent: public Event{
public:
  KeyboardEvent(EVENT_NAME eventName, wchar_t key): Event(eventName, EVENT_TYPE::keyboard), key(key) {};
  KeyboardEvent(EVENT_NAME eventName, wchar_t key, int action, int mods): Event(eventName, EVENT_TYPE::keyboard), key(key), action(action), mods(mods) {};
  wchar_t key;
  int action = -1;
  int mods = -1;
};

typedef void (*event_callback_t)(Event&, void*);

#endif