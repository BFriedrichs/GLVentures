#include "editor.h"

#include <iostream>
#include <string>

#include "applicationStore.h"

#include "ui/graphics/quad.h"
#include "ui/textInput.h"
#include "ui/text.h"
#include "ui/container.h"

#include "interaction.h"

Container* cont;
Text* t1;
Text* t2;

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
  t1 = new Text(L"Hello World!");
  t1->setPosition(100, 100);
  t2 = new Text(L"");
  t2->setPosition(100, 116);

  cont = new Container();
  cont->addChild(q1);
  cont->addChild(q2);
  cont->addChild(q3);
  cont->addChild(ti);
  cont->addChild(t1);
  cont->addChild(t2);

  event_callback_t x = [](Event& e) {
    CursorEvent& ce = (CursorEvent&) e;

    t1->setText(L"Click at " + std::to_wstring(ce.global.x) +  L", " + std::to_wstring(ce.global.y));
  };

  t1->on(EVENT_NAME::mousedown, x);
  
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
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    CursorEvent e(EVENT_NAME::mousedown, _STORE->interactionManager->getLastCursorPos());
    _STORE->interactionManager->handleEvent(e);
  }
}

void Editor::charUpdate(GLFWwindow* window, unsigned int character) {
  t2->setText(t2->getText() + std::wstring(1, (wchar_t) character));
}

void Editor::keyUpdate(GLFWwindow* window, int key, int scancode, int action, int mods) {
  auto getKey = [&window] (int keyCode) {
    return glfwGetKey(window, keyCode);
  };

  if(key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS) {
    t2->setText(t2->getText().substr(0, t2->getText().size() - 1));
  }
/*
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
  */
}