#ifndef TEXT_H
#define TEXT_H

#include <string>
#include "container.h"

class Text: public Container {
public:
  Text(int x, int y, std::wstring text);
  Text(std::wstring text = L"");
  
  void setText(std::wstring text);
  std::wstring getText();
private:
  std::wstring text = L"";
};

#endif