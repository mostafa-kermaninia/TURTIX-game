#include "Player.h"

// PRIVATE FUNCS
void Player::initTexture()
{
    // LOAD TEXTURE FROM FILE
    if (!texture.loadFromFile("Textures/mainChar.png"))
    {
        std::cout << "ERROR::PLAYER::INITTEXTURE:: FILE RO NASHOD BEKHUNAMMMM!!! " << std::endl;
    }
}
void Player::initSprite()
{
    // SET TEXTURE TO SPRITE
    sprite.setTexture(texture);

    // Resize sprite
    sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y);
    sprite.scale(0.2f, 0.2f);
    sprite.move(WINDOWWIDTH / 8.f, WINDOWHEIGHT * 2.3 + 30.f);
}

Player::Player()
{
    movementSpeed = 10.f;
    playerDir = RIGHT;
    initTexture();
    initSprite();
}
Player::~Player()
{
}

// FUNCS

void Player::move(const float dirX, const float dirY)
{
    sprite.move(movementSpeed * dirX, movementSpeed * dirY);
}
void Player::jump(const float dirX, const float dirY)
{
    sprite.move(movementSpeed * dirX, movementSpeed * dirY);
}
void Player::goBack()
{
    playerDir *= -1;
    sprite.scale(-1.f, 1.f);
}
void Player::update()
{
}
void Player::render(sf::RenderTarget &target)
{
    target.draw(sprite);
}
int Player::getDir()
{
    return playerDir;
}
bool Player::collided(sf::Sprite target)
{
    if (sprite.getGlobalBounds().intersects(target.getGlobalBounds()))
    {
        return true;
    }
    return false;
}
