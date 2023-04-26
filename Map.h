#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
const int WINDOWHEIGHT = 800;
const int WINDOWWIDTH = 1300;
const int RIGHT = 1;
const int LEFT = -1;
class Map
{
private:
    sf::Texture texture;
    sf::Sprite sprite;

    float movementSpeed;
    int playerDir;

    // PRIVATE FUNCS
    void initTexture();
    void initSprite();

public:
    Map();
    virtual ~Map();

    // FUNCS
    int getDir();

    void move(const float dirX, const float dirY);
    bool collided(sf::Sprite target);
    void goBack();
    void update();
    void render(sf::RenderTarget &target);
};
