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

const int CHANGE_MODE_TIME = 300;

class Enemy2
{
private:
    sf::Sprite enemy;
    sf::Texture normal_texture;
    sf::Texture freezed_texture;
    int direction;
    float speed;
    int state;
    bool stabled;
    
    bool is_change_time();

public:
    Enemy2(int offset, sf::Texture n_texture, sf::Texture f_texture);
    ~Enemy2();
    void set_texture(sf::Sprite new_texture);
    void move();
    bool is_on_ground(sf::Sprite ground);
    void go_back();
    void render(sf::RenderTarget &target);
    int get_dir();
    bool collided(sf::Sprite target);
    bool is_in_world(sf::Sprite world);
    bool is_immortal() { return stabled; }

    sf::Sprite get_sprite() { return enemy; }
};