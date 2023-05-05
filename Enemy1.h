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
#define MOVEMENT_VALUE 50


class Enemy1
{
private:
    sf::Sprite enemy;
    int health;
    int direction;
    float speed; 
  
public:
    Enemy1();

    void set_texture(sf::Sprite new_texture);
    void update_health();

    void move();
    void go_back();
    bool collided(sf::Sprite target);
    
    bool is_on_ground(sf::Sprite ground);
    bool is_in_world(sf::Sprite world);

    int get_dir();
    int get_health();
    sf::Sprite get_sprite();
    
    void render(sf::RenderTarget &target);
};