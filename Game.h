#pragma once
#include "Player.h"
#include "Map.h"
#include "Menu.h"

#define MAIN_MENU_CODE 1
#define MAP_LIST_CODE 2


class Game
{
private:
    sf::RenderWindow *window;
    MainMenu *mainMenu;
    // World
    sf::Sprite worldBackground;
    sf::Texture worldBackgroundTexture;

    // // view
    sf::View gameView;

    // PLAYER
    Player *player;
    Map *map;

    // PRIVATE FUNCS
    void initWindow();
    void initMenu();
    void initSounds();
    void initWorld();
    void initView();
    void initMap();
    void initPlayer();
    bool handleCollisions(int direction);

public:
    Game();
    virtual ~Game();

    bool canPlay;
    int curPage;
    // FUNCS
    void run();
    bool is_done();
    void updatePollEvents();
    void updateInput();
    void updateView();
    void updateGame();
    void updateMenu();
    void renderWorld();
    void renderGame();
    void renderMenu();
};