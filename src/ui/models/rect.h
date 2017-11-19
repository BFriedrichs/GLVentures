#ifndef RECT_H
#define RECT_H

#include <cstring>
#include <iostream>
#include <map>

#include "movable.h"

typedef struct {
  int x;
  int y;
  int width;
  int height;
} bounds_t;

typedef void (*callback_t)(void*);

class Rect: public Movable {

friend class Movable;

public:
  Rect();
  Rect(int x, int y, int width, int height);
  Rect(const Rect& rect);
  ~Rect();

  virtual int getX() { return this->x; };
  virtual int getY() { return this->y; };
  virtual int getWidth() { return this->width; };
  virtual int getHeight() { return this->height; };

  virtual void setX(int x);
  virtual void setY(int y);
  virtual void setWidth(int width);
  virtual void setHeight(int height);

  virtual void setPosition(int x, int y);
  virtual void setSize(int width, int height);

  virtual void setRect(int x, int y, int width, int height);

  virtual void render();

  Rect* getParent();
  void setParent(Rect* parent);
  void removeParent();

  void on(std::string eventName, callback_t callback);
  void off(std::string eventName, callback_t callback);

  bounds_t getBounds();
  virtual void calcGlobalBounds();
protected:
  int x, y, width, height;
  bounds_t _bounds;

  Rect* parent = NULL;
  std::map<std::string, callback_t> eventListener;
};

#endif