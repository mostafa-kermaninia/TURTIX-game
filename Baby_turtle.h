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

class BabyTurtle
{
private:
    sf::Sprite baby;
    bool is_free;
    int direction;
    float speed; 

public:
    BabyTurtle();
    ~BabyTurtle();
    void make_free(sf::Sprite free_baby_sprite);
    void set_texture(sf::Sprite new_texture);
    void move();
    void go_back();
    void render(sf::RenderTarget &target);
    int get_dir();
    bool collided(sf::Sprite target);
    bool is_in_world(sf::Sprite world);
    bool is_jailed() { return !is_free; }
    sf::Sprite get_sprite() { return baby; }
};