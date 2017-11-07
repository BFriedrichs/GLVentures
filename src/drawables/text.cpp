
#include <cstring>

#include <GL/glew.h>
#include <OpenGL/gl.h>

#include "text.h"

Text::Text(int x, int y, const char* text) {
  const char* vertexShader =
  "#version 410\n"
  "in vec3 vp;"
  "in vec2 vertTexCoord;"
  "out vec2 fragTexCoord;"
  "void main() {"
  "  fragTexCoord = vertTexCoord;"
  "  gl_Position = vec4(vp, 1.0);"
  "}";
  
  const char* fragmentShader =
  "#version 410\n"
  "uniform sampler2D tex;"
  "in vec2 fragTexCoord;"
  "out vec4 frag_colour;"
  "void main() {"
  "  frag_colour = texture( tex, fragTexCoord );"
  "}";

  this->createShader(vertexShader, fragmentShader);

  FontHelper f;
  f.loadFont();

  this->textImage = f.renderText(text);

  int width = this->textImage->po2_width;
  int height = this->textImage->po2_height;

  this->setRect(x, y, width, height);

  std::cout << "x: " << this->x 
            << ", y: " << this->y 
            << ", w: " << this->width
            << ", h: " << this->height << std::endl;

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

}

void Text::render() {
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, this->texture);

  Rect::render();
}