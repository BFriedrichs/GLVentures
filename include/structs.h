#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>

typedef struct {
  int x;
  int y;

  int operator[](int i) {
    return i == 0 ? x : i == 1 ? y : -1;
  }
} Point, vec2;

typedef struct {
  float x;
  float y;

  float operator[](int i) {
    return i == 0 ? x : i == 1 ? y : -1;
  }
} PointF, vec2f;

typedef struct {
  int x;
  int y;
  int width;
  int height;

  bool contains(Point p) {
    return p.x >= this->x && p.x <= this->x + this->width && p.y >= this->y && p.y <= this->y + this->height; 
  }
} bounds_t;

#endif