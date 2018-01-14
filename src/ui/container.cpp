#include "container.h"

#include <algorithm>

Container::Container() { }

Container::~Container() {
  for(auto const& r: this->children) {
    delete r;
  }
}

void Container::addChild(Rect* rect) {
  this->calcGlobalBounds();

  rect->setParent(this);
  this->children.push_back(rect);

  this->calcGlobalBounds();
  if(this->parent != NULL) {
    this->parent->calcGlobalBounds();
  }
}

void Container::removeAllChilds() {
  this->children.erase(this->children.begin(), this->children.end());
}

Rect* Container::getChildAt(int i) {
  return this->children[i];
}

int Container::length() {
  return this->children.size();
}

void Container::calcGlobalBounds() {
  Rect::calcGlobalBounds();

  for(auto const& r: this->children) {
    r->calcGlobalBounds();
  }

  bounds_t cb = this->getBounds();
  int x = cb.x;
  int y = cb.y;
  int width = INT32_MIN;
  int height = INT32_MIN;
  
  for(auto const& r: this->children) {
    bounds_t b = r->getBounds();
    width = std::max(width, r->getX() + b.width);
    height = std::max(height, r->getY() + b.height);
  }

  width = width == INT32_MIN ? 0 : width;
  height = height == INT32_MIN ? 0 : height;

  this->_bounds = {x, y, width, height};
}

void Container::render() {
  for(auto const& r: this->children) {
    r->render();
  }
}
