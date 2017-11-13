#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "Game.h"
#include "rect.h"
#include "Text.h"

Rect* r;
Rect* r2;
Rect* r3;
Text* t;
Rect* cursor;

Game::Game() {
  r = new Rect(200, 200, 50, 50);
  r2 = new Rect(0, 0, 512, 512);
  r3 = new Rect(512, 512, 512, 512);

  t = new Text(100, 0, "Test Text.", 10);

  float color[] =  {0.1, 0.5, 0.5};
  r->setColor(color);

  float color2[] =  {0.2, 0.2, 0.5};
  r3->setColor(color2);

  r->setBorderRadius(10);
}

Game::~Game() {

} 

void Game::start() {
    
}

void Game::update(float delta) {
  r->updatePosition(delta);
}

void Game::render() {
  r2->render();
  r3->render();
  llt->render();

  
  r->render();
}

void Game::cursorUpdate(GLFWwindow* window, double xpos, double ypos) {

}

void Game::keyUpdate(GLFWwindow* window, int key, int scancode, int action, int mods) {
  auto getKey = [&window] (int keyCode) {
    return glfwGetKey(window, keyCode);
  };

  if(action == GLFW_RELEASE) {
    if(key == GLFW_KEY_D && getKey(GLFW_KEY_A) != GLFW_PRESS) {
      r->setAccelerationX(0);
    }
    if(key == GLFW_KEY_W && getKey(GLFW_KEY_S) != GLFW_PRESS) {
      r->setAccelerationY(0);
    }
    if(key == GLFW_KEY_A && getKey(GLFW_KEY_D) != GLFW_PRESS) {
      r->setAccelerationX(0);
    }
    if(key == GLFW_KEY_S && getKey(GLFW_KEY_W) != GLFW_PRESS) {
      r->setAccelerationY(0);
    }
  }

  if(action == GLFW_PRESS) {
    if(key == GLFW_KEY_D) {
      r->setAccelerationX(100);
    }
    if(key == GLFW_KEY_W) {
      r->setAccelerationY(-100);
    }
    if(key == GLFW_KEY_A) {
      r->setAccelerationX(-100);
    }
    if(key == GLFW_KEY_S) {
      r->setAccelerationY(100);
    }
  }
}