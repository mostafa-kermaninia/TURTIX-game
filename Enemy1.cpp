#include "Enemy1.h"

// private functions

// constructor and distructor
Enemy1::Enemy1()
{
    speed = 1.f;
    direction = RIGHT;
}
Enemy1::~Enemy1()
{
}

// FUNCS

void Enemy1::set_texture(sf::Sprite new_enemy)
{
    enemy = new_enemy;
}

void Enemy1::move()
{
    enemy.move(speed * direction, 0);
}

void Enemy1::go_back()
{
    direction *= -1;
    enemy.scale(-1.f, 1.f);
}

void Enemy1::render(sf::RenderTarget &target)
{
    target.draw(enemy);
    move();
}

int Enemy1::get_dir()
{
    return direction;
}
bool Enemy1::collided(sf::Sprite target)
{
    if (enemy.getGlobalBounds().intersects(target.getGlobalBounds()))
    {
        return true;
    }
    return false;
}
