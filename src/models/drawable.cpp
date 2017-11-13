#include <cstring>

#include "drawable.h"
#include "shader.h"

Drawable::Drawable() {
}

void Drawable::createShader(const char* vertexShader, const char* fragmentShader) {
  this->shaderProgram = LoadShader(vertexShader, fragmentShader, this->getShaderMixins());

  this->alphaLocation = glGetUniformLocation(this->shaderProgram, "alpha");  
  this->colorLocation = glGetUniformLocation(this->shaderProgram, "color");

  this->setColor((const float[]) {0, 0, 0});
  this->setAlpha(1);
}

void Drawable::setAlpha(const float alpha) {
  this->alpha = alpha;
}

void Drawable::setColor(const float color[]) {
  std::memcpy(this->color, color, sizeof(float) * 3);
}

void Drawable::render() {
  glUseProgram(this->shaderProgram);

  glUniform3fv(this->colorLocation, 1, this->color);
  glUniform1f(this->alphaLocation, this->alpha);
}