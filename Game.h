#pragma once
#include "Player.h"
#include "Map.h"
#include "Menu.h"


class Game
{
private:
    sf::View default_view;
    sf::Event e;
    sf::RenderWindow *window;
    Menu *menu;
    // World
    sf::Sprite worldBackground;
    sf::Texture worldBackgroundTexture;
    sf::Font font;
    std::vector<sf::Text> scoreInfo;

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
    void initScore();
    void initMap(int mapCode);
    void initPlayer();
    bool is_in_game();
    bool handleCollisions(int direction);
    std::string make_heart(int count);


public:
    Game();
    virtual ~Game();

    int curPage;
    // FUNCS
    void run();
    void check_end_game();
    void updatePollEvents();
    void updateInput();
    void updateView();
    void updateGame();
    void updateMenu();
    void updateScore();
    void renderWorld();
    void renderGame();
    void renderMenu();
    void renderScore();
};