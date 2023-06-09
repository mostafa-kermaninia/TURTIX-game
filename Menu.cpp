#include "Menu.h"

Menu::Menu(float width, float height, int menuCode, int totalScore, int diamonds, int stars)
{
    initFont();
    switch (menuCode)
    {
    case MAIN_MENU_CODE:
        initMainMenu(width, height);
        break;
    case MAP_LIST_CODE:
        initListMenu(width, height);
        break;
    case WIN_PAGE_CODE:
        initWinPage(width, height, totalScore, diamonds, stars);
        break;
    case LOSE_PAGE_CODE:
        initLosePage(width, height, totalScore, diamonds, stars);
        break;
    }
}
void Menu::initFont()
{
    if (!font.loadFromFile("Fonts/Ignorant.ttf"))
    {
        std::cerr << "COULDN'T READ FONT!\n";
    }
}
void Menu::initMainMenu(float width, float height)
{
    menu[START_INDEX].setFont(font);
    menu[START_INDEX].setFillColor(sf::Color::Black);
    menu[START_INDEX].setString("PLAY");
    menu[START_INDEX].setPosition(sf::Vector2f(width / 2, height / (NUM_OF_MAIN_ITEMS + 3) * 1));
    menu[START_INDEX].scale(5.0f, 5.0f);

    menu[EXIT_INDEX].setFont(font);
    menu[EXIT_INDEX].setFillColor(sf::Color::Black);
    menu[EXIT_INDEX].setString("EXIT");
    menu[EXIT_INDEX].setPosition(sf::Vector2f(width / 2, height / (NUM_OF_MAIN_ITEMS + 2) * 2));
    menu[EXIT_INDEX].scale(4.5f, 4.5f);

    selectedItemIndex = START_INDEX;

    // LOAD TEXTURE FROM FILE
    if (!mainTexture.loadFromFile("Textures/MainMenuBackground.png"))
    {
        std::cout << "ERROR::PLAYER::INITTEXTURE:: FILE RO NASHOD BEKHUNAMMMM!!! " << std::endl;
    }
    mainBackground.setTexture(mainTexture);
    mainBackground.scale(0.8f, 0.8f);
    mainBackground.move(-30, 0);
}
void Menu::initListMenu(float width, float height)
{
    list[MAP1_INDEX].setFont(font);
    list[MAP1_INDEX].setFillColor(sf::Color(128, 128, 128));
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
    listBackground.move(-30, 0);
}
void Menu::initWinPage(float width, float height, int totalScore, int diamonds, int stars)
{
    std::vector<sf::Text> finalVec(NUM_OF_PAGE_ITEMS);

    finalVec[TOTAL_SCORE_INDEX].setFont(font);
    finalVec[TOTAL_SCORE_INDEX].setFillColor(sf::Color::Black);
    finalVec[TOTAL_SCORE_INDEX].setString(std::to_string(totalScore));
    finalVec[TOTAL_SCORE_INDEX].setPosition(sf::Vector2f(width / 1.83, height / (NUM_OF_PAGE_ITEMS)*1.5));
    finalVec[TOTAL_SCORE_INDEX].scale(1.0f, 1.0f);

    finalVec[STARS_INDEX].setFont(font);
    finalVec[STARS_INDEX].setFillColor(sf::Color::Black);
    finalVec[STARS_INDEX].setString(std::to_string(stars));
    finalVec[STARS_INDEX].setPosition(sf::Vector2f(width / 1.83, height / (NUM_OF_PAGE_ITEMS)*1.85));
    finalVec[STARS_INDEX].scale(1.0f, 1.0f);

    finalVec[DIAMONDS_INDEX].setFont(font);
    finalVec[DIAMONDS_INDEX].setFillColor(sf::Color::Black);
    finalVec[DIAMONDS_INDEX].setString(std::to_string(diamonds));
    finalVec[DIAMONDS_INDEX].setPosition(sf::Vector2f(width / 1.83, height / (NUM_OF_PAGE_ITEMS)*2.06));
    finalVec[DIAMONDS_INDEX].scale(1.0f, 1.0f);

    winPage = finalVec;
    // LOAD TEXTURE FROM FILE
    if (!winPageTexture.loadFromFile("Textures/WinGame.png"))
    {
        std::cout << "ERROR::PLAYER::INITTEXTURE:: FILE RO NASHOD BEKHUNAMMMM!!! " << std::endl;
    }
    winPageBackground.setTexture(winPageTexture);
    winPageBackground.scale(1.2f, 1.2f);
    winPageBackground.setPosition(sf::Vector2f(0.0f, 0.0f));
    winPageBackground.move(-70.f, 0.f);
}
void Menu::initLosePage(float width, float height, int totalScore, int diamonds, int stars)
{
    std::vector<sf::Text> finalVec(NUM_OF_PAGE_ITEMS);

    finalVec[TOTAL_SCORE_INDEX].setFont(font);
    finalVec[TOTAL_SCORE_INDEX].setFillColor(sf::Color::Black);
    finalVec[TOTAL_SCORE_INDEX].setString(std::to_string(totalScore));
    finalVec[TOTAL_SCORE_INDEX].setPosition(sf::Vector2f(width * 2.05f, height * 2.83));
    finalVec[TOTAL_SCORE_INDEX].scale(1.0f, 1.0f);

    finalVec[STARS_INDEX].setFont(font);
    finalVec[STARS_INDEX].setFillColor(sf::Color::Black);
    finalVec[STARS_INDEX].setString(std::to_string(stars));
    finalVec[STARS_INDEX].setPosition(sf::Vector2f(width * 2.08f, height * 3.38));
    finalVec[STARS_INDEX].scale(1.0f, 1.0f);

    finalVec[DIAMONDS_INDEX].setFont(font);
    finalVec[DIAMONDS_INDEX].setFillColor(sf::Color::Black);
    finalVec[DIAMONDS_INDEX].setString(std::to_string(diamonds));
    finalVec[DIAMONDS_INDEX].setPosition(sf::Vector2f(width * 2.08f, height * 3.69));
    finalVec[DIAMONDS_INDEX].scale(1.0f, 1.0f);

    losePage = finalVec;

    // LOAD TEXTURE FROM FILE
    if (!losePageTexture.loadFromFile("Textures/LoseGame.png"))
    {
        std::cout << "ERROR::PLAYER::INITTEXTURE:: FILE RO NASHOD BEKHUNAMMMM!!! " << std::endl;
    }
    losePageBackground.setTexture(losePageTexture);
    losePageBackground.scale(1.f, 1.f);
    losePageBackground.setPosition(65, 60);

    losePageBackground.move(-70.f, 0.f);
}
std::vector<sf::Text> Menu::getMenu()
{
    int n = sizeof(menu) / sizeof(menu[0]);

    std::vector<sf::Text> res(menu, menu + n);
    return res;
}
std::vector<sf::Text> Menu::getList()
{
    int n = sizeof(list) / sizeof(list[0]);

    std::vector<sf::Text> res(list, list + n);
    return res;
}
void Menu::draw(sf::RenderWindow &window, int curPage)
{
    switch (curPage)
    {
    case MAIN_MENU_CODE:
        window.draw(mainBackground);
        for (int i = 0; i < NUM_OF_MAIN_ITEMS; i++)
        {
            window.draw(menu[i]);
        }
        break;
    case MAP_LIST_CODE:
        window.draw(listBackground);
        for (int i = 0; i < NUM_OF_LIST_ITEMS; i++)
        {
            window.draw(list[i]);
        }
        break;
    case WIN_PAGE_CODE:
        window.draw(winPageBackground);
        for (int i = 0; i < NUM_OF_PAGE_ITEMS; i++)
        {
            window.draw(winPage[i]);
        }
        break;
    case LOSE_PAGE_CODE:
        window.draw(losePageBackground);
        for (int i = 0; i < NUM_OF_PAGE_ITEMS; i++)
        {
            window.draw(losePage[i]);
        }
        break;
    }
}
void Menu::mouseOn(int menuCode, int textIndex)
{
    if (menuCode == MAIN_MENU_CODE)
    {
        menu[textIndex].setFillColor(sf::Color::Red);
        menu[textIndex].setScale(5.0f, 5.0f);
    }
    else if (menuCode == MAP_LIST_CODE)
    {
        list[textIndex].setFillColor(sf::Color::Magenta);
        list[textIndex].setOutlineColor(sf::Color::Black);
        list[textIndex].setOutlineThickness(5.f);
    }
}
void Menu::mouseOut(int menuCode, int textIndex)
{
    if (menuCode == MAIN_MENU_CODE)
    {
        menu[textIndex].setFillColor(sf::Color::Black);
        menu[textIndex].setScale(4.5f, 4.5f);
    }
    else if (menuCode == MAP_LIST_CODE)
    {
        list[textIndex].setFillColor(sf::Color(128, 128, 128));
        list[textIndex].setOutlineThickness(0);
    }
}
