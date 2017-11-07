#ifndef SIZEHELPER_H
#define SIZEHELPER_H

#include <glm/vec2.hpp>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768


class SizeHelper {
public:
  static glm::vec2 sizeToGlobal(glm::vec2 size);
  static glm::vec2 posToGlobal(glm::vec2 pos);
private:
  SizeHelper() {};
};


#endif
