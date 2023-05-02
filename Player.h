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
#define SIDES 0
#define TOP 1
#define ERROR -1



const double ACCELERATION = 0.25;
const int JUMP_DURATION = 80;
const int INITIAL_HEALTH = 3;
const int STAR_SCORE = 5;
const int DIAMOND_SCORE = 10;

enum INDEX
{
    LEFT_INDEX,
    UP_INDEX,
    RIGHT_INDEX,
    DOWM_INDEX
};

class Player
{
private:
    sf::Texture texture;
    sf::Sprite sprite;

    float movement_speed;
    float jump_speed;
    int player_dir;

    bool is_in_air;
    int jump_time;
    int health;
    int score;
    // PRIVATE FUNCS
    void initTexture();
    void initSprite();

public:
    Player();
    virtual ~Player();

    // FUNCS
    int getDir();
    std::vector<float> getEdges()
    {
        return {
            sprite.getGlobalBounds().left, sprite.getGlobalBounds().top, sprite.getGlobalBounds().left + sprite.getGlobalBounds().width, sprite.getGlobalBounds().top + sprite.getGlobalBounds().height};
    }
    sf::Vector2f getPos()
    {
        return sprite.getPosition();
    }

    bool is_jumping_finished();
    void move(const float dirX, const float dirY);
    void jump(const float dirX, const float dirY);
    void undo_jump(const float dirX, const float dirY);
    bool collided(sf::Sprite target);
    int collotionType(sf::Sprite target);
    void update_score(std::string reward_name);
    void update_health();
    void goBack();
    void update();
    void render(sf::RenderTarget &target);
};
