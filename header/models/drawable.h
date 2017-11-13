#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <vector>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <OpenGL/gl.h>

#include "mixins.h"

class Drawable {
public:
  virtual void render();

  void setColor(const float color[]);
  void setAlpha(const float alpha);  
  void createShader(const char* vertexShader, const char* fragmentShader);

protected:
  virtual std::vector<std::string> getShaderMixins() { return std::vector<std::string> { MIXIN_ALPHA, MIXIN_COLOR }; };

  GLuint shaderProgram = 0;

  GLint alphaLocation = 0;
  GLint colorLocation = 0;
  
  float alpha = 1.0f;
  float color[3] = {0, 0, 0};

  Drawable();
};

#endif