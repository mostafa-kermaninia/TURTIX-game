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

#define MAX_NUM_OF_ITEMS 3
#define START_INDEX 0
#define MAPS_INDEX 1
#define EXIT_INDEX 2

class Menu
{
private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[MAX_NUM_OF_ITEMS];
    sf::Texture texture;
    sf::Sprite backGround;


public:
    Menu(float width, float height);
    ~Menu();

    void draw(sf::RenderWindow &window);
    void moveUp();
    void moveDown();
    int getPressedItem() { return selectedItemIndex; }
};
