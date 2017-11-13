
#include <cstring>
#include <iostream>

#include <GL/glew.h>
#include <OpenGL/gl.h>

#include "text.h"

Text::Text(int x, int y, const char* text, int fontSize) {
  this->createShader("assets/shader files/text.vert", "assets/shader files/text.frag");  

  FontHelper f;
  f.loadFont();
  f.setFontSize(fontSize);

  this->textImage = f.renderText(text);

  int width = this->textImage->po2_width;
  int height = this->textImage->po2_height;

  this->setRect(x, y, width, height);

  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1, &this->texture);
  glBindTexture(GL_TEXTURE_2D, this->texture);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->textImage->image_data);

  float indices[] {
    0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f 
  };

  std::memcpy(&this->vectors[12], indices, sizeof(float) * 8);

  GLint texLoc;
  texLoc = glGetUniformLocation(this->shaderProgram, "tex");
  glUniform1i(texLoc, 0);
}

Text::~Text() {
  delete this->textImage;
  glDeleteTextures(1, &this->texture);
}

void Text::render() {
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, this->texture);

  Rect::render();
}