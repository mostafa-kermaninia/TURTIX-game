#include "Menu.h"

Menu::Menu(float width, float height)
{
    if (!font.loadFromFile("Fonts\\Ignorant.ttf"))
    {
        // handle Errors
    }

    menu[START_INDEX].setFont(font);
    menu[START_INDEX].setFillColor(sf::Color::Red);
    menu[START_INDEX].setString("PLAY");
    menu[START_INDEX].setPosition(sf::Vector2f(width / 2, height / (MAX_NUM_OF_ITEMS + 1) * 1));
    menu[START_INDEX].scale(5.f, 5.f);

    menu[MAPS_INDEX].setFont(font);
    menu[MAPS_INDEX].setFillColor(sf::Color::Black);
    menu[MAPS_INDEX].setString("MAPS");
    menu[MAPS_INDEX].setPosition(sf::Vector2f(width / 2, height / (MAX_NUM_OF_ITEMS + 1) * 2));
    menu[MAPS_INDEX].scale(5.f, 5.f);

    menu[EXIT_INDEX].setFont(font);
    menu[EXIT_INDEX].setFillColor(sf::Color::Black);
    menu[EXIT_INDEX].setString("EXIT");
    menu[EXIT_INDEX].setPosition(sf::Vector2f(width / 2, height / (MAX_NUM_OF_ITEMS + 1) * 3));
    menu[EXIT_INDEX].scale(5.f, 5.f);

    selectedItemIndex = START_INDEX;

    // LOAD TEXTURE FROM FILE
    if (!texture.loadFromFile("Textures/MenuBackground.png"))
    {
        std::cout << "ERROR::PLAYER::INITTEXTURE:: FILE RO NASHOD BEKHUNAMMMM!!! " << std::endl;
    }
    backGround.setTexture(texture);
    backGround.scale(1.1f,1.15f);
}
Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow &window)
{
    window.draw(backGround);
    for (int i = 0; i < MAX_NUM_OF_ITEMS; i++)
    {
        window.draw(menu[i]);
    }
}
void Menu::moveUp()
{
    if (selectedItemIndex - 1 >= 0)
    {
        menu[selectedItemIndex].setFillColor(sf::Color::Black);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}
void Menu::moveDown()
{
    if (selectedItemIndex + 1 < MAX_NUM_OF_ITEMS)
    {
        menu[selectedItemIndex].setFillColor(sf::Color::Black);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}
