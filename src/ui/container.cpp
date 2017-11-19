#include "container.h"

#include <algorithm>

Container::Container() { }

void Container::addChild(Rect* rect) {
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

  int x = INT32_MAX;
  int y = INT32_MAX;
  int width = INT32_MIN;
  int height = INT32_MIN;
  
  for(auto const& r: this->children) {
    x = std::min(x, r->getX());
    y = std::min(y, r->getY());
    width = std::max(x + width, r->getX() + r->getWidth());
    height = std::max(y + height, r->getY() + r->getHeight());
  }

  this->_bounds = {x, y, width, height};
}

void Container::render() {
  for(auto const& r: this->children) {
    r->render();
  }
}
