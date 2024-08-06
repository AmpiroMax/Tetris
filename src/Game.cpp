#include "Game.h"
#include <sstream>

Game::Game()
: window(sf::VideoMode(320, 480), "Tetris"), score(0), timer(0), delay(0.3), isRunning(true) {
    srand(time(0));
    currentTetromino.spawn();
    nextTetromino.spawn();
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        processEvents();
        if (isRunning) {
            update();
        }
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed)
            handlePlayerInput(event.key.code, true);
    }
}

void Game::update() {
    if (timer > delay) {
        if (!currentTetromino.move(0, 1, field)) {
            currentTetromino.place(field);
            checkLines();
            currentTetromino = nextTetromino;
            nextTetromino.spawn();
            if (!currentTetromino.isValidPosition(field)) {
                isRunning = false; // Game over
            }
        }
        timer = 0;
    }
}

void Game::render() {
    window.clear(sf::Color(0, 0, 128));
    gameInterface.draw(window, field, currentTetromino, nextTetromino, score);
    window.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::Left) {
        currentTetromino.move(-1, 0, field);
    } else if (key == sf::Keyboard::Right) {
        currentTetromino.move(1, 0, field);
    } else if (key == sf::Keyboard::Down) {
        currentTetromino.move(0, 1, field);
    } else if (key == sf::Keyboard::Up) {
        currentTetromino.rotate(field);
    }
}

void Game::checkLines() {
    int lines = 0;
    for (int i = 19; i >= 0; i--) {
        bool lineFilled = true;
        for (int j = 0; j < 10; j++) {
            if (field[i][j] == 0) {
                lineFilled = false;
                break;
            }
        }
        if (lineFilled) {
            lines++;
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < 10; j++) {
                    field[k][j] = field[k - 1][j];
                }
            }
            for (int j = 0; j < 10; j++) {
                field[0][j] = 0;
            }
            i++;
        }
    }
    if (lines > 0) {
        score += 1000 * lines * (lines > 1 ? 1.5 : 1);
    }
}