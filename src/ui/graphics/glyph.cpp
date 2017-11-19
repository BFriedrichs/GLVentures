#include "glyph.h"

#include <cstring>
#include <iostream>

#include <GL/glew.h>
#include <OpenGL/gl.h>

#include "applicationStore.h"

extern ApplicationStore* _STORE;

Glyph::Glyph(wchar_t c) {
  this->linkShader();

  this->textImage = _STORE->fontHelper->getTextureForChar(c);

  int x = 0;
  int y = 0;
  int width = this->textImage->po2_width;
  int height = this->textImage->po2_height;

  Quad::setRect(x, y, width, height);

  float indices[] {
    0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f 
  };

  std::memcpy(&this->vectors[12], indices, sizeof(float) * 8);
  
  GLint texLoc;
  texLoc = glGetUniformLocation(this->shaderProgram, "tex");
  glUniform1i(texLoc, 0);
}

Glyph::~Glyph() {
  //glDeleteTextures(1, &this->texture);
}

letter Glyph::getLetter() {
  return this->textImage->letters[0];
}

void Glyph::render() {
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, this->textImage->texture);

  Quad::render();
}

