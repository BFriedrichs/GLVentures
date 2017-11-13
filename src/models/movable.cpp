
#include <iostream>
#include <cmath>

#include "movable.h"
#include "rect.h"


Movable::Movable() {

}

void Movable::setAcceleration(float x, float y) {
  this->acceleration.x = x * (this->moveSpeed / 1000.0f);
  this->acceleration.y = y * (this->moveSpeed / 1000.0f);
}

void Movable::setAccelerationX(float x) {
  this->setAcceleration(x, this->acceleration.y);
}

void Movable::setAccelerationY(float y) {
  this->setAcceleration(this->acceleration.x, y);
}

void Movable::updatePosition(float delta) {
  this->setPosition(this->getX() + this->velocity.x, this->getY() + this->velocity.y);

  if(this->acceleration.x == 0 && std::abs(this->velocity.x) < (1 - this->friction.y)) {
    this->velocity.x = 0;
  } else {
    this->velocity.x = this->velocity.x * (1 - this->friction.x) + this->acceleration.x * delta;
  }

  if(this->acceleration.y == 0 && std::abs(this->velocity.y) < (1 - this->friction.y)) {
    this->velocity.y = 0;
  } else {
    this->velocity.y = this->velocity.y * (1 - this->friction.y) + this->acceleration.y * delta;
  }
}