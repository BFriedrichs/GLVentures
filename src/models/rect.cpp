#include <GL/glew.h>
#include <OpenGL/gl.h>

#include <cstring>
#include <iterator>
#include <algorithm>

#include "rect.h"
#include "sizeHelper.h"

#include <iostream>

using namespace glm;

Rect::Rect() {};

Rect::Rect(int x, int y, int width, int height) {
  this->setRect(x, y, width, height);
}

Rect::~Rect() {

}

void Rect::setRect(int x, int y, int width, int height) {
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;

  vec2 pos = SizeHelper::posToGlobal(vec2(x, y));
  vec2 size = SizeHelper::sizeToGlobal(vec2(width, height));

  float square[] = {
    pos[0], pos[1] - size[1], 0,
    pos[0] + size[0], pos[1] - size[1], 0,
    pos[0], pos[1], 0,
    pos[0] + size[0], pos[1], 0
  };
  
  std::memcpy(this->vectors, square, sizeof(float) * 12);
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

void Rect::render() {

  GLuint indices[] {
    0,1,3,
    0,2,3
  };

  GLuint vbo = 0;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, this->getVectorSize() * sizeof(float), this->vectors, GL_DYNAMIC_DRAW);

  GLuint vao = 0;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*) (12 * sizeof(float))); // Supposed texture position
  glEnableVertexAttribArray(1);

  GLuint vbo_ind = 0;
  glGenBuffers(1, &vbo_ind);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ind);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glUseProgram(this->shaderProgram);
  glBindVertexArray(vao);

  glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, (GLvoid*) 0);

  glDeleteBuffers(1, &vbo);
  glDeleteBuffers(1, &vbo_ind);
  glDeleteVertexArrays(1, &vao);
}
