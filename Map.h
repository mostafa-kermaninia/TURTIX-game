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
#include "Enemy1.h"
#include "Enemy2.h"
#include "Baby_turtle.h"

#define WINDOWHEIGHT 800
#define WINDOWWIDTH 1300
#define BACKGROUNDHEIGHT 4000
#define BACKGROUNDWIDTH 3000

#define RIGHT 1
#define LEFT -1

const int DELAY = 50;

const char F_ENEMIE = 'E';
const char S_ENEMIE = 'M';
const char JAILED_BABY = 'O';
const char STAR = '*';
const char DIAMOND = '^';
const char PLAY_GROUND = '.';
const char PORTAL = '$';
const char TRAP = '|';
const char BLOCK = 'H';

const std::string TEXTURE_SOURCE = "Textures/";
const std::vector<std::string> TEXTURE_NAME = {
    "ground.png",
    "Enemy1.png",
    "Enemy2.png",
    "jailed_baby.png",
    "free_baby.png",
    "star.png",
    "diamond.png",
    "portal.png",
    "trap.png",
    "block.png",
    "Enemy2Freezed.png"};
const std::vector<std::string> MAPS = {"map1", "map2", "map3"};

enum
{
    PLAY_GROUND_INDEX,
    F_ENEMIE_INDEX,
    S_ENEMIE_INDEX,
    JAILED_BABY_INDEX,
    FREE_BABY_INDEX,
    STAR_INDEX,
    DIAMOND_INDEX,
    PORTAL_INDEX,
    TRAP_INDEX,
    BLOCK_INDEX,
    ENEMY2_FREEZED_INDEX
};

class Map
{
private:
    int map_number;
    std::vector<sf::Texture> textures;
    std::vector<sf::Sprite> babies_texture;
    // game objects
    sf::Sprite world_background;
    sf::Sprite portal;
    std::vector<Enemy1 *> f_enemies;
    std::vector<Enemy2 *> s_enemies;
    std::vector<BabyTurtle *> babies;
    std::vector<sf::Sprite> stars;
    std::vector<sf::Sprite> diamonds;
    std::vector<sf::Sprite> ground;
    std::vector<sf::Sprite> traps;
    std::vector<sf::Sprite> blocks;

    // PRIVATE FUNCS
    sf::Vector2f initMoves(int x_pos, int y_pos);
    void initTexture();
    void initSprites(char object_char, int y_pos, int x_pos);
    void load_texture(std::string file_name);
    void moveToPos(int xMove, int yMove, sf::Sprite &sprite);
    void load_baby_turtles();

public:
    Map(sf::Sprite world,int mapCode);
    virtual ~Map();

    // FUNCS
    void load_map(int mapCode);
    void remove_object(std::string obj_name, int object_index);
    void free_baby(int baby_index);
    bool rescued_all_babies();
    void render(sf::RenderTarget &target);

    sf::Sprite getPortal() { return portal; }
    std::vector<Enemy1 *> getFEnemies() { return f_enemies; }
    std::vector<Enemy2 *> getSEnemies() { return s_enemies; }
    std::vector<BabyTurtle *> getJailedBabies() { return babies; }
    std::vector<sf::Sprite> getStars() { return stars; }
    std::vector<sf::Sprite> getDiamonds() { return diamonds; }
    std::vector<sf::Sprite> getGround() { return ground; }
    std::vector<sf::Sprite> getTraps() { return traps; }
    std::vector<sf::Sprite> getBlocks() { return blocks; }
};
