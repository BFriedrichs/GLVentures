
#include <GL/glew.h>
#include <OpenGL/gl.h>

#include <iostream>

#include "drawableRect.h"

DrawableRect::DrawableRect(int x, int y, int width, int height) : Rect(x, y, width, height) {
  const char* vertexShader =
  "#version 400\n"
  "in vec3 vp;"
  "void main() {"
  "  gl_Position = vec4(vp, 1.0);"
  "}";
  
  const char* fragmentShader =
  "#version 400\n"
  "uniform vec3 color;"
  "uniform float alpha;"
  "out vec4 fragColor;"
  "void main() {"
  "  fragColor = vec4(color, alpha);"
  "}";
  

  this->createShader(vertexShader, fragmentShader);

  glUseProgram(this->shaderProgram);
  this->colorLocation = glGetUniformLocation(this->shaderProgram, "color");
  this->alphaLocation = glGetUniformLocation(this->shaderProgram, "alpha");  

  this->setColor((const float[]) {0, 0, 0});
  this->setAlpha(1);
}

DrawableRect::~DrawableRect() {

}

void DrawableRect::setColor(const float color[]) {
  std::memcpy(this->color, color, sizeof(float) * 3);
}

void DrawableRect::setAlpha(const float alpha) {
  this->alpha = alpha;
}

void DrawableRect::render() {
  glUseProgram(this->shaderProgram);

  glUniform3fv(this->colorLocation, 1, this->color);
  glUniform1f(this->alphaLocation, this->alpha);

  Rect::render();
}