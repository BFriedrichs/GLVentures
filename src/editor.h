#ifndef EDITOR_H
#define EDITOR_H

#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <GLFW/glfw3.h>

class Editor {
  public:
    Editor();
    ~Editor();

    void start();
    void update(float delta);
    void render();
    void cursorUpdate(GLFWwindow* window, double xpos, double ypos);
    void keyUpdate(GLFWwindow* window, int key, int scancode, int action, int mods);
    void charUpdate(GLFWwindow* window, unsigned int character);
};

#endif