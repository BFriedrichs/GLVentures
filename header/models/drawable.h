#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <iostream>
#include <GL/glew.h>
#include <OpenGL/gl.h>

class Drawable {
public:
  virtual void render() {};
  void createShader(const char* vertexShader, const char* fragmentShader);
protected:
  GLuint shaderProgram = 0;

  Drawable();
};

#endif