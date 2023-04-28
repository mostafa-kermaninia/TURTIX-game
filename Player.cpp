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
    sprite.scale(0.1f, 0.1f);
    sprite.move(WINDOWWIDTH / 1.9, WINDOWHEIGHT / 1.9);
}

Player::Player()
{
    is_in_air = false;
    jump_time = 1;
    movement_speed = 10.f;
    jump_speed = 10.f;
    player_dir = RIGHT;
    initTexture();
    initSprite();
}
Player::~Player()
{
}

// FUNCS

bool Player::is_jumping_finished()
{
    if (jump_time == JUMP_DURATION || jump_time == 1)
    {
        jump_time = 1;
        return true;
    }
    return false;
}

void Player::move(const float dirX, const float dirY)
{
    sprite.move(movement_speed * dirX, movement_speed * dirY);
}
void Player::jump(const float dirX, const float dirY)
{
    sprite.move(movement_speed * dirX, (jump_speed - ACCELERATION * jump_time) * dirY);
    jump_time++;
}
void Player::goBack()
{
    player_dir *= -1;
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
    return player_dir;
}

bool Player::collided(sf::Sprite target)
{
    if (sprite.getGlobalBounds().intersects(target.getGlobalBounds()))
    {
        return true;
    }
    return false;

    // updatev view if its in background area
    // if (sprite.getGlobalBounds().left > target.getGlobalBounds().left &&
    //     sprite.getGlobalBounds().top> target.getGlobalBounds().top  &&
    //     sprite.getGlobalBounds().left+sprite.getGlobalBounds().width < target.getGlobalBounds().left+sprite.getGlobalBounds().width &&
    //     getPos().x < worldBackground.getGlobalBounds().width)
    // {
    //     gameView.setCenter(getPos());
    // }
}
