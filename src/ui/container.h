#ifndef CONTAINER_H
#define CONTAINER_H

#include <vector>

#include "models/rect.h"

class Container : public Rect {
public:
  Container();
  ~Container();

  void addChild(Rect* rect);
  void removeAllChilds();
  Rect* getChildAt(int i);
  int length();

  virtual void render();
  virtual void calcGlobalBounds();

  void handleEvent();
protected:
  std::vector<Rect*> children;
};

#endif