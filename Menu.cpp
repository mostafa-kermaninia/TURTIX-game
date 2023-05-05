#include "Menu.h"

MainMenu::MainMenu(float width, float height, int menuType)
{
    if (!font.loadFromFile("Fonts/Ignorant.ttf"))
    {
        // handle Errors
    }
    if (menuType == MAIN_MENU)
    {
        menu[START_INDEX].setFont(font);
        menu[START_INDEX].setFillColor(sf::Color::Red);
        menu[START_INDEX].setString("PLAY");
        menu[START_INDEX].setPosition(sf::Vector2f(width / 2, height / (NUM_OF_MAIN_ITEMS + 1) * 1));
        menu[START_INDEX].scale(5.f, 5.f);

        menu[EXIT_INDEX].setFont(font);
        menu[EXIT_INDEX].setFillColor(sf::Color::Black);
        menu[EXIT_INDEX].setString("EXIT");
        menu[EXIT_INDEX].setPosition(sf::Vector2f(width / 2, height / (NUM_OF_MAIN_ITEMS + 1) * 2));
        menu[EXIT_INDEX].scale(5.f, 5.f);

        selectedItemIndex = START_INDEX;

        // LOAD TEXTURE FROM FILE
        if (!mainTexture.loadFromFile("Textures/MainMenuBackground.png"))
        {
            std::cout << "ERROR::PLAYER::INITTEXTURE:: FILE RO NASHOD BEKHUNAMMMM!!! " << std::endl;
        }
        mainBackground.setTexture(mainTexture);
        mainBackground.scale(0.8f, 0.8f);
        mainBackground.move(-30,0);
    }
    else if (menuType == LIST_MENU)
    {
        list[MAP1_INDEX].setFont(font);
        list[MAP1_INDEX].setFillColor(sf::Color::Magenta);
        list[MAP1_INDEX].setString("EASY MAP");
        list[MAP1_INDEX].setPosition(sf::Vector2f(width / 6, height / (NUM_OF_LIST_ITEMS + 1) * 1));
        list[MAP1_INDEX].scale(3.f, 3.f);

        list[MAP2_INDEX].setFont(font);
        list[MAP2_INDEX].setFillColor(sf::Color(128, 128, 128));
        list[MAP2_INDEX].setString("NORMAL MAP");
        list[MAP2_INDEX].setPosition(sf::Vector2f(width / 6, height / (NUM_OF_LIST_ITEMS + 1) * 2));
        list[MAP2_INDEX].scale(3.f, 3.f);

        list[MAP3_INDEX].setFont(font);
        list[MAP3_INDEX].setFillColor(sf::Color(128, 128, 128));
        list[MAP3_INDEX].setString("HARD MAP");
        list[MAP3_INDEX].setPosition(sf::Vector2f(width / 6, height / (NUM_OF_LIST_ITEMS + 1) * 3));
        list[MAP3_INDEX].scale(3.f, 3.f);

        list[GO_BACK_INDEX].setFont(font);
        list[GO_BACK_INDEX].setFillColor(sf::Color(128, 128, 128));
        list[GO_BACK_INDEX].setString("GO BACK");
        list[GO_BACK_INDEX].setPosition(sf::Vector2f(width / 8, height / (NUM_OF_LIST_ITEMS + 1) * 4));
        list[GO_BACK_INDEX].scale(2.f, 2.f);

        selectedItemIndex = MAP1_INDEX;

        // LOAD TEXTURE FROM FILE
        if (!listTexture.loadFromFile("Textures/ListMenuBachground.png"))
        {
            std::cout << "ERROR::PLAYER::INITTEXTURE:: FILE RO NASHOD BEKHUNAMMMM!!! " << std::endl;
        }
        listBackground.setTexture(listTexture);
        listBackground.scale(0.8f, 0.8f);
        listBackground.move(-30,0);

    }
}
MainMenu::~MainMenu()
{
}

void MainMenu::draw(sf::RenderWindow &window, int menuType)
{
    if (menuType == MAIN_MENU)
    {
        window.draw(mainBackground);
        for (int i = 0; i < NUM_OF_MAIN_ITEMS; i++)
        {
            window.draw(menu[i]);
        }
    }
    else if (menuType == LIST_MENU)
    {
        window.draw(listBackground);
        for (int i = 0; i < NUM_OF_LIST_ITEMS; i++)
        {
            window.draw(list[i]);
        }
    }
}
void MainMenu::moveUp(int menuType)
{
    if (menuType == MAIN_MENU)

    {
        if (selectedItemIndex - 1 >= 0)
        {
            menu[selectedItemIndex].setFillColor(sf::Color::Black);
            selectedItemIndex--;
            menu[selectedItemIndex].setFillColor(sf::Color::Red);
        }
    }
    else if (menuType == LIST_MENU)
    {
        if (selectedItemIndex - 1 >= 0)
        {
            list[selectedItemIndex].setFillColor(sf::Color(128, 128, 128));
            selectedItemIndex--;
            list[selectedItemIndex].setFillColor(sf::Color::Magenta);
        }
    }
}
void MainMenu::moveDown(int menuType)
{
    if (menuType == MAIN_MENU)
    {
        if (selectedItemIndex + 1 < NUM_OF_MAIN_ITEMS)
        {
            menu[selectedItemIndex].setFillColor(sf::Color::Black);
            selectedItemIndex++;
            menu[selectedItemIndex].setFillColor(sf::Color::Red);
        }
    }
    else if (menuType == LIST_MENU)
    {
        if (selectedItemIndex + 1 < NUM_OF_LIST_ITEMS)
        {
            list[selectedItemIndex].setFillColor(sf::Color(128, 128, 128));
            selectedItemIndex++;
            list[selectedItemIndex].setFillColor(sf::Color::Magenta);
        }
    }
}
