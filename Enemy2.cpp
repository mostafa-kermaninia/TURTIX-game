#include "Enemy2.h"

bool Enemy2::is_change_time()
{
    if (state % CHANGE_MODE_TIME == 0)
    {
        if (stabled)
            enemy.setTexture(normal_texture);
        else
            enemy.setTexture(freezed_texture);
        return true;
    }
    return false;
}

Enemy2::Enemy2(int offset, sf::Texture n_texture, sf::Texture f_texture)
{
    normal_texture = n_texture;
    freezed_texture = f_texture;
    srand((unsigned)(time(NULL) + offset));
    state = rand() % CHANGE_MODE_TIME;
    stabled = false;
    speed = 1.f;
    direction = RIGHT;
}

void Enemy2::set_texture(sf::Sprite new_enemy)
{
    enemy = new_enemy;
}

void Enemy2::move()
{
    if (is_change_time())
    {
        state %= CHANGE_MODE_TIME;
        stabled = !stabled;
    }
    if (!stabled)
        enemy.move(speed * direction, 0);
    state++;
}

void Enemy2::go_back()
{
    direction *= -1;
    enemy.scale(-1.f, 1.f);
}

bool Enemy2::collided(sf::Sprite target)
{
    if (enemy.getGlobalBounds().intersects(target.getGlobalBounds()))
    {
        return true;
    }
    return false;
}

bool Enemy2::is_on_ground(sf::Sprite ground)
{
    bool on_ground = false;
    enemy.move(MOVEMENT_VALUE * direction, MOVEMENT_VALUE * speed);
    on_ground = collided(ground);
    enemy.move(-MOVEMENT_VALUE * direction, -MOVEMENT_VALUE * speed);
    return on_ground;
}

bool Enemy2::is_in_world(sf::Sprite world)
{

    if (enemy.getGlobalBounds().left >= world.getGlobalBounds().left &&
        enemy.getGlobalBounds().top >= world.getGlobalBounds().top &&
        enemy.getGlobalBounds().left + enemy.getGlobalBounds().width <=
            world.getGlobalBounds().left + world.getGlobalBounds().width &&
        enemy.getGlobalBounds().top + enemy.getGlobalBounds().height <= world.getGlobalBounds().top + world.getGlobalBounds().height)
    {
        return true;
    }

    return false;
}

bool Enemy2::is_immortal()
{
    return stabled;
}

int Enemy2::get_dir()
{
    return direction;
}

sf::Sprite Enemy2::get_sprite()
{
    return enemy;
}

void Enemy2::render(sf::RenderTarget &target)
{
    target.draw(enemy);
    move();
}