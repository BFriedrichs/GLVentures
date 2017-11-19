#include "rect.h"

#include <cstring>
#include <algorithm>

#include "sizeHelper.h"
#include "applicationStore.h"

#include <iostream>

extern ApplicationStore* _STORE;

Rect::Rect() : Rect(0, 0, 0, 0) { }

Rect::Rect(int x, int y, int width, int height): _bounds{x, y, width, height} {
  this->setRect(x, y, width, height);
}

Rect::Rect(const Rect& rect) : Rect(rect.x, rect.y, rect.width, rect.height) { }

Rect::~Rect() { }

void Rect::setRect(int x, int y, int width, int height) {
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;

  this->calcGlobalBounds();
}

void Rect::setPosition(int x, int y) {
  this->setRect(x, y, this->width, this->height);
}

void Rect::setSize(int width, int height) {
  this->setRect(this->x, this->y, width, height);
}

void Rect::setX(int x) {
  this->setPosition(x, this->y);
}

void Rect::setY(int y) {
  this->setPosition(this->x, y);
}

void Rect::setWidth(int width) {
  this->setSize(width, this->height);
}

void Rect::setHeight(int height) {
  this->setSize(this->width, height);
}

void Rect::render() {}

bounds_t Rect::getBounds() {
  return this->_bounds;
}

Rect* Rect::getParent() {
  return this->parent;
}

void Rect::setParent(Rect* parent) {
  this->parent = parent;
  this->calcGlobalBounds();
}

void Rect::removeParent() {
  this->parent = NULL;
}

void Rect::calcGlobalBounds() {

  int x = this->x;
  int y = this->y;

  Rect* parent = this->parent;
  if(parent != NULL) {
    x += parent->getX();
    y += parent->getY();
  }

  this->_bounds = {x, y, this->width, this->height};
}
