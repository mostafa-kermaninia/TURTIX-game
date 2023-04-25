#include "Game.h"

// PRIVATE
void Game::initVariables()
{
    window = nullptr;

    // Game logic
    points = 0;
    enemySpawnTimerMax = 1000.f;
    enemySpawnTimer = enemySpawnTimerMax;
    maxEnemies = 5;
}
void Game::initWindow()
{
    videoMode.height = 600;
    videoMode.width = 800;

    window = new sf::RenderWindow(videoMode, "TURTIX", sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(60);
}
void Game::initEnemies()
{
    enemy.setPosition(10.f, 10.f);
    enemy.setSize(sf::Vector2f(100.f, 100.f));
    enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    enemy.setFillColor(sf::Color::Black);
    enemy.setOutlineColor(sf::Color::Green);
    enemy.setOutlineThickness(1.f);
}

// CONSTRUCTS / DESTRUCTORS
Game::Game()
{
    initVariables();
    initWindow();
    initEnemies();
}
Game::~Game()
{
    delete window;
}

// PUBLIC
const bool Game::running() const
{
    return window->isOpen();
}
void Game::spawnEnemy()
{
    enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(window->getSize().x - enemy.getSize().x)),
        static_cast<float>(rand() % static_cast<int>(window->getSize().y - enemy.getSize().y)));

    enemy.setFillColor(sf::Color::Green);
    enemies.push_back(enemy);
}
void Game::pollEvents()
{
    // Event handling
    while (window->pollEvent(ev))
    {
        switch (ev.type)
        {
        case sf::Event::Closed:
            window->close();
            break;

        case sf::Event::KeyPressed:
            if (ev.key.code == sf::Keyboard::Escape)
                window->close();
            break;
            ;
        }
    }
}
void Game::updateMousePositions()
{
    mousePosWindow = sf::Mouse::getPosition(*window);
}

void Game::updateEnemies()
{
    // Update timer for enemy spawning
    if (enemies.size() < maxEnemies)
    {
        if (enemySpawnTimer >= enemySpawnTimerMax)
        {
            // Spawn enemy and reset timer
            spawnEnemy();
            spawnEnemy();
            spawnEnemy();
            spawnEnemy();
            spawnEnemy();
            enemySpawnTimer = 0.f;
        }
        else
        {
            enemySpawnTimer++;
        }
    }

    // Move the enemies
    for (auto &e : enemies)
    {
        e.move(0.f, 2.f);
    }
}
void Game::update()
{
    pollEvents();
    updateMousePositions();
    updateEnemies();

    // Relative to screen
    // std::cout << "MOUSE: " << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << '\n';
    // Relative to window
    // std::cout << "MOUSE: " << sf::Mouse::getPosition(*window).x << " " << sf::Mouse::getPosition(*window).y << '\n';
}

void Game::renderEnemies()
{
    for (auto &e : enemies)
    {
        window->draw(e);
    }
}
void Game::render()
{
    window->clear(sf::Color(0, 255, 255));
    renderEnemies();
    window->display();
}