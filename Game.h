#pragma once
#include "Player.h"
#include "Map.h"
#include "Menu.h"

class Game
{
private:
    sf::RenderWindow *window;
    Menu *menu;
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
    void initMap(int mapCode);
    void initPlayer();
    bool handleCollisions(int direction);

public:
    Game();
    virtual ~Game();

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