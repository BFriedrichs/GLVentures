#include "drawable.h"

Drawable::Drawable() {

}

void Drawable::createShader(const char* vertexShader, const char* fragmentShader) {
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertexShader, NULL);
  glCompileShader(vs);
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragmentShader, NULL);
  glCompileShader(fs);

  this->shaderProgram = glCreateProgram();

  glAttachShader(this->shaderProgram, fs);
  glAttachShader(this->shaderProgram, vs);
  glLinkProgram(this->shaderProgram);
  glUseProgram(this->shaderProgram);
}