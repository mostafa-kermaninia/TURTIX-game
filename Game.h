#pragma once
#include"Player.h"

class Game
{
private:
    sf::RenderWindow *window;

    // World
    sf::Sprite worldBackground;
    sf::Texture worldBackgroundTexture;

    // PLAYER
    Player *player;

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