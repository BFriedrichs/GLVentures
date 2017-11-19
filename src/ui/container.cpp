#include "container.h"

#include <algorithm>

Container::Container() { }

void Container::addChild(Rect* rect) {
  this->calcGlobalBounds();

  rect->setParent(this);
  this->children.push_back(rect);
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

  int x = this->x;
  int y = this->y;
  int width = INT32_MIN;
  int height = INT32_MIN;
  
  for(auto const& r: this->children) {
    width = std::max(width, r->getX() + r->getWidth());
    height = std::max(height, r->getY() + r->getHeight());
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
