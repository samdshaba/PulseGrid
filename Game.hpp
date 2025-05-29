#ifndef GAME_HPP
#define GAME_HPP
#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <random>

class Game {
private:
    sf::RenderWindow& window;
    std::vector<std::vector<std::unique_ptr<Entity>>> grid; // 2D grid for pulses
    std::vector<std::unique_ptr<Entity>> waves; // Enemy waves
    sf::Vector2i cursorPos;
    float stability; // Network stability (0 to 100)
    std::mt19937 rng;
    bool isLevelComplete;

public:
    Game(sf::RenderWindow& win);
    void handleEvents();
    void update(float deltaTime);
    void render();
};

#endif // GAME_HPP
