#ifndef MOVABLE_H
#define MOVABLE_H

typedef struct {
  float x;
  float y;
} vec2f;

class Movable {
public:
  virtual int getX() {};
  virtual int getY() {};

  virtual void setX(int x) {};
  virtual void setY(int y) {};

  virtual void setPosition(int x, int y) {};

  void setAcceleration(float x, float y);
  void setAccelerationX(float x);
  void setAccelerationY(float y);

  void updatePosition(float delta);
protected:
  Movable();
private:
  int moveSpeed = 800;

  vec2f friction = {0.1, 0.1};

  vec2f velocity = {0, 0};
  vec2f acceleration = {0, 0};
};

#endif