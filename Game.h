#pragma once
#include "Player.h"
#include "Map.h"

class Game
{
private:
    sf::RenderWindow *window;

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
    void initWorld();
    void initView();
    void initMap();
    void initPlayer();
    bool handleCollisions(int direction);
public:
    Game();
    virtual ~Game();

    // FUNCS
    void run();

    void updatePollEvents();
    void updateInput();
    void updateView();
    void update();
    void renderWorld();
    void render();
    
};