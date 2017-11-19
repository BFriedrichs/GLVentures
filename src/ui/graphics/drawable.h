#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <string>
#include <iostream>

#include <GL/glew.h>
#include <OpenGL/gl.h>

class Drawable {
public:
  virtual void render();

  void setColor(const float color[]);
  void setAlpha(const float alpha);  
  void linkShader();

protected:
  virtual std::string getShaderType() { return "rect"; };

  GLuint shaderProgram = 0;
  GLint alphaLocation = 0;
  GLint colorLocation = 0;
  
  float alpha = 1.0f;
  float color[3] = {0, 0, 0};

  Drawable();
};

#endif