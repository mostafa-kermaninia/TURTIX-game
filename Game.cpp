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

    // float scaleHeight = (float)WINDOWHEIGHT * 3 / BACKGROUNDHEIGHT;
    // float scaleWidth = (float)WINDOWWIDTH * 3 / BACKGROUNDWIDTH;

    float scaleHeight = 0.1;
    float scaleWidth = 0.1;
    worldBackground.setScale(0.5, 0.5);
}
void Game::initView()
{
    gameView = sf::View((sf::FloatRect(WINDOWWIDTH, WINDOWWIDTH, WINDOWWIDTH, WINDOWHEIGHT)));
}
void Game::initMap()
{
    map = new Map();
}
void Game::initPlayer()
{
    player = new Player();
}

bool Game::handleCollisions()
{
    // if player is in world,it can move
    if (!player->collided(worldBackground))
    {
        return true;
    }

    // // // handle collision with objects

    // // Collision with PORTAL
    // if (player->collided(map->getPortal()))
    // {
    //     // return true;
    // }

    // // Collision with FIRST Enemies
    // for (auto enemy : map->getFEnemies())
    // {
    //     if (player->collided(enemy))
    //     {
    //         // return true;
    //     }
    // }

    // // Collision with SECOND Enemies
    // for (auto enemy : map->getSEnemies())
    // {
    //     if (player->collided(enemy))
    //     {
    //         // return true;
    //     }
    // }

    // // Collision with Jailed Babies
    // for (auto baby : map->getJailedBabies())
    // {
    //     if (player->collided(baby))
    //     {
    //         return false;
    //     }
    // }

    // // Collision with stars
    // for (auto star : map->getStars())
    // {
    //     if (player->collided(star))
    //     {
    //         // return true;
    //     }
    // }

    // // Collision with diamonds
    // for (auto diamond : map->getDiamonds())
    // {
    //     if (player->collided(diamond))
    //     {
    //         // return true;
    //     }
    // }

    // // Collision with ground
    // for (auto groundPart : map->getGround())
    // {
    //     if (player->collided(groundPart))
    //     {
    //         return false;
    //     }
    // }

    // // Collision with traps
    // for (auto trap : map->getTraps())
    // {
    //     if (player->collided(trap))
    //     {
    //         return false;
    //     }
    // }

    // // Collision with blocks
    // for (auto block : map->getBlocks())
    // {
    //     if (player->collided(block))
    //     {
    //         return false;
    //     }
    // }

    return false;
}

// CON/DES
Game::Game()
{
    initWindow();
    initWorld();
    initView();
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
    bool canMove = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        if (player->getDir() == RIGHT)
        {
            player->goBack();
        }
        player->move(-1.f, 0.f);
        canMove = handleCollisions();
        if (canMove)
        {
            player->move(1.f, 0.f);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        if (player->getDir() == LEFT)
        {
            player->goBack();
        }
        player->move(1.f, 0.f);
        canMove = handleCollisions();
        if (canMove)
        {
            player->move(-1.f, 0.f);
        }
    }
    // pakesh konnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        player->move(0.f, 1.f);
    }
    if (((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
     && player->is_jumping_finished())
     || !player->is_jumping_finished())
    {
        player->jump(0.f, -1.f);   
    }
}
void Game::updateView()
{
    // updatev view if its in background area
    if (player->getPos().x > 0 &&
        player->getPos().y > 0 &&
        player->getPos().y < worldBackground.getGlobalBounds().height &&
        player->getPos().x < worldBackground.getGlobalBounds().width)
    {
        gameView.setCenter(player->getPos());
    }
}
void Game::update()
{
    updatePollEvents();
    updateInput();
    updateView();
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

    // set view
    window->setView(gameView);

    // DRAW all things
    player->render(*window);
    map->render(*window);

    window->display();
}
