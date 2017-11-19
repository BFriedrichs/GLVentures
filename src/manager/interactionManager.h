#ifndef INTERACTIONMANAGER_H
#define INTERACTIONMANAGER_H

#include <string>
#include <map>
#include "rect.h"

enum EVENT_TYPE { cursor, keyboard };

typedef struct {
  std::string eventName;
  EVENT_TYPE type;
} Event;

typedef struct {
  std::string eventName;
  EVENT_TYPE type;
  int globalX;
  int globalY;
} CursorEvent;

typedef struct {
  std::string eventName;
  EVENT_TYPE type;
  char key;
} KeyboardEvent;

class InteractionManager {
public:
  InteractionManager();

  void on(std::string eventName, Rect* element);
  void off(std::string eventName, Rect* element);

  void handleEvent(Event* event);
private:
  std::map<std::string, Rect*> eventListener;
};

#endif