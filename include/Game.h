#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Tetromino.h"
#include "Interface.h"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void checkLines();

    sf::RenderWindow window;
    Tetromino currentTetromino;
    Tetromino nextTetromino;
    Interface gameInterface;
    int field[20][10] = {0};
    int score;
    float timer;
    float delay;
    bool isRunning;
};

#endif // GAME_H