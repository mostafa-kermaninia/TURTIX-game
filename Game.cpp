#include "Game.h"

// PRIVATE FUNCS
void Game::initWindow()
{
    window = new sf::RenderWindow(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "GAME SPACEEEE", sf::Style::Close | sf::Style::Titlebar);
    window->setFramerateLimit(80);
    window->setVerticalSyncEnabled(false);
    default_view = window->getDefaultView();
}
void Game::initMenu()
{
    menu = new Menu(window->getSize().x, window->getSize().y, curPage);
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

    float scaleHeight = 0.1;
    float scaleWidth = 0.1;
    worldBackground.setScale(0.5, 0.5);
}
void Game::initView()
{
    gameView = sf::View((sf::FloatRect(WINDOWWIDTH, WINDOWWIDTH, WINDOWWIDTH, WINDOWHEIGHT)));
}
void Game::initScore()
{
    font.loadFromFile("Fonts/Premier.ttf");
    std::vector<sf::Text> finalVec(6);
    for (int i = 0; i < finalVec.size(); i++)
    {
        finalVec[i].setFont(font);
        finalVec[i].scale(0.8f, 0.8f);
        finalVec[i].setFillColor(sf::Color::Black);
        finalVec[i].setFillColor(sf::Color::Magenta);
        finalVec[i].setOutlineColor(sf::Color::Black);
        finalVec[i].setOutlineThickness(5.f);
    }
    scoreInfo = finalVec;
}
void Game::initMap(int mapCode)
{
    map = new Map(worldBackground, mapCode);
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
    // canPlay = false;
    curPage = MAIN_MENU_CODE;
    initWindow();
    initMenu();
    initWorld();
    initView();
    initPlayer();
    initScore();
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
        check_end_game();
        switch (curPage)
        {
        case MAIN_MENU_CODE:
            updateMenu();
            renderMenu();
            break;
        case MAP_LIST_CODE:
            updateMenu();
            renderMenu();
            break;
        case MAP1_CODE:
            updateGame();
            renderGame();
            break;
        case MAP2_CODE:
            updateGame();
            renderGame();
            break;
        case MAP3_CODE:
            updateGame();
            renderGame();
            break;
        case WIN_PAGE_CODE:
            window->setView(default_view);
            renderMenu();
            updateMenu();
            break;
        case LOSE_PAGE_CODE:
            window->setView(default_view);
            updateMenu();
            renderMenu();
            break;
        }
    }
}

bool Game::is_in_game()
{
    return curPage == MAP1_CODE || curPage == MAP2_CODE || curPage == MAP3_CODE;
}
void Game::check_end_game()
{
    if ((is_in_game() && player->collided(map->getPortal()) && map->rescued_all_babies()))
    {
        curPage = WIN_PAGE_CODE;
        delete menu;
        menu = new Menu(window->getSize().x, window->getSize().y, curPage);
    }
    else if (!player->is_alive() && is_in_game())
    {
        // curPage = WIN_PAGE_CODE;
        curPage = LOSE_PAGE_CODE;
        delete menu;
        menu = new Menu(window->getPosition().x, window->getPosition().y, curPage);
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
    if (player->is_change_time())
        player->change_mode();
    player->gravity_effect(map->getGround());
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
    if (((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) && player->is_on_ground(map->getGround())) || !player->is_jumping_finished())
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
void Game::updateGame()
{
    updatePollEvents();
    updateInput();
    updateView();
    updateScore();
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
        }
        if (event.type == sf::Event::MouseMoved)
        {
            if (curPage == MAIN_MENU_CODE)
            {
                for (int i = 0; i < menu->getMenu().size(); i++)
                {
                    if (menu->getMenu()[i].getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
                    {
                        menu->mouseOn(curPage, i);
                    }
                    else
                    {
                        menu->mouseOut(curPage, i);
                    }
                }
            }
            else if (curPage == MAP_LIST_CODE)
            {
                for (int i = 0; i < menu->getList().size(); i++)
                {
                    if (menu->getList()[i].getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
                    {
                        menu->mouseOn(curPage, i);
                    }
                    else
                    {
                        menu->mouseOut(curPage, i);
                    }
                }
            }
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            int selected = DEFAULT;
            switch (curPage)
            {
            case MAIN_MENU_CODE:
            {
                for (int i = 0; i < menu->getMenu().size(); i++)
                {
                    if (menu->getMenu()[i].getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
                    {
                        selected = i;
                    }
                }

                if (selected == START_INDEX)
                {
                    curPage = MAP_LIST_CODE;

                    delete menu;
                    menu = new Menu(window->getSize().x, window->getSize().y, curPage);
                }
                else if (selected == EXIT_INDEX)
                {
                    window->close();
                }
                break;
            }
            case MAP_LIST_CODE:
            {
                for (int i = 0; i < menu->getList().size(); i++)
                {
                    if (menu->getList()[i].getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
                    {
                        selected = i;
                    }
                }

                if (selected == MAP1_INDEX)
                {
                    curPage = MAP1_CODE;
                    initMap(MAP1_CODE);
                }
                else if (selected == MAP2_INDEX)
                {
                    curPage = MAP2_CODE;
                    initMap(MAP2_CODE);
                }
                else if (selected == MAP3_INDEX)
                {
                    curPage = MAP3_CODE;
                    initMap(MAP3_CODE);
                }
                else if (selected == GO_BACK_INDEX)
                {
                    curPage = MAIN_MENU_CODE;
                    delete menu;
                    menu = new Menu(window->getSize().x, window->getSize().y, curPage);
                }
                break;
            }
            case WIN_PAGE_CODE:
            {
                curPage = MAP_LIST_CODE;
                delete menu;
                menu = new Menu(window->getSize().x, window->getSize().y, curPage);
                break;
            }
            case LOSE_PAGE_CODE:
            {
                curPage = MAP_LIST_CODE;
                delete menu;
                menu = new Menu(window->getSize().x, window->getSize().y, curPage);
                break;
            }
            }
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            int selected = DEFAULT;
            switch (curPage)
            {
            case MAIN_MENU_CODE:
            {
                for (int i = 0; i < menu->getMenu().size(); i++)
                {
                    if (menu->getMenu()[i].getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
                    {
                        selected = i;
                    }
                }

                if (selected == START_INDEX)
                {
                    curPage = MAP_LIST_CODE;

                    delete menu;
                    menu = new Menu(window->getSize().x, window->getSize().y, curPage);
                }
                else if (selected == EXIT_INDEX)
                {
                    window->close();
                }
                break;
            }
            case MAP_LIST_CODE:
            {
                for (int i = 0; i < menu->getList().size(); i++)
                {
                    if (menu->getList()[i].getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
                    {
                        selected = i;
                    }
                }

                if (selected == MAP1_INDEX)
                {
                    curPage = MAP1_CODE;
                    initMap(MAP1_CODE);
                }
                else if (selected == MAP2_INDEX)
                {
                    curPage = MAP2_CODE;
                    initMap(MAP2_CODE);
                }
                else if (selected == MAP3_INDEX)
                {
                    curPage = MAP3_CODE;
                    initMap(MAP3_CODE);
                }
                else if (selected == GO_BACK_INDEX)
                {
                    curPage = MAIN_MENU_CODE;
                    delete menu;
                    menu = new Menu(window->getSize().x, window->getSize().y, curPage);
                }
                break;
            }
            case WIN_PAGE_CODE:
            {
                curPage = MAP_LIST_CODE;
                delete menu;
                menu = new Menu(window->getSize().x, window->getSize().y, curPage);
                break;
            }
            case LOSE_PAGE_CODE:
            {
                curPage = MAP_LIST_CODE;
                delete menu;
                menu = new Menu(window->getSize().x, window->getSize().y, curPage);
                break;
            }
            }
        }
    }
}
void Game::updateScore()
{
    scoreInfo[0].setString("DIAMONDS (*10) :");
    scoreInfo[1].setString(std::to_string(player->get_diamond_count()));
    scoreInfo[2].setString("STARS (*5) :");
    scoreInfo[3].setString(std::to_string(player->get_star_count()));
    scoreInfo[4].setString("TOTAL SCORE :");
    scoreInfo[5].setString(std::to_string(player->get_total_score()));

    for (int i = 0; i < scoreInfo.size(); i++)
    {
        scoreInfo[i].setPosition(window->getView().getCenter().x - window->getView().getSize().x / 2.f + 10.f, window->getView().getCenter().y - window->getView().getSize().y / 2.f + 30 * i + 10.f);
    }
}
void Game::renderMenu()
{
    window->clear();
    menu->draw(*window, curPage);
    window->display();
}
void Game::renderScore()
{
    for (auto text : scoreInfo)
    {
        window->draw(text);
    }
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
    renderScore();

    window->display();
}
