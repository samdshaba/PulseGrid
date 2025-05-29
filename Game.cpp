#include "Game.hpp"
#include <cmath>

class Pulse : public Entity {
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    float timer;
    bool active;

public:
    Pulse(float x, float y) : position(x, y), timer(0.f), active(true) {
        shape.setRadius(10.f);
        shape.setFillColor(sf::Color::Blue);
        shape.setPosition(position);
    }

    void update(float deltaTime) override {
        timer += deltaTime;
        if (timer > 3.f) active = false; // Pulse lasts 3 seconds
    }

    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }

    sf::Vector2f getPosition() const override { return position; }
    bool isActive() const override { return active; }
    void disrupt(float strength) override {} // Pulses aren't disrupted
};

class Wave : public Entity {
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    float strength;
    bool active;

public:
    Wave(float x, float y) : position(x, y), strength(1.f), active(true) {
        shape.setRadius(15.f);
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(position);
    }

    void update(float deltaTime) override {
        shape.setPosition(position);
    }

    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }

    sf::Vector2f getPosition() const override { return position; }
    bool isActive() const override { return active; }
    void disrupt(float disruptStrength) override {
        strength -= disruptStrength;
        if (strength <= 0.f) active = false;
    }
};

Game::Game(sf::RenderWindow& win) : window(win), cursorPos(0, 0), stability(0.f), rng(std::random_device{}()), isLevelComplete(false) {
    grid.resize(5, std::vector<std::unique_ptr<Entity>>(5));
    std::uniform_real_distribution<float> distX(250.f, 450.f);
    std::uniform_real_distribution<float> distY(150.f, 350.f);
    for (int i = 0; i < 3; ++i) {
        waves.push_back(std::make_unique<Wave>(distX(rng), distY(rng)));
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::R) {
                grid.clear();
                grid.resize(5, std::vector<std::unique_ptr<Entity>>(5));
                waves.clear();
                std::uniform_real_distribution<float> distX(250.f, 450.f);
                std::uniform_real_distribution<float> distY(150.f, 350.f);
                for (int i = 0; i < 3; ++i) {
                    waves.push_back(std::make_unique<Wave>(distX(rng), distY(rng)));
                }
                cursorPos = {0, 0};
                stability = 0.f;
                isLevelComplete = false;
            } else if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            } else if (event.key.code == sf::Keyboard::Up && cursorPos.y > 0) {
                cursorPos.y--;
            } else if (event.key.code == sf::Keyboard::Down && cursorPos.y < 4) {
                cursorPos.y++;
            } else if (event.key.code == sf::Keyboard::Left && cursorPos.x > 0) {
                cursorPos.x--;
            } else if (event.key.code == sf::Keyboard::Right && cursorPos.x < 4) {
                cursorPos.x++;
            } else if (event.key.code == sf::Keyboard::Space && !grid[cursorPos.y][cursorPos.x]) {
                grid[cursorPos.y][cursorPos.x] = std::make_unique<Pulse>(250.f + cursorPos.x * 50.f, 150.f + cursorPos.y * 50.f);
            }
        }
    }
}

void Game::update(float deltaTime) {
    // Update grid entities
    for (auto& row : grid) {
        for (auto& entity : row) {
            if (entity) entity->update(deltaTime);
        }
    }

    // Update waves
    for (auto& wave : waves) {
        wave->update(deltaTime);
    }

    // Check pulse disruptions
    for (auto& row : grid) {
        for (auto& pulse : row) {
            if (pulse && pulse->isActive()) {
                sf::Vector2f pulsePos = pulse->getPosition();
                for (auto& wave : waves) {
                    if (wave->isActive()) {
                        float dist = std::hypot(pulsePos.x - wave->getPosition().x, pulsePos.y - wave->getPosition().y);
                        if (dist < 50.f) {
                            wave->disrupt(0.5f); // Disrupt wave
                            stability += 5.f; // Increase instability per pulse
                        }
                    }
                }
            }
        }
    }

    // Check level completion
    isLevelComplete = std::all_of(waves.begin(), waves.end(), [](const auto& wave) { return !wave->isActive(); });
}

void Game::render() {
    window.clear(sf::Color::Black);

    // Draw grid
    for (int i = 0; i <= 5; ++i) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(250.f, 150.f + i * 50.f), sf::Color::White),
            sf::Vertex(sf::Vector2f(450.f, 150.f + i * 50.f), sf::Color::White)
        };
        window.draw(line, 2, sf::Lines);
        line[0] = sf::Vertex(sf::Vector2f(250.f + i * 50.f, 150.f), sf::Color::White);
        line[1] = sf::Vertex(sf::Vector2f(250.f + i * 50.f, 350.f), sf::Color::White);
        window.draw(line, 2, sf::Lines);
    }

    // Draw cursor
    sf::RectangleShape cursor(sf::Vector2f(50.f, 50.f));
    cursor.setFillColor(sf::Color::Transparent);
    cursor.setOutlineColor(sf::Color::Yellow);
    cursor.setOutlineThickness(2.f);
    cursor.setPosition(250.f + cursorPos.x * 50.f, 150.f + cursorPos.y * 50.f);
    window.draw(cursor);

    // Render entities
    for (const auto& row : grid) {
        for (const auto& entity : row) {
            if (entity) entity->render(window);
        }
    }
    for (const auto& wave : waves) {
        wave->render(window);
    }

    // Draw stability meter
    sf::RectangleShape stabilityBar(sf::Vector2f(200.f * (stability / 100.f), 20.f));
    stabilityBar.setPosition(300.f, 50.f);
    stabilityBar.setFillColor(stability > 80.f ? sf::Color::Red : sf::Color::Green);
    window.draw(stabilityBar);

    // Draw win/lose condition
    if (isLevelComplete) {
        sf::Text winText;
        winText.setString("Level Complete!");
        winText.setCharacterSize(24);
        winText.setFillColor(sf::Color::Green);
        winText.setPosition(300.f, 400.f);
        window.draw(winText);
    } else if (stability >= 100.f) {
        sf::Text loseText;
        loseText.setString("Network Overload!");
        loseText.setCharacterSize(24);
        loseText.setFillColor(sf::Color::Red);
        loseText.setPosition(300.f, 400.f);
        window.draw(loseText);
    }

    window.display();
}
