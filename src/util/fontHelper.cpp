#include "fontHelper.h"

#include <iostream>
#include <GL/glew.h>
#include <OpenGL/gl.h>

TextImage::TextImage() {
  this->width = 0;
  this->height = 0;
  this->baseline = 0;
  this->alpha = 1.0f;
  this->po2_width = 0;
  this->po2_height = 0;
  this->image_data = NULL;
  this->letters = NULL;
  this->texture = 0;
};

TextImage::~TextImage() { 
  if(this->image_data != NULL) {
    delete[] this->image_data; 
  }
  if(letters != NULL) {
    delete[] this->letters;
  }
  glDeleteTextures(1, &this->texture);
};

int TextImage::generatePNGBuffer(uchar*** buffer) {
  if(buffer == NULL) {
    return -1;
  }

  (*buffer) = (uchar**) new pixel*[po2_height];

  for(int i = 0; i < po2_height; i++) {
    (*buffer)[i] = (uchar*) new pixel[po2_width];
    std::memcpy((*buffer)[i], &image_data[po2_width * i], sizeof(pixel) * po2_width);
  }

  return 0;
};

/*
  only pixels with pre-existing alpha will be changed

  @param letterIndices - indices of letters which should be changed
  @param p - pixel that the corresponding pixels will be overwritten with
  @param setAlpha - set new alpha
*/
void TextImage::setPixels(std::vector<int>& letterIndices, pixel& p, bool setAlpha) {
  double newAlpha = (double) p.a / 255;
  for(int i = 0; i < po2_height; i++) {

    for(int j = 0; j < letterIndices.size(); j++) {
      letter currLetter = this->letters[letterIndices[j]];

      for(int k = 0; k < currLetter.w; k++) {
        
        int index = i * this->po2_width + currLetter.x + k;
        pixel* currPixel = &this->image_data[index];
        if(currPixel->a > 0) {
          currPixel->r = p.r;
          currPixel->g = p.g;
          currPixel->b = p.b;
          if(setAlpha) {
            // hack to be able to change these in the future
            currPixel->a = std::max(1, (int)(currPixel->a / this->alpha * newAlpha));
          }
        }
      }
    }
  }
  if(setAlpha) {
    this->alpha = newAlpha;
  }
}

FontHelper::FontHelper() {
  this->ft = new FT_Library;
  this->face = new FT_Face;
  
  this->_CACHED_CHARS = L"abcdefghijklmnopqrstuvwxyz"
                        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                        "1234567890";
                        "+-*/.,:;(){}[]|<>#'\"?=#";

  this->loadFont();
}

FontHelper::~FontHelper() {
  delete this->ft;
  delete this->face;
}

void FontHelper::generateCache(std::wstring s) {
  std::wcout << "Generate Cache: " << FontHelper::_CACHED_CHARS.length() << std::endl;

  for(int i = 0; i < s.length(); i++) {
    auto x = this->getTextureForChar(s.at(i));
  }
}

TextImage* FontHelper::getTextureForChar(wchar_t c) {
  auto find = this->fontCache.find(c);
  TextImage* result = NULL;

  if(find == this->fontCache.end()) {
    result = this->renderChar(c);
    this->fontCache.insert(std::pair<wchar_t, TextImage*>(c, result));
  } else {
    result = find->second;
  }

  return result;
}

void FontHelper::loadFont() {
  if(FT_Init_FreeType(this->ft)) {
    fprintf(stderr, "Could not init freetype library\n");
  }

  FT_New_Face(*this->ft, "/Applications/Utilities/Terminal.app/Contents/Resources/Fonts/SFMono-Regular.otf", 0, this->face);
  setFontSize(this->fontSize);
}

void FontHelper::setFontSize(int size) {
  this->fontSize = size;
  //FT_Set_Char_Size(*this->face, 0, size*size, 300, 300); 
  FT_Set_Pixel_Sizes(*this->face, 0, size);
  this->generateCache(this->_CACHED_CHARS);
}

TextImage* FontHelper::renderChar(wchar_t code) {
  TextImage* result = new TextImage;

  FT_UInt glyph_index = FT_Get_Char_Index(*this->face, (FT_ULong) code);
  FT_Load_Glyph(*this->face, glyph_index, FT_LOAD_DEFAULT);
  FT_GlyphSlot slot = (*this->face)->glyph;

  //render_glyph returns an array containing 8-bit values representing the current alpha status of each pixel from 0x00 to 0xFF, 0x00 being invisible
  FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);

  int height = slot->bitmap.rows;
  int width = slot->bitmap.width;
  int bitmapTop = slot->bitmap_top;
  int underBaseline = height - bitmapTop;

  letter* newLetters = new letter[1];

  auto x = [](int point_size) {
    return point_size * (1024 / 768) / 72;
  };

  letter l = {code, result->width, bitmapTop, x(slot->advance.x) + 1, height};
  std::memcpy(&newLetters[0], &l, sizeof(letter));

  result->letters = newLetters;
  uchar* bitmap = slot->bitmap.buffer;

  int newWidth = result->width + width + 2 * slot->bitmap_left;
  int newHeight = height + slot->bitmap_top;

  // find next power of two
  int newPo2Width =  std::max(16, (int) std::pow(2, std::ceil(std::log2(newWidth))));
  int newPo2Height = std::max(16, (int) std::pow(2, std::ceil(std::log2(newHeight))));

  pixel* old_data = result->image_data;
  int size = newPo2Height * newPo2Width;
  result->image_data = new pixel[size];

  std::fill((uchar*)result->image_data, (uchar*)(result->image_data + size), 0);

  for(int i = 0; i < result->po2_height; i++) {
    std::memcpy(&result->image_data[newPo2Width * i], &old_data[result->po2_width * i], sizeof(pixel) * result->width);
  }

  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      uchar currPixel = bitmap[i * width + j];
      pixel p = { 255, 255, 255, currPixel };

      int row = i * newPo2Width;
      int col = result->width + j + slot->bitmap_left;
      std::memcpy(&result->image_data[row + col], &p, sizeof(pixel));
    }
  }

  result->width = newWidth;
  result->height = newHeight;
  result->po2_width = newPo2Width;
  result->po2_height = newPo2Height;

  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1, &result->texture);
  glBindTexture(GL_TEXTURE_2D, result->texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, newPo2Width, newPo2Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, result->image_data);

  return result;
}

TextImage* FontHelper::renderText(std::string string) {
  TextImage* result = new TextImage;
/*
  for(int c_i = 0; c_i < string.length(); c_i++) {
    char c = string[c_i];
    FT_UInt glyph_index = FT_Get_Char_Index(*this->face, c);
    FT_Load_Glyph(*this->face, glyph_index, FT_LOAD_DEFAULT);
    FT_GlyphSlot slot = (*this->face)->glyph;

    //render_glyph returns an array containing 8-bit values representing the current alpha status of each pixel from 0x00 to 0xFF, 0x00 being invisible
    FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);

    int height = slot->bitmap.rows;
    int width = slot->bitmap.width;
    int bitmapTop = slot->bitmap_top;
    int underBaseline = height - bitmapTop;

    if(c == ' ') {
      width = this->fontSize;
    }

    letter* newLetters = new letter[c_i + 1];

    if(result->letters != NULL) {
      std::memcpy(newLetters, result->letters, c_i * sizeof(letter));
      delete result->letters;
    }

    letter l = {c, result->width, bitmapTop, width + slot->bitmap_left, height};
    std::memcpy(&newLetters[c_i], &l, sizeof(letter));

    result->letters = newLetters;
    uchar* bitmap = slot->bitmap.buffer;

    int newWidth = result->width + width + slot->bitmap_left;
    int newHeight = std::max(std::max(result->height, result->baseline + underBaseline), height + (result->height - result->baseline));

    if(newHeight > result->height) {
      result->baseline = newHeight - std::max(underBaseline, result->height - result->baseline);
    }

    // find next power of two
    int newPo2Width = std::pow(2, std::ceil(std::log2(newWidth)));
    int newPo2Height = std::pow(2, std::ceil(std::log2(newHeight)));
    
    int heightOffset = result->baseline - bitmapTop;

    pixel* old_data = result->image_data;
    int size = newPo2Height * newPo2Width;
    result->image_data = new pixel[size];

    std::fill((uchar*)result->image_data, (uchar*)(result->image_data + size), 0);

    for(int i = 0; i < result->po2_height; i++) {
      std::memcpy(&result->image_data[newPo2Width * i], &old_data[result->po2_width * i], sizeof(pixel) * result->width);
    }

    for(int i = 0; i < height; i++) {
      for(int j = 0; j < width; j++) {
        uchar currPixel = bitmap[i * width + j];
        pixel p = { 255, 255, 255, currPixel };

        int row = (i + heightOffset) * newPo2Width;
        int col = result->width + j + slot->bitmap_left;
        std::memcpy(&result->image_data[row + col], &p, sizeof(pixel));
      }
    }

    result->width = newWidth;
    result->height = newHeight;
    result->po2_width = newPo2Width;
    result->po2_height = newPo2Height;

    if(old_data != NULL) {
      delete[] old_data;
    }
  }
*/
  return result;
}