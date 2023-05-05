#include "Enemy1.h"

Enemy1::Enemy1()
{
    health = 2;
    speed = 1.f;
    direction = RIGHT;
}

void Enemy1::set_texture(sf::Sprite new_enemy)
{
    enemy = new_enemy;
}

void Enemy1::update_health()
{
    health--;
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

bool Enemy1::collided(sf::Sprite target)
{
    if (enemy.getGlobalBounds().intersects(target.getGlobalBounds()))
    {
        return true;
    }
    return false;
}

bool Enemy1::is_on_ground(sf::Sprite ground)
{
    bool on_ground = false;
    enemy.move(MOVEMENT_VALUE * direction, MOVEMENT_VALUE * speed);
    on_ground = collided(ground);
    enemy.move(-MOVEMENT_VALUE * direction, -MOVEMENT_VALUE * speed);
    return on_ground;
}

bool Enemy1::is_in_world(sf::Sprite world)
{
    if (enemy.getGlobalBounds().left >= world.getGlobalBounds().left &&
        enemy.getGlobalBounds().top >= world.getGlobalBounds().top &&
        enemy.getGlobalBounds().left + enemy.getGlobalBounds().width <=
            world.getGlobalBounds().left + world.getGlobalBounds().width &&
        enemy.getGlobalBounds().top + enemy.getGlobalBounds().height <=
            world.getGlobalBounds().top + world.getGlobalBounds().height)
    {
        return true;
    }

    return false;
}

int Enemy1::get_dir()
{
    return direction;
}

int Enemy1::get_health()
{
    return health;
}
sf::Sprite Enemy1::get_sprite()
{
    return enemy;
}

void Enemy1::render(sf::RenderTarget &target)
{
    target.draw(enemy);
    move();
}