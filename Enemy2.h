#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#define RIGHT 1
#define LEFT -1
#define MOVEMENT_VALUE 50

const int CHANGE_MODE_TIME = 300;

class Enemy2
{
private:
    sf::Sprite enemy;
    sf::Texture normal_texture;
    sf::Texture freezed_texture;
    int direction;
    int state;
    float speed;
    bool stabled;
    
    bool is_change_time();

public:
    Enemy2(int offset, sf::Texture n_texture, sf::Texture f_texture);

    void set_texture(sf::Sprite new_texture);

    void move();
    void go_back();
    bool collided(sf::Sprite target);
    
    bool is_on_ground(sf::Sprite ground);
    bool is_in_world(sf::Sprite world);
    bool is_immortal();

    int get_dir();
    sf::Sprite get_sprite();
    
    void render(sf::RenderTarget &target);
};