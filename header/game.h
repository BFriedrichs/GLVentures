#ifndef GAME_H
#define GAME_H

class Game {
  public:
    Game();
    ~Game();

    void start();
    void update();
    void render();
    void cursorUpdate(double xpos, double ypos);
    void keyUpdate(int key, int scancode, int action, int mods);
};

#endif