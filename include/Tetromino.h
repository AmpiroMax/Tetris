#ifndef TETROMINO_H
#define TETROMINO_H

#include <SFML/Graphics.hpp>

struct Point {
    int x, y;
};

class Tetromino {
public:
    Tetromino();
    void spawn();
    bool move(int dx, int dy, int field[20][10]);
    void rotate(int field[20][10]);
    void place(int field[20][10]);
    bool isValidPosition(int field[20][10]);
    Point getPosition(int index);
    sf::Color getColor();
    static sf::Color getColor(int num); // Добавляем статический метод

private:
    Point blocks[4];
    Point tempBlocks[4];
    int color;
    int type;
    static const int figures[7][4];
    bool check(int field[20][10]);
};

#endif // TETROMINO_H