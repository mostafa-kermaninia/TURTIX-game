#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#define WINDOWHEIGHT 800
#define WINDOWWIDTH 1300
#define GROUND 3800.f
#define RIGHT 1
#define LEFT -1

class Player
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
    Player();
    virtual ~Player();

    // FUNCS
    int getDir();
    sf::Vector2f getPos(){
        return sprite.getPosition();
    }
    void move(const float dirX, const float dirY);
    void jump(const float dirX, const float dirY);
    bool collided(sf::Sprite target);
    void goBack();
    void update();
    void render(sf::RenderTarget &target);
};
