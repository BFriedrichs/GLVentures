#include <GL/glew.h>
#include <OpenGL/gl.h>

#include <cstring>
#include <iterator>
#include <algorithm>

#include "structs.h"
#include "quad.h"
#include "sizeHelper.h"

#include "applicationStore.h"
#include <iostream>

extern ApplicationStore* _STORE;

Quad::Quad() : Quad(0, 0, 100, 100) {};

Quad::Quad(int x, int y, int width, int height) : Rect(x, y, width, height) {
  this->linkShader();

  this->sizeLocation = glGetUniformLocation(this->shaderProgram, "size");
  this->borderRadiusLocation = glGetUniformLocation(this->shaderProgram, "borderRadius");
}

Quad::~Quad() {

}

void Quad::setRect(int x, int y, int width, int height) {
  Rect::setRect(x, y, width, height);
  this->setVectors();
}

void Quad::setBorderRadius(int borderRadius) {
  this->borderRadius = borderRadius;
}

void Quad::setVectors() {
  bounds_t globalBounds = this->getBounds();

  PointF pos = SizeHelper::posToGlobal(Point{globalBounds.x, globalBounds.y});
  PointF size = SizeHelper::sizeToGlobal(Point{globalBounds.width, globalBounds.height});

  float square[] = {
    pos[0], pos[1] - size[1], 0,
    pos[0] + size[0], pos[1] - size[1], 0,
    pos[0], pos[1], 0,
    pos[0] + size[0], pos[1], 0
  };
  
  std::memcpy(this->vectors, square, sizeof(float) * 12);
}

void Quad::calcGlobalBounds() {
  Rect::calcGlobalBounds();
  this->setVectors();
}

void Quad::render() {
  Drawable::render();
  
  glUniform1i(this->borderRadiusLocation, this->borderRadius);
  bounds_t b = this->getBounds();
  int size[4] = {
    b.x, 
    _STORE->windowHeight - b.y - b.height, // flip y because FragCoord 0,0 is bottom left
    b.width, 
    b.height
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
