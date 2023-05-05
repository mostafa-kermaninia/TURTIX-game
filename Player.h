#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <cmath>
#define WINDOWHEIGHT 800
#define WINDOWWIDTH 1300
#define GROUND 3800.f
#define RIGHT 1
#define LEFT -1
#define CLOSION_L 3
#define SIDES -5
#define UP 0
#define DOWN 2
#define NO_MOVE -1
#define ERROR -1

const double ACCELERATION = 0.25;
const double G_ACCELERATION = 0.01;
const int JUMP_DURATION = 56;
const int INITIAL_HEALTH = 3;
const int STAR_SCORE = 5;
const int DIAMOND_SCORE = 10;
const int IMMORTAL_TIME = 300;

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
    sf::Texture mortal_texture;
    sf::Texture immortal_texture;
    sf::Sprite sprite;

    float movement_speed;
    float jump_speed;
    int player_dir;
    int diamond_counter;
    int star_counter;
    int immortal_time_counter;
    int jump_time;
    int gravity_time;
    int health;
    int score;
    bool is_immortal_now;
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
        return {sprite.getGlobalBounds().left, sprite.getGlobalBounds().top, sprite.getGlobalBounds().left + sprite.getGlobalBounds().width, sprite.getGlobalBounds().top + sprite.getGlobalBounds().height};
    }
    sf::Vector2f getPos()
    {
        return sprite.getPosition();
    }
    void set_jumping_time(int t) { jump_time = t; }
    bool is_change_time();
    void change_mode();
    bool is_immortal();
    bool is_alive();
    bool is_jumping_finished();
    void move(const float dirX, const float dirY);
    void side_move();
    void jump(const float dirX, const float dirY);
    void undo_jump(const float dirX, const float dirY);
    bool collided(sf::Sprite target);
    int collosionType(sf::Sprite target, int direction);
    void update_score(std::string reward_name);
    void update_health();
    void goBack();
    void update();
    bool is_on_ground(std::vector<sf::Sprite> ground);
    void gravity_effect(std::vector<sf::Sprite> ground);
    bool is_falling();
    void render(sf::RenderTarget &target);
    void undo_move(int direction);
    std::pair<int, double> vertical_collosion_time(sf::Sprite target);
    double collosion_time_solver(double distance);
    std::pair<int, double> horizental_collosion_time(sf::Sprite target);
    int get_diamond_count()
    {
        return diamond_counter;
    }
    int get_star_count()
    {
        return star_counter;
    }
    int get_total_score()
    {
        return score;
    }
    int get_health(){
        return health;
    }
};
