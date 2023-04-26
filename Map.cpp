#include "Map.h"

// PRIVATE FUNCS
void Map::initMoves()
{
    moves = {sf::Vector2f(0.f, 700.f),
             sf::Vector2f(204.f, 700.f),
             sf::Vector2f(408.f, 700.f),
             sf::Vector2f(612.f, 700.f),
             sf::Vector2f(816.f, 700.f),
             sf::Vector2f(1020.f, 700.f),
             sf::Vector2f(1224.f, 700.f)};
}
void Map::initTexture()
{
    // LOAD TEXTURE FROM FILE
    if (!texture.loadFromFile("Textures/ground.png"))
    {
        std::cout << "ERROR::PLAYER::INITTEXTURE:: FILE RO NASHOD BEKHUNAMMMM!!! " << std::endl;
    }
}
void Map::initSprites()
{
    for (int i = 0; i < moves.size(); i++)
    {
        // SET TEXTURE TO SPRITE
        sf::Sprite curSp;
        curSp.setTexture(texture);
        // Resize sprite
        curSp.scale(0.2f, 0.2f);
        curSp.move(moves[i]);
        sprites.push_back(curSp);
    }
}

void Map::moveToPos(int xMove, int yMove, sf::Sprite &sprite)
{
    sprite.move(xMove, yMove);
}

Map::Map()
{
    initTexture();
    initMoves();
    initSprites();
}
Map::~Map()
{
}

// FUNCS
void Map::render(sf::RenderTarget &target)
{
    for (sf::Sprite s : sprites)
    {
        target.draw(s);
    }
}
