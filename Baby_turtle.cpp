#include "Baby_turtle.h"

// private functions

// constructor and distructor
BabyTurtle::BabyTurtle(std::vector<sf::Sprite> gParts)
{
    fallTime = 1;
    speed = 1.f;
    direction = RIGHT;
    is_free = false;
    groundParts = gParts;
}
BabyTurtle::~BabyTurtle()
{
}

// FUNCS

void BabyTurtle::make_free(sf::Sprite free_baby_sprite)
{
    set_texture(free_baby_sprite);
    is_free = true;
}
void BabyTurtle::set_texture(sf::Sprite new_baby)
{
    baby = new_baby;
}

void BabyTurtle::move()
{
    if (is_free)
        baby.move(speed * direction, 0);

    for (auto part : groundParts)
        if (is_it_on_ground())
        {
            return;
        }
    baby.move(0, ACCELERATION * fallTime);
    fallTime++;
}

void BabyTurtle::moveBack()
{
    baby.move(0, -ACCELERATION * fallTime);
}

void BabyTurtle::go_back()
{
    direction *= -1;
    baby.scale(-1.f, 1.f);
    move();
}

void BabyTurtle::render(sf::RenderTarget &target)
{
    target.draw(baby);
}

int BabyTurtle::get_dir()
{
    return direction;
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
