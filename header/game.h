#ifndef GAME_H
#define GAME_H

class Game {
  public:
    Game();
    ~Game();

    void start();
    void update(float delta);
    void render();
    void cursorUpdate(GLFWwindow* window, double xpos, double ypos);
    void keyUpdate(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif