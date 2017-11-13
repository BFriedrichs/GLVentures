#include <GL/glew.h>
#include <OpenGL/gl.h>

#include <cstring>
#include <iterator>
#include <algorithm>

#include "rect.h"
#include "sizeHelper.h"

#include "applicationStore.h"
#include <iostream>

extern ApplicationStore* _STORE;

using namespace glm;

Rect::Rect() {};

Rect::Rect(int x, int y, int width, int height) {
  this->createShader("assets/shader files/rect.vert", "assets/shader files/rect.frag");

  this->sizeLocation = glGetUniformLocation(this->shaderProgram, "size");  
  this->borderRadiusLocation = glGetUniformLocation(this->shaderProgram, "borderRadius");

  std::cout << this->sizeLocation << std::endl;

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

void Rect::setBorderRadius(int borderRadius) {
  this->borderRadius = borderRadius;
}

void Rect::render() {
  Drawable::render();

  glUniform1i(this->borderRadiusLocation, this->borderRadius);
  int size[4] = {
    this->x, 
    _STORE->windowHeight - this->y - this->height, // flip y because FragCoord 0,0 is bottom left
    this->width, 
    this->height
  };

  glUniform4iv(this->sizeLocation, 1, size);
  //std::cout << this->sizeLocation << " " << size[0] << " " << size[1] << " " << size[2] << " " << size[3] << std::endl;

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
