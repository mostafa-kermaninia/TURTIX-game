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
#define DEFAULT -1

#define MAIN_MENU 1
#define LIST_MENU 2

#define MAP1_INDEX 0
#define MAP2_INDEX 1
#define MAP3_INDEX 2
#define GO_BACK_INDEX 3

enum PAGES
{
    MAP1_CODE,
    MAP2_CODE,
    MAP3_CODE,
    MAIN_MENU_CODE,
    MAP_LIST_CODE,
    LOSE_PAGE_CODE,
    WIN_PAGE_CODE

};

class Menu
{
private:
    int selectedItemIndex;
    sf::Font font;
    
    sf::Text menu[NUM_OF_MAIN_ITEMS];
    sf::Text list[NUM_OF_LIST_ITEMS];
    
    sf::Texture mainTexture;
    sf::Texture listTexture;
    sf::Texture winPageTexture;
    sf::Texture losePageTexture;
    
    sf::Sprite mainBackground;
    sf::Sprite listBackground;
    sf::Sprite winPageBackground;
    sf::Sprite losePageBackground;
public:
    Menu(float width, float height, int menuType);
    ~Menu();

    void initMainMenu(float width, float height);
    void initListMenu(float width, float height);
    void initWinPage(float width, float height);
    void initLosePage(float width, float height);
    void draw(sf::RenderWindow &window, int menuType);
    void mouseOn(int menuType,int textIndex);
    void mouseOut(int menuType,int textIndex);
    void setSelectedItem(int index) { selectedItemIndex = index;}
    int getSelectedItem() { return selectedItemIndex; }
    void initFont();
    std::vector<sf::Text> getMenu();
    std::vector<sf::Text> getList();

};