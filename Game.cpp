#include "Game.h"

// PRIVATE FUNCS
void Game::initWindow()
{
    window = new sf::RenderWindow(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "GAME SPACEEEE", sf::Style::Close | sf::Style::Titlebar);
    window->setFramerateLimit(144);
    window->setVerticalSyncEnabled(false);
}

void Game::initSounds()
{
    // sf::SoundBuffer buffer;
    // if (!buffer.loadFromFile(""))
    // {
    //     /* code */
    // }
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
    map = new Map(worldBackground);
}
void Game::initPlayer()
{
    player = new Player();
}
bool Game::handleCollisions(int direction)
{
    // if player is in world,it can move
    // update view if its in background area
    // // // handle collision with objects
    // handle collision with objects
    std::vector<sf::Sprite> objects;
    // // Collision with PORTAL
    // if (player->collided(map->getPortal()))
    // {
    //     // return true;
    // }
    // Collision with FIRST Enemies
    std::vector<Enemy1 *> f_enemies = map->getFEnemies();
    for (int i = 0; i < f_enemies.size(); i++)
    {
        if (player->collided(f_enemies[i]->get_sprite()))
        {
            if (player->collosionType(f_enemies[i]->get_sprite(), direction) == DOWN)
            {
                map->remove_object("Enemy1", i);
            }
            else
            {
                player->update_health();
            }
            player->jump(0.f, -1.f);
            break;
        }
    }
    // Collision with SECOND Enemies
    std::vector<Enemy2 *> s_enemies = map->getSEnemies();
    for (int i = 0; i < s_enemies.size(); i++)
    {
        if (player->collided(s_enemies[i]->get_sprite()))
        {
            if (player->collosionType(s_enemies[i]->get_sprite(), direction) == DOWN)
            {
                map->remove_object("Enemy2", i);
            }
            else
            {
                player->update_health();
            }
            player->jump(0.f, -1.f);
            break;
        }
    }
    // Collision with Jailed Babies
    std::vector<BabyTurtle *> babies = map->getJailedBabies();
    for (int i = 0; i < babies.size(); i++)
    {
        if (player->collided(*babies[i]->get_sprite()) && babies[i]->is_jailed())
        {
            map->free_baby(i);
        }
    }
    // Collision with stars
    objects = map->getStars();
    for (int i = 0; i < objects.size(); i++)
    {
        if (player->collided(objects[i]))
        {
            map->remove_object("star", i);
            player->update_score("star");
        }
    }
    // Collision with diamonds
    objects = map->getDiamonds();
    for (int i = 0; i < objects.size(); i++)
    {
        if (player->collided(objects[i]))
        {
            map->remove_object("diamond", i);
            player->update_score("diamond");
        }
    }
    // Collision with ground
    for (auto groundPart : map->getGround())
    {
        if (player->collided(groundPart))
        {
            return false;
        }
    }
    // Collision with traps
    for (auto trap : map->getTraps())
    {
        if (player->collided(trap))
        {
            player->update_health();
        }
    }
    // Collision with blocks
    for (auto block : map->getBlocks())
    {
        if (player->collided(block))
        {
            return false;
        }
    }
    if (player->getEdges()[LEFT_INDEX] > worldBackground.getGlobalBounds().left &&
        player->getEdges()[UP_INDEX] > worldBackground.getGlobalBounds().top &&
        player->getEdges()[RIGHT_INDEX] < worldBackground.getGlobalBounds().left + worldBackground.getGlobalBounds().width &&
        player->getEdges()[DOWM_INDEX] < worldBackground.getGlobalBounds().top + worldBackground.getGlobalBounds().height)
    {
        return true;
    }
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
    while (window->isOpen() && !is_done())
    {
        update();
        render();
    }
}

bool Game::is_done()
{
    if (player->collided(map->getPortal()) && map->rescued_all_babies())
    {
        std::cout << "bordiiiii\n"; 
        return true;
    }
    else if (!player->is_alive())
    {
        std::cout << "mordiiiiiiiiii\n";
        // return true;
    }
    return false;
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
    handleCollisions(NO_MOVE);
    // Move Player
    bool canMove = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        if (player->getDir() == RIGHT)
        {
            player->goBack();
        }
        player->move(-1.f, 0.f);
        canMove = handleCollisions(LEFT);
        if (!canMove)
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
        canMove = handleCollisions(RIGHT);
        if (!canMove)
        {
            player->move(-1.f, 0.f);
        }
    }
    // pakesh konnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        player->move(0.f, 1.f);
        canMove = handleCollisions(DOWN);
        if (!canMove)
        {
            player->move(0.f, -1.f);
        }
    }
    if (((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) && player->is_jumping_finished()) || !player->is_jumping_finished())
    {
        player->jump(0.f, -1.f);
        canMove = handleCollisions(UP);
        if (!canMove)
        {
            player->undo_jump(0.f, 1.f);
        }
    }
}
void Game::updateView()
{
    float x = player->getPos().x;
    float y = player->getPos().y;
    x = std::max(x, worldBackground.getGlobalBounds().left + WINDOWWIDTH / 2.f);
    x = std::min(x, worldBackground.getGlobalBounds().left + worldBackground.getGlobalBounds().width - WINDOWWIDTH / 2.f);
    y = std::min(y, worldBackground.getGlobalBounds().top + worldBackground.getGlobalBounds().height - WINDOWHEIGHT / 2.f);
    y = std::max(y, worldBackground.getGlobalBounds().top + WINDOWHEIGHT / 2.f);
    gameView.setCenter(x, y);
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
    map->render(*window);
    player->render(*window);

    window->display();
}
