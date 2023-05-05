#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define RIGHT 1
#define LEFT -1
#define ACCELERATION 0.15

class BabyTurtle
{
private:
    sf::Sprite baby;
    std::vector<sf::Sprite> ground_parts;
    bool is_free;
    bool is_on_ground;
    int direction;
    int fall_time;
    float speed;

public:
    BabyTurtle(std::vector<sf::Sprite> g_parts);

    void set_texture(sf::Sprite new_texture);
    void set_fall_time(int t);
    void set_on_ground(bool og);
    void update_fall_time();
    
    void make_free(sf::Sprite free_baby_sprite);
    void move();
    void move_back();
    void go_back();
    bool collided(sf::Sprite target);

    bool is_in_world(sf::Sprite world);
    bool is_jailed();
    bool is_it_on_ground();

    int get_dir();
    sf::Sprite *get_sprite();
    int get_fall_time();

    void render(sf::RenderTarget &target);
};