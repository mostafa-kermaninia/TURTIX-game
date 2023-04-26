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
#define WINDOWHEIGHT 800
#define WINDOWWIDTH 1300
#define RIGHT 1
#define LEFT -1
const char F_ENEMIE = 'E';
const char S_ENEMIE = 'M';
const char JAILED_BABY = 'O';
const char STAR = '*';
const char DIAMOND = '^';
const char PLAY_GROUND = '.';
const char PORTAL = '$';

const std::vector<std::string> maps = {"map1", "map2", "map3"};

enum
{
    PLAY_GROUND_INDEX,
    F_ENEMIE_INDEX,
    S_ENEMIE_INDEX,
    JAILED_BABY_INDEX,
    FREE_BABY_INDEX,
    STAR_INDEX,
    DIAMOND_INDEX,
    PORTAL_INDEX
};

class Map
{
private:

    int map_number;
    std::vector<sf::Texture> textures;

    // game objects
    sf::Sprite portal;
    std::vector<sf::Sprite> f_enemies;
    std::vector<sf::Sprite> s_enemies;
    std::vector<sf::Sprite> jailed_babies;
    std::vector<sf::Sprite> stars;
    std::vector<sf::Sprite> diamonds;
    std::vector<sf::Sprite> ground;

    // PRIVATE FUNCS
    sf::Vector2f initMoves(int x_pos, int y_pos);
    void initTexture();
    void initSprites(char object_char, int y_pos, int x_pos);
    void load_texture(std::string file_name);
    void load_map();
    void moveToPos(int xMove, int yMove, sf::Sprite &sprite);

public:
    Map();
    virtual ~Map();

    // FUNCS
    void render(sf::RenderTarget &target);
};
