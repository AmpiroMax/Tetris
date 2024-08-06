#include "Interface.h"
#include <sstream>

Interface::Interface() {
    if (!font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
        throw std::runtime_error("Failed to load font");
    }
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(200, 10);

    tile.setSize(sf::Vector2f(TILE_SIZE - 1, TILE_SIZE - 1));
}

void Interface::draw(sf::RenderWindow& window, int field[20][10], Tetromino& currentTetromino, Tetromino& nextTetromino, int score) {
    // Draw the field
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            if (field[i][j] == 0) continue;
            tile.setFillColor(Tetromino::getColor(field[i][j]));
            tile.setPosition(j * TILE_SIZE, i * TILE_SIZE);
            tile.move(28, 31); // offset
            window.draw(tile);
        }
    }

    // Draw the current tetromino
    for (int i = 0; i < 4; i++) {
        tile.setFillColor(currentTetromino.getColor());
        tile.setPosition(currentTetromino.getPosition(i).x * TILE_SIZE, currentTetromino.getPosition(i).y * TILE_SIZE);
        tile.move(28, 31); // offset
        window.draw(tile);
    }

    // Draw the next tetromino
    for (int i = 0; i < 4; i++) {
        tile.setFillColor(nextTetromino.getColor());
        tile.setPosition(200 + nextTetromino.getPosition(i).x * TILE_SIZE, 50 + nextTetromino.getPosition(i).y * TILE_SIZE);
        window.draw(tile);
    }

    // Draw the score
    std::ostringstream ss;
    ss << "Score: " << score;
    scoreText.setString(ss.str());
    window.draw(scoreText);

    // Draw game area border
    sf::RectangleShape border(sf::Vector2f(10 * TILE_SIZE, 20 * TILE_SIZE));
    border.setPosition(28, 31);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(1);
    border.setOutlineColor(sf::Color::Black);
    window.draw(border);
}