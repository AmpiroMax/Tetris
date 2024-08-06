#ifndef INTERFACE_H
#define INTERFACE_H

#include <SFML/Graphics.hpp>
#include "Tetromino.h"

const int TILE_SIZE = 18; // Добавлено объявление TILE_SIZE

class Interface {
public:
    Interface();
    void draw(sf::RenderWindow& window, int field[20][10], Tetromino& currentTetromino, Tetromino& nextTetromino, int score);

private:
    sf::Font font;
    sf::Text scoreText;
    sf::RectangleShape tile;
};

#endif // INTERFACE_H