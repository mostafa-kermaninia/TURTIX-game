#include "Enemy2.h"

// private functions

// constructor and distructor
Enemy2::Enemy2(int offset, sf::Texture n_texture, sf::Texture f_texture)
{
    normal_texture = n_texture;
    freezed_texture = f_texture;
    srand((unsigned)(time(NULL) + offset));
    state = rand() % 300;
    stabled = false;
    speed = 1.f;
    direction = RIGHT;
}
Enemy2::~Enemy2()
{
}

// FUNCS

void Enemy2::set_texture(sf::Sprite new_enemy)
{
    enemy = new_enemy;
}

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

bool Enemy2::is_on_ground(sf::Sprite ground)
{
    bool on_ground = false;
    enemy.move(50 * direction, 50 * speed);
    on_ground = collided(ground);
    enemy.move(-50 * direction, -50 * speed);
    return on_ground;
}

void Enemy2::go_back()
{
    direction *= -1;
    enemy.scale(-1.f, 1.f);
}

void Enemy2::render(sf::RenderTarget &target)
{
    target.draw(enemy);
    move();
}

int Enemy2::get_dir()
{
    return direction;
}
bool Enemy2::collided(sf::Sprite target)
{
    if (enemy.getGlobalBounds().intersects(target.getGlobalBounds()))
    {
        return true;
    }
    return false;
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
