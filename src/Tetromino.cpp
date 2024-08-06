#include "Tetromino.h"

const int Tetromino::figures[7][4] = {
    1, 3, 5, 7, // I
    2, 4, 5, 7, // Z
    3, 5, 4, 6, // S
    3, 5, 4, 7, // T
    2, 3, 5, 7, // L
    3, 5, 7, 6, // J
    2, 3, 4, 5, // O
};

Tetromino::Tetromino() {
    spawn();
}

void Tetromino::spawn() {
    type = rand() % 7;
    color = 1 + rand() % 7;
    for (int i = 0; i < 4; i++) {
        blocks[i].x = figures[type][i] % 2 + 4;
        blocks[i].y = figures[type][i] / 2;
    }
}

bool Tetromino::move(int dx, int dy, int field[20][10]) {
    for (int i = 0; i < 4; i++) {
        tempBlocks[i] = blocks[i];
        blocks[i].x += dx;
        blocks[i].y += dy;
    }
    if (!check(field)) {
        for (int i = 0; i < 4; i++) {
            blocks[i] = tempBlocks[i];
        }
        return false;
    }
    return true;
}

void Tetromino::rotate(int field[20][10]) {
    Point p = blocks[1];
    for (int i = 0; i < 4; i++) {
        int x = blocks[i].y - p.y;
        int y = blocks[i].x - p.x;
        tempBlocks[i].x = p.x - x;
        tempBlocks[i].y = p.y + y;
    }
    if (check(field)) {
        // Коррекция позиции, если фигура выходит за пределы границ
        int minX = tempBlocks[0].x, maxX = tempBlocks[0].x;
        for (int i = 1; i < 4; i++) {
            if (tempBlocks[i].x < minX) minX = tempBlocks[i].x;
            if (tempBlocks[i].x > maxX) maxX = tempBlocks[i].x;
        }

        // Если фигура выходит за правую границу, сдвинем её влево
        if (maxX >= 10) {
            for (int i = 0; i < 4; i++) {
                tempBlocks[i].x -= (maxX - 9);
            }
        }
        // Если фигура выходит за левую границу, сдвинем её вправо
        if (minX < 0) {
            for (int i = 0; i < 4; i++) {
                tempBlocks[i].x -= minX;
            }
        }

        for (int i = 0; i < 4; i++) {
            blocks[i] = tempBlocks[i];
        }
    }
}

void Tetromino::place(int field[20][10]) {
    for (int i = 0; i < 4; i++) {
        field[blocks[i].y][blocks[i].x] = color;
    }
}

bool Tetromino::isValidPosition(int field[20][10]) {
    return check(field);
}

Point Tetromino::getPosition(int index) {
    return blocks[index];
}

sf::Color Tetromino::getColor() {
    return getColor(color);
}

sf::Color Tetromino::getColor(int num) {
    switch (num) {
        case 1: return sf::Color::Cyan;
        case 2: return sf::Color::Red;
        case 3: return sf::Color::Green;
        case 4: return sf::Color::Magenta;
        case 5: return sf::Color::Yellow;
        case 6: return sf::Color::Blue;
        case 7: return sf::Color::White;
        default: return sf::Color::Black;
    }
}

bool Tetromino::check(int field[20][10]) {
    for (int i = 0; i < 4; i++) {
        if (blocks[i].x < 0 || blocks[i].x >= 10 || blocks[i].y >= 20) {
            return false;
        } else if (field[blocks[i].y][blocks[i].x]) {
            return false;
        }
    }
    return true;
}