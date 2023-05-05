#include "Player.h"

// PRIVATE FUNCS
void Player::initTexture()
{
    // LOAD TEXTURE FROM FILE
    if (!mortal_texture.loadFromFile("Textures/mainChar.png"))
    {
        std::cout << "ERROR::PLAYER::INITTEXTURE:: FILE RO NASHOD BEKHUNAMMMM!!! " << std::endl;
    }
    if (!immortal_texture.loadFromFile("Textures/immortalMainChar.png"))
    {
        std::cout << "ERROR::PLAYER::INITTEXTURE:: FILE RO NASHOD BEKHUNAMMMM!!! " << std::endl;
    }
}
void Player::initSprite()
{
    // SET TEXTURE TO SPRITE
    sprite.setTexture(mortal_texture);

    // Resize sprite
    sprite.setOrigin(mortal_texture.getSize().x / 2.f, mortal_texture.getSize().y);
    sprite.scale(0.1f, 0.1f);
    sprite.move(50, 1940);
}

Player::Player()
{
    is_immortal_now = false;
    immortal_time_counter = 0;
    gravity_time = 0;
    score = 0;
    health = INITIAL_HEALTH;
    jump_time = 1;
    movement_speed = 20.f;
    jump_speed = 14.f;
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
bool Player::is_alive()
{
    return health > 0;
}
bool Player::is_change_time()
{
    immortal_time_counter++;
    return (immortal_time_counter == IMMORTAL_TIME && is_immortal_now);
}

void Player::change_mode()
{
    if (is_immortal_now)
        sprite.setTexture(mortal_texture);
    else
        sprite.setTexture(immortal_texture);
    immortal_time_counter = 0;
    is_immortal_now = !is_immortal_now;
}

bool Player::is_immortal()
{
    return is_immortal_now;
}
void Player::move(const float dirX, const float dirY)
{
    if (!is_jumping_finished())
        sprite.move(movement_speed * 2 * dirX, movement_speed * 2 * dirY);
    else
        sprite.move(movement_speed * dirX, movement_speed * dirY);
}
void Player::jump(const float dirX, const float dirY)
{
    sprite.move(movement_speed * dirX, (jump_speed - ACCELERATION * jump_time) * dirY);
    jump_time++;
}
void Player::undo_jump(const float dirX, const float dirY)
{
    jump_time--;
    sprite.move(movement_speed * dirX, (jump_speed - ACCELERATION * jump_time) * dirY);
    if (jump_speed - ACCELERATION * jump_time < 0)
        jump_time = 0;
    else
        jump_time = jump_speed / ACCELERATION + 1;
}
void Player::update_score(std::string reward_name)
{
    if (reward_name == "star")
        score += STAR_SCORE;
    else if (reward_name == "diamond")
        score += DIAMOND_SCORE;
}
void Player::update_health()
{
    health--;
    // sprite.setPosition(50.f, 1940.f);
}
void Player::goBack()
{
    player_dir *= -1;
    sprite.scale(-1.f, 1.f);
}
void Player::update()
{
}

bool Player::is_on_ground(std::vector<sf::Sprite> ground)
{
    gravity_time++;
    move(0, (G_ACCELERATION * gravity_time));
    bool on_ground = false;
    for (auto g : ground)
    {
        if (collided(g))
        {
            on_ground = true;
            move(0, -(G_ACCELERATION * gravity_time));
            gravity_time = 0;
        }
    }
    gravity_time--;
    return on_ground;
}

void Player::gravity_effect(std::vector<sf::Sprite> ground)
{
    if (is_jumping_finished())
    {
        gravity_time++;
        move(0, (G_ACCELERATION * gravity_time));
        bool is_on_ground = false;
        for (auto g : ground)
        {
            if (collided(g))
            {
                is_on_ground = true;
                move(0, -(G_ACCELERATION * gravity_time));
                gravity_time = 0;
            }
        }
    }
}
bool Player::is_falling()
{
    return (jump_speed - ACCELERATION * jump_time) <= 0 || gravity_time != 0;
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
}
int Player::collosionType(sf::Sprite target, int direction)
{
    if (direction != NO_MOVE)
    {
        direction = (direction + 2) % 4;
        undo_move(direction);
    }
    std::pair<int, double> v_time = vertical_collosion_time(target);
    std::pair<int, double> h_time = horizental_collosion_time(target);
    if (v_time.second > h_time.second)
        return h_time.first;
    else if (v_time.first == DOWN)
        return DOWN;
    else
        return SIDES;
}
void Player::undo_move(int direction)
{
    if (direction == CLOSION_L)
        move(-1.f, 0.f);
    else if (direction == RIGHT)
        move(1.f, 0.f);
    else if (direction == DOWN)
        undo_jump(0.f, 1.f);
    else if (direction == UP)
        undo_jump(0.f, -1.f);
}
std::pair<int, double> Player::vertical_collosion_time(sf::Sprite target)
{
    std::pair<int, double> collosion_info;
    double d_distance = sprite.getGlobalBounds().top + sprite.getGlobalBounds().height - target.getGlobalBounds().top;
    double u_distance = (target.getGlobalBounds().top + target.getGlobalBounds().height) - sprite.getGlobalBounds().top;
    if (d_distance < 0)
        d_distance *= -1;
    if (u_distance < 0)
        u_distance *= -1;
    if (d_distance > u_distance)
    {
        collosion_info.first = UP;
        collosion_info.second = collosion_time_solver(u_distance);
    }
    else
    {
        collosion_info.first = DOWN;
        collosion_info.second = collosion_time_solver(d_distance);
    }
    return collosion_info;
}
double Player::collosion_time_solver(double distance)
{
    double delta = pow(jump_speed, 2) + (2 * ACCELERATION * distance);
    double answer1 = (-jump_speed + pow(delta, 0.5)) / ACCELERATION;
    double answer2 = (-jump_speed - pow(delta, 0.5)) / ACCELERATION;
    if (answer1 < 0)
    {
        return answer2;
    }
    if (answer2 < 0)
    {
        return answer1;
    }
    else
    {
        return std::min(answer1, answer2);
    }
}
std::pair<int, double> Player::horizental_collosion_time(sf::Sprite target)
{
    std::pair<int, double> collosion_info;
    double r_distance = sprite.getGlobalBounds().left + sprite.getGlobalBounds().width - target.getGlobalBounds().left;
    double l_distance = sprite.getGlobalBounds().left - (target.getGlobalBounds().left + target.getGlobalBounds().width);
    if (r_distance < 0)
        r_distance *= -1;
    if (l_distance < 0)
        l_distance *= -1;
    if (r_distance > l_distance)
    {
        collosion_info.first = LEFT;
        collosion_info.second = l_distance / movement_speed;
    }
    else
    {
        collosion_info.first = RIGHT;
        collosion_info.second = r_distance / movement_speed;
    }
    return collosion_info;
}