#include "Baby_turtle.h"

BabyTurtle::BabyTurtle(std::vector<sf::Sprite> g_parts)
{
    fall_time = 1;
    speed = 1.f;
    direction = RIGHT;
    is_free = false;
    ground_parts = g_parts;
}

void BabyTurtle::set_texture(sf::Sprite new_baby)
{
    baby = new_baby;
}

void BabyTurtle::set_fall_time(int t)
{
    fall_time = t;
}

void BabyTurtle::set_on_ground(bool og)
{
    is_on_ground = og;
}

void BabyTurtle::update_fall_time()
{
    fall_time++;
}

void BabyTurtle::make_free(sf::Sprite free_baby_sprite)
{
    set_texture(free_baby_sprite);
    is_free = true;
}

void BabyTurtle::move()
{
    if (is_free)
        baby.move(speed * direction, 0);
    if (is_it_on_ground())
    {
        return;
    }
    baby.move(0, ACCELERATION * fall_time);
    fall_time++;
}

void BabyTurtle::move_back()
{
    baby.move(0, -ACCELERATION * fall_time);
}

void BabyTurtle::go_back()
{
    direction *= -1;
    baby.scale(-1.f, 1.f);
    move();
}

bool BabyTurtle::collided(sf::Sprite target)
{
    if (baby.getGlobalBounds().intersects(target.getGlobalBounds()))
    {
        return true;
    }
    return false;
}

bool BabyTurtle::is_in_world(sf::Sprite world)
{
    if (baby.getGlobalBounds().left >= world.getGlobalBounds().left &&
        baby.getGlobalBounds().top >= world.getGlobalBounds().top &&
        baby.getGlobalBounds().left + baby.getGlobalBounds().width <=
            world.getGlobalBounds().left + world.getGlobalBounds().width &&
        baby.getGlobalBounds().top + baby.getGlobalBounds().height <=
            world.getGlobalBounds().top + world.getGlobalBounds().height)
    {
        return true;
    }
    return false;
}

bool BabyTurtle::is_jailed()
{
    return !is_free;
}

bool BabyTurtle::is_it_on_ground()
{
    return is_on_ground;
}

int BabyTurtle::get_dir()
{
    return direction;
}

sf::Sprite *BabyTurtle::get_sprite()
{
    return &baby;
}

int BabyTurtle::get_fall_time()
{
    return fall_time;
}

void BabyTurtle::render(sf::RenderTarget &target)
{
    target.draw(baby);
}