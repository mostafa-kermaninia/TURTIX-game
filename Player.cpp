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
    sprite.move(50, 1640);
}

Player::Player()
{
    score = 0;
    health = INITIAL_HEALTH;
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

bool Player::is_alive()
{
    return health > 0;
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
}
void Player::goBack()
{
    player_dir *= -1;
    sprite.scale(-1.f, 1.f);
}
void Player::update()
{
}

bool Player::is_falling()
{
    return (jump_speed - ACCELERATION * jump_time) <= 0;
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
    bool is_fall = is_falling();
    jump_time = 2;
    if (v_time.second > h_time.second)
        return h_time.first;
    else if (v_time.first == DOWN && is_fall)
        return DOWN;
    else
        return SIDES;
}

void Player::undo_move(int direction)
{
    if (direction == LEFT)
        move(-1.f, 0.f);
    else if (direction == RIGHT)
        move(1.f, 0.f);
    else if (direction == DOWN)
        move(0.f, 1.f);
    else if (direction == UP)
        move(0.f, -1.f);
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