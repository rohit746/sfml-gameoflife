#include "Game.h"
#include <iostream>

void copyVector(std::vector<Cell> &v1, std::vector<Cell> &v2) {
    v2.clear();
    for (const auto & i : v1) {
        v2.push_back(i);
    }
}

Game::Game() {
    window.create(sf::VideoMode(this->WINDOW_SIZE, this->WINDOW_SIZE), "Game of life!");
    window.setFramerateLimit(FPS);
    for (int i = 0; i < this->GRID_SIZE; i++) {
        for (int j = 0; j < this->GRID_SIZE; j++) {
            Cell newCell(i, j, this->CELL_SIZE);
            this->grid.push_back(newCell);
            this->gridCopy.push_back(newCell);
        }
    }
    isRunning = false;
}

Game::~Game() = default;

int Game::getLivingNeighbors(int x, int y) {
    int livingNeighbors = 0;
    if (x < GRID_SIZE - 1                                  &&  grid[y * GRID_SIZE + x + 1].isAlive()) livingNeighbors++;
    if (x > 0                                              &&  grid[y * GRID_SIZE + x - 1].isAlive()) livingNeighbors++;
    if (y < GRID_SIZE - 1                                  &&  grid[(y + 1) * GRID_SIZE + x].isAlive()) livingNeighbors++;
    if (y > 0                                              &&  grid[(y - 1) * GRID_SIZE + x].isAlive()) livingNeighbors++;
    if (y < GRID_SIZE - 1   &&  x < GRID_SIZE - 1          &&  grid[(y + 1) * GRID_SIZE + x + 1].isAlive()) livingNeighbors++;
    if (y < GRID_SIZE - 1   &&  x > 0                      &&  grid[(y + 1) * GRID_SIZE + x - 1].isAlive()) livingNeighbors++;
    if (y > 0               &&  x < GRID_SIZE - 1          &&  grid[(y - 1) * GRID_SIZE + x + 1].isAlive()) livingNeighbors++;
    if (y > 0               &&  x > 0                      &&  grid[(y - 1) * GRID_SIZE + x - 1].isAlive()) livingNeighbors++;

    return livingNeighbors;
}

void Game::run() {
    this->elapsedActivated = this->clockActivating.getElapsedTime();
    while(window.isOpen()) {
        sf::Event event{};
        this->elapsedActivated = this->clockActivating.getElapsedTime();
        elapsedStart = clockStart.getElapsedTime();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.mouseButton.button == sf::Mouse::Left && !isRunning) {
                int yCell = event.mouseButton.x / CELL_SIZE;
                int xCell = event.mouseButton.y / CELL_SIZE;
                grid[yCell * ROWS + xCell].update(this->window, this->clockActivating, this->elapsedActivated);
                // getLivingNeighbors(xCell, yCell);
            } else {
                event.type = sf::Event::KeyPressed;
                if (event.type) {
                    if (event.key.code == sf::Keyboard::Space) {
                        if (elapsedStart.asSeconds() >= 2) {
                            std::cout << "Apasat\n";
                            isRunning = !isRunning;
                            clockStart.restart();
                        }
                    }
                    if (event.key.code == sf::Keyboard::R && !isRunning) {
                        for (auto & i : grid) {
                            i.kill();
                        }
                    }
                }
            }
        }
        if (isRunning) {
            copyVector(grid, gridCopy);
            std::cout << "DA";
            for (int i = 0; i < grid.size(); i++) {
                int nb = getLivingNeighbors(grid[i].getX(), grid[i].getY());
                gridCopy[i].isAlive();
                if (nb < 2) {
                    gridCopy[i].kill();
                } else if (nb > 3) {
                    gridCopy[i].kill();
                } else if (nb == 3) {
                    gridCopy[i].born();
                }
            }
            copyVector(gridCopy, grid);
        }
        for (auto & i : grid) {
            i.draw(window);
        }
        window.display();
    }
}