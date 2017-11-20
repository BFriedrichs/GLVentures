#include "editor.h"

#include <iostream>
#include <string>
#include <stdlib.h>

#include "applicationStore.h"

#include "ui/graphics/quad.h"
#include "ui/textInput.h"
#include "ui/text.h"
#include "ui/container.h"

#include "interaction.h"

Container* cont;
Text* t1;

Editor::Editor() {
  Quad* q1 = new Quad(200, 200, 50, 50);
  Quad* q2 = new Quad(0, 0, 512, 512);
  Quad* q3 = new Quad(512, 512, 512, 512);

  float color[] =  {0.1, 0.5, 0.5};
  q2->setColor(color);

  float color2[] =  {0.2, 0.2, 0.5};
  q3->setColor(color2);

  q1->setBorderRadius(10);
  TextInput* ti = new TextInput();
  ti->setPosition(100, 150);
  t1 = new Text(L"Hello World!");
  t1->setPosition(100, 100);

  cont = new Container();

  Container* cont2 = new Container();
  cont2->setPosition(50, 50);
  
  cont2->addChild(q2);
  cont2->addChild(q1);

  cont->addChild(q3);
  cont->addChild(cont2);
  cont->addChild(ti);
  cont->addChild(t1);
  
  event_callback_t x = [](Event& e, void* i) {
    CursorEvent& ce = (CursorEvent&) e;

    t1->setText(L"Click at " + std::to_wstring(ce.local.x) +  L", " + std::to_wstring(ce.local.y));
  };

  t1->on(EVENT_NAME::click, x);
  
  
}

Editor::~Editor() {

} 

void Editor::start() {
    
}

void Editor::update(float delta) {

}

void Editor::render() {
  cont->render();
}

void Editor::cursorUpdate(GLFWwindow* window, double xpos, double ypos) {
  CursorEvent e(EVENT_NAME::mousemove, xpos, ypos);
  _STORE->interactionManager->handleEvent(e);
}

void Editor::cursorAction(GLFWwindow* window, int button, int action, int mods) {
  EVENT_NAME name = EVENT_NAME::__default;

  if (button == GLFW_MOUSE_BUTTON_LEFT) {
    if(action == GLFW_PRESS) {
      name = EVENT_NAME::mousedown;
    } else if(action == GLFW_RELEASE) {
      name = EVENT_NAME::mouseup;
    }
  }

  CursorEvent e(name, _STORE->interactionManager->getLastCursorPos());
  _STORE->interactionManager->handleEvent(e);
}

void Editor::charUpdate(GLFWwindow* window, unsigned int character) {
  // for now only keydown is supported
  KeyboardEvent e(EVENT_NAME::keydown, character);
  _STORE->interactionManager->handleEvent(e);
}

void Editor::keyUpdate(GLFWwindow* window, int key, int scancode, int action, int mods) {
  auto getKey = [&window] (int keyCode) {
    return glfwGetKey(window, keyCode);
  };

  EVENT_NAME name = EVENT_NAME::__default;

  if(action == GLFW_PRESS || action == GLFW_REPEAT) {
    name = EVENT_NAME::keydown;
  } else if(action == GLFW_RELEASE) {
    name = EVENT_NAME::keyup;
  }

  switch(key) {
    case GLFW_KEY_BACKSPACE:
    case GLFW_KEY_ENTER:
    case GLFW_KEY_TAB:
      {
        KeyboardEvent e(name, key, action, mods);
        _STORE->interactionManager->handleEvent(e);
      }
    break;
  }
}