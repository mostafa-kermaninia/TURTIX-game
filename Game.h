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

    // PLAYER
    Player *player;
    Map *map;

    // PRIVATE FUNCS
    void initWindow();
    void initWorld();
    void initMap();
    void initPlayer();

public:
    Game();
    virtual ~Game();

    // FUNCS
    void run();

    void updatePollEvents();
    void updateInput();
    void update();
    void renderWorld();
    void render();
};