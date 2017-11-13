#include "applicationStore.h"

ApplicationStore::ApplicationStore() {};

ApplicationStore* ApplicationStore::instance = new ApplicationStore();

ApplicationStore* ApplicationStore::getInstance() {
  return ApplicationStore::instance;
}