#include "Game.h"

// PRIVATE FUNCS
void Game::initWindow()
{
    window = new sf::RenderWindow(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "GAME SPACEEEE", sf::Style::Close | sf::Style::Titlebar);
    window->setFramerateLimit(80);
    window->setVerticalSyncEnabled(false);
}
void Game::initMenu()
{
    mainMenu = new MainMenu(window->getSize().x, window->getSize().y, curPage);
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
    std::vector<sf::Sprite> objects;
    std::vector<Enemy1 *> f_enemies = map->getFEnemies();
    for (int i = 0; i < f_enemies.size(); i++)
    {
        if (!player->is_immortal() && player->collided(f_enemies[i]->get_sprite()))
        {
            if (player->collosionType(f_enemies[i]->get_sprite(), direction) == DOWN)
            {
                map->remove_object("Enemy1", i);
                player->undo_move(DOWN);
                player->set_jumping_time(1);
                player->jump(0.f, -1.f);
            }
            else
            {
                player->change_mode();
                player->update_health();
                player->jump(0.f, -1.f);
            }
            break;
        }
    }
    // Collision with SECOND Enemies
    std::vector<Enemy2 *> s_enemies = map->getSEnemies();
    for (int i = 0; i < s_enemies.size(); i++)
    {
        if (!player->is_immortal() && player->collided(s_enemies[i]->get_sprite()))
        {
            if (player->collosionType(s_enemies[i]->get_sprite(), direction) == DOWN && !s_enemies[i]->is_immortal())
            {
                map->remove_object("Enemy2", i);
                player->undo_move(DOWN);
                player->set_jumping_time(1);
                player->jump(0.f, -1.f);
            }
            else
            {
                player->change_mode();
                player->update_health();
                player->jump(0.f, -1.f);
            }
            break;
        }
    }
    // Collision with Jailed Babies
    std::vector<BabyTurtle *> babies = map->getJailedBabies();
    for (int i = 0; i < babies.size(); i++)
    {
        if (!player->is_immortal() && player->collided(*babies[i]->get_sprite()) && babies[i]->is_jailed())
        {
            if (player->collosionType(*babies[i]->get_sprite(), direction) == DOWN)
            {
                map->free_baby(i);
                player->undo_move(DOWN);
                player->set_jumping_time(1);
                player->jump(0.f, -1.f);
            }
            else
                player->undo_move((direction + 2) % 4);
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
    canPlay = false;
    curPage = MAIN_MENU_CODE;
    initWindow();
    initMenu();
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
        while (!canPlay)
        {
            updateMenu();
            renderMenu();
        }

        updateGame();
        renderGame();
    }
}
bool Game::is_done()
{
    if (player->collided(map->getPortal()) && map->rescued_all_babies())
    {
        // std::cout << "bordiiiii\n";
        return true;
    }
    else if (!player->is_alive())
    {
        // std::cout << "mordiiiiiiiiii\n";
        // return true;
    }
    return false;
}
void Game::updatePollEvents()
{
    if (!player->is_jumping_finished())
    {
        player->jump(0.f, -1.f);
        bool canMove = handleCollisions(UP);
        if (!canMove)
        {
            player->undo_jump(0.f, 1.f);
        }
    }
    if (player->is_change_time())
        player->change_mode();
    player->gravity_effect(map->getGround());
    handleCollisions(NO_MOVE);
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
        updateInput();
    }
}
void Game::updateInput()
{
    bool canMove = true;
    if (((e.type == sf::Event::KeyPressed && (e.key.code == sf::Keyboard::W || e.key.code == sf::Keyboard::Up)) && player->is_on_ground(map->getGround())) || !player->is_jumping_finished())
    {
        player->jump(0.f, -1.f);
        canMove = handleCollisions(UP);
        if (!canMove)
        {
            player->undo_jump(0.f, 1.f);
        }
    }
    if (e.type == sf::Event::KeyPressed && (e.key.code == sf::Keyboard::A || e.key.code == sf::Keyboard::Left))
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
    if (e.type == sf::Event::KeyPressed && (e.key.code == sf::Keyboard::D || e.key.code == sf::Keyboard::Right))
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
void Game::updateGame()
{
    updatePollEvents();
    // updateInput();
    updateView();
}
void Game::updateMenu()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
        }
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                window->close();
            }
            else if (event.key.code == sf::Keyboard::Up)
            {
                mainMenu->moveUp(curPage);
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                mainMenu->moveDown(curPage);
            }
            else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
            {
                if (curPage == MAIN_MENU_CODE)
                {
                    if (mainMenu->getPressedItem() == START_INDEX)
                    {
                        curPage = MAP_LIST_CODE;
                        delete mainMenu;

                        mainMenu = new MainMenu(window->getSize().x, window->getSize().y, curPage);
                    }
                    else if (mainMenu->getPressedItem() == EXIT_INDEX)
                    {
                        window->close();
                    }
                }
                else if (curPage == MAP_LIST_CODE)
                {
                    if (mainMenu->getPressedItem() == MAP1_INDEX)
                    {
                        canPlay = true;
                    }
                    else if (mainMenu->getPressedItem() == MAP2_INDEX)
                    {
                        canPlay = true;
                    }
                    else if (mainMenu->getPressedItem() == MAP3_INDEX)
                    {
                        canPlay = true;
                    }
                    else if (mainMenu->getPressedItem() == GO_BACK_INDEX)
                    {
                        curPage = MAIN_MENU_CODE;
                        delete mainMenu;
                        mainMenu = new MainMenu(window->getSize().x, window->getSize().y, curPage);
                    }
                }
            }
        }
    }
}
void Game::renderMenu()
{
    window->clear();
    mainMenu->draw(*window, curPage);
    window->display();
}
void Game::renderWorld()
{
    window->draw(worldBackground);
}
void Game::renderGame()
{
    window->clear();
    // Draw world
    renderWorld();
    // set view
    window->setView(gameView);
    // DRAW all things
    map->render(*window);
    player->render(*window);

    window->display();
}
