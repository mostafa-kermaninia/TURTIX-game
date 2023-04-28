#include "Game.h"

// PRIVATE FUNCS
void Game::initWindow()
{
    window = new sf::RenderWindow(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "GAME SPACEEEE", sf::Style::Close | sf::Style::Titlebar);
    window->setFramerateLimit(144);
    window->setVerticalSyncEnabled(false);
}
void Game::initWorld()
{
    if (!worldBackgroundTexture.loadFromFile("Textures/background.png"))
    {
        std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND PIC!!!" << std::endl;
    }
    worldBackground.setTexture(worldBackgroundTexture);

    float scaleHeight = (float)WINDOWHEIGHT / worldBackgroundTexture.getSize().y;
    float scaleWidth = (float)WINDOWWIDTH / worldBackgroundTexture.getSize().x;
    worldBackground.scale(scaleWidth, scaleHeight);
}

void Game::initMap()
{
    map = new Map();
}
void Game::initPlayer()
{
    player = new Player();
}

// CON/DES
Game::Game()
{
    initWindow();
    initWorld();
    initMap();
    initPlayer();
}
Game::~Game()
{
    delete window;
    delete map;
    delete player; 
}

// FUNCS
void Game::run()
{
    while (window->isOpen())
    {
        update();
        render();
    }
}
void Game::updatePollEvents()
{
    sf::Event e;
    while (window->pollEvent(e))
    {
        if (e.Event::type == sf::Event::Closed)
        {
            window->close();
        }
        if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
        {
            window->close();
        }
    }
}
void Game::updateInput()
{
    // Move Player
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        if (player->getDir() == RIGHT)
        {
            player->goBack();
        }
        player->move(-1.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        if (player->getDir() == LEFT)
        {
            player->goBack();
        }
        player->move(1.f, 0.f);
    }
    if (((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
     && player->is_jumping_finished())
     || !player->is_jumping_finished())
    {
        player->jump(0.f, -1.f);   
    }
}
void Game::update()
{
    updatePollEvents();
    updateInput();
}
void Game::renderWorld()
{
    window->draw(worldBackground);
}
void Game::render()
{
    window->clear(sf::Color::Cyan);

    // Draw world
    renderWorld();

    // DRAW all things
    player->render(*window);
    map->render(*window);

    window->display();
}
