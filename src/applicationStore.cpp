#include "applicationStore.h"
#include <iostream>

ApplicationStore::ApplicationStore() {

};

ApplicationStore* ApplicationStore::instance = new ApplicationStore();

ApplicationStore* ApplicationStore::getInstance() {
  return ApplicationStore::instance;
}

void ApplicationStore::init() {
  this->fontHelper = new FontHelper();
  this->shader = new ShaderManager();
}