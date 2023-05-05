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

#define NUM_OF_MAIN_ITEMS 2
#define NUM_OF_LIST_ITEMS 4
#define START_INDEX 0
#define EXIT_INDEX 1

#define MAIN_MENU 1
#define LIST_MENU 2

#define MAP1_INDEX 0
#define MAP2_INDEX 1
#define MAP3_INDEX 2
#define GO_BACK_INDEX 3

class MainMenu
{
private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[NUM_OF_MAIN_ITEMS];
    sf::Text list[NUM_OF_LIST_ITEMS];
    sf::Texture mainTexture;
    sf::Texture listTexture;
    sf::Sprite mainBackground;
    sf::Sprite listBackground;

public:
    MainMenu(float width, float height, int menuType);
    ~MainMenu();

    void draw(sf::RenderWindow &window, int menuType);
    void moveUp(int menuType);
    void moveDown(int menuType);
    int getPressedItem() { return selectedItemIndex; }
};
