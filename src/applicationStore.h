#ifndef APPLICATION_STORE_H
#define APPLICATION_STORE_H

#include "util/fontHelper.h"
#include "manager/shaderManager.h"

class ApplicationStore {
public:
  static ApplicationStore* getInstance();

  int windowWidth = 1024;
  int windowHeight = 768;

  FontHelper* fontHelper;
  ShaderManager* shader;

  void init();
private:
  ApplicationStore();
  static ApplicationStore* instance;
};

extern ApplicationStore* _STORE;

#endif