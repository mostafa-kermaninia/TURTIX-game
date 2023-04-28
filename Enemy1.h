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

class Enemy1
{
private:
    sf::Sprite enemy;
    int direction;
    float speed; 
  
public:
    Enemy1();
    ~Enemy1();
    void set_texture(sf::Sprite new_texture);
    void move();
    void go_back();
    void render(sf::RenderTarget &target);
    int get_dir();
    bool collided(sf::Sprite target);
};