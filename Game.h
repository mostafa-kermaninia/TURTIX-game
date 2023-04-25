#pragma once
#include <iostream>
#include <vector>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class Game
{
private:
    // Window
    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Event ev;

    // Mouse position
    sf::Vector2i mousePosWindow;

    // Game logic
    int points;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;

    // Game objects
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;

    // Private
    void initVariables();
    void initWindow();
    void initEnemies();

public:
    Game();
    virtual ~Game();

    const bool running() const;

    // FUNCS
    void spawnEnemy();

    void pollEvents();
    void updateMousePositions();

    void updateEnemies();
    void update();

    void renderEnemies();
    void render();
};