#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Game.h"
#include "DrawableRect.h"
#include "Text.h"

DrawableRect* r;
DrawableRect* r2;
DrawableRect* r3;
Text* t;
Game::Game() {
  r = new DrawableRect(200, 200, 50, 50);
  r2 = new DrawableRect(0, 0, 512, 512);
  r3 = new DrawableRect(512, 512, 512, 512);
  t = new Text(100, 100, "I am a GOD");

  float color[] =  {0.1, 0.5, 0.5};
  r->setColor(color);

  float color2[] =  {0.2, 0.2, 0.5};
  r3->setColor(color2);

  r2->setAlpha(0.1);
}

Game::~Game() {

} 

void Game::start() {
    
}

void Game::update() {

}

void Game::render() {
  r2->render();
  r3->render();
  t->render();
  r->render();
}

void Game::cursorUpdate(double xpos, double ypos) {
  t->setPosition(xpos, ypos);
}

void Game::keyUpdate(int key, int scancode, int action, int mods) {

}