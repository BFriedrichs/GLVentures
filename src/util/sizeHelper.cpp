#include "sizeHelper.h"

glm::vec2 SizeHelper::sizeToGlobal(glm::vec2 size) {
  return glm::vec2(size[0] * 2 / WINDOW_WIDTH, size[1] * 2 / WINDOW_HEIGHT);
}

glm::vec2 SizeHelper::posToGlobal(glm::vec2 pos) {
  glm::vec2 newPos = SizeHelper::sizeToGlobal(pos);
  return glm::vec2(newPos[0] - 1, 1 - newPos[1]);
}