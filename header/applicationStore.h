#ifndef APPLICATION_STORE_H
#define APPLICATION_STORE_H

class ApplicationStore {
public:
  static ApplicationStore* getInstance();

  int windowWidth = 1024;
  int windowHeight = 768;

private:
  ApplicationStore();
  static ApplicationStore* instance;
};

#endif