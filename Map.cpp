#include "Map.h"

// PRIVATE FUNCS
void Map::initTexture()
{
    // LOAD TEXTURE FROM FILE
    if (!texture.loadFromFile("Textures/mainChar.png"))
    {
        std::cout << "ERROR::PLAYER::INITTEXTURE:: FILE RO NASHOD BEKHUNAMMMM!!! " << std::endl;
    }
}
void Map::initSprite()
{
    // SET TEXTURE TO SPRITE
    sprite.setTexture(texture);

    // Resize sprite
    sprite.setOrigin((sf::Vector2f)texture.getSize() / 2.f);
    sprite.move(WINDOWWIDTH / 10.f, WINDOWHEIGHT / 2.f);
    sprite.scale(0.2f, 0.2f);
}

Map::Map()
{
    movementSpeed = 1.f;
    playerDir = RIGHT;
    initTexture();
    initSprite();
}
Map::~Map()
{
}

// FUNCS

void Map::move(const float dirX, const float dirY)
{
    sprite.move(movementSpeed * dirX, movementSpeed * dirY);
}

void Map::goBack()
{
    playerDir *= -1;
    sprite.scale(-1.f, 1.f);
}

void Map::update()
{
}

void Map::render(sf::RenderTarget &target)
{
    target.draw(sprite);
}

int Map::getDir()
{
    return playerDir;
}

bool Map::collided(sf::Sprite target)
{
    if (sprite.getGlobalBounds().intersects(target.getGlobalBounds()))
    {
        return true;
    }
    return false;
}
