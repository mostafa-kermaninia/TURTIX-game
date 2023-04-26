#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <vector>
#define WINDOWHEIGHT 800
#define WINDOWWIDTH 1300
#define RIGHT 1
#define LEFT -1

class Map
{
private:
    sf::Texture texture;
    std::vector<sf::Sprite> sprites;
    std::vector<sf::Vector2f> moves;


    // PRIVATE FUNCS
    void initMoves();
    void initTexture();
    void initSprites();

    void moveToPos(int xMove, int yMove, sf::Sprite &sprite);

public:
    Map();
    virtual ~Map();

    // FUNCS
    void render(sf::RenderTarget &target);
};
