#ifndef FONTHELPER_H
#define FONTHELPER_H

#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>
#include <map>
#include <stdlib.h>

#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

#include <string.h>

typedef unsigned char uchar;

typedef struct {
  uchar r;
  uchar g;
  uchar b;
  uchar a;
} pixel;

typedef struct {
  wchar_t charcode;
  int x;
  int y;
  int w;
  int h;
} letter;

class TextImage {
public:
  int width;
  int height;
  double alpha;
  int baseline;
  int po2_width;
  int po2_height;
  pixel* image_data;
  letter* letters;
  unsigned int texture;

  TextImage();
  ~TextImage();
  int generatePNGBuffer(uchar*** buffer);

  void setPixels(std::vector<int>& letterIndices, pixel& p, bool setAlpha = false);
};

class FontHelper {
public:
  FT_Library* ft;
  FT_Face* face; 
  int fontSize = 16;

  std::wstring _CACHED_CHARS;
  std::map<wchar_t, TextImage*> fontCache;

  FontHelper();
  ~FontHelper();

  void generateCache(std::wstring s);
  TextImage* getTextureForChar(wchar_t c);

  void loadFont();
  void setFontSize(int size);
  TextImage* renderText(std::string string);
  TextImage* renderChar(wchar_t code);
};

#endif