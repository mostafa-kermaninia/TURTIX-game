#include "Menu.h"

Menu::Menu(float width, float height)
{
    if (!font.loadFromFile("Fonts\\Ignorant.ttf"))
    {
        // handle Errors
    }

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Green);
    menu[0].setString("play");
    menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUM_OF_ITEMS + 1) * 1));
    menu[0].scale(5.f, 5.f);

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::Yellow);
    menu[1].setString("options");
    menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUM_OF_ITEMS + 1) * 2));
    menu[1].scale(5.f, 5.f);

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::Red);
    menu[2].setString("exit");
    menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUM_OF_ITEMS + 1) * 3));
    menu[2].scale(5.f, 5.f);
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < MAX_NUM_OF_ITEMS; i++)
    {
        window.draw(menu[i]);
    }
}

void Menu::moveUp()
{
}

void Menu::moveDown()
{
}
