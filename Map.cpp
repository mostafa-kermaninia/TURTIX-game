#include "Map.h"

sf::Vector2f Map::init_moves(int x_pos, int y_pos)
{
    x_pos *= MOVEMENT_VALUE;
    y_pos *= MOVEMENT_VALUE;
    return sf::Vector2f((float)x_pos, (float)y_pos);
}

void Map::load_texture(std::string file_name)
{
    sf::Texture new_texture;
    if (!new_texture.loadFromFile(file_name))
    {
        std::cout << "ERROR::PLAYER::INITTEXTURE:: COULDN'T READ FILE!!! " << std::endl;
    }
    else
        textures.push_back(new_texture);
}

void Map::init_texture()
{
    for (int i = 0; i < TEXTURE_NAME.size(); i++)
        load_texture(TEXTURE_SOURCE + TEXTURE_NAME[i]);
}

void Map::init_ground(int y_pos, int x_pos)
{
    sf::Sprite new_sp;
    new_sp.setTexture(textures[PLAY_GROUND_INDEX]);
    new_sp.scale(0.05f, 0.40f);
    new_sp.move(init_moves(x_pos, y_pos));
    ground.push_back(new_sp);
}

void Map::init_f_enemy(int y_pos, int x_pos)
{
    sf::Sprite new_sp;
    Enemy1 *new_enemy = new Enemy1();
    new_sp.setTexture(textures[F_ENEMIE_INDEX]);
    new_sp.scale(0.1f, 0.08f);
    new_sp.move(init_moves(x_pos, y_pos));
    new_enemy->set_texture(new_sp);
    f_enemies.push_back(new_enemy);
}

void Map::init_s_enemy(int y_pos, int x_pos)
{
    sf::Sprite new_sp;
    Enemy2 *new_enemy = new Enemy2(s_enemies.size() * DELAY, textures[S_ENEMIE_INDEX], textures[ENEMY2_FREEZED_INDEX]);
    new_sp.setTexture(textures[S_ENEMIE_INDEX]);
    new_sp.scale(0.1f, 0.1f);
    new_sp.move(init_moves(x_pos, y_pos));
    new_enemy->set_texture(new_sp);
    s_enemies.push_back(new_enemy);
}

void Map::init_baby(int y_pos, int x_pos)
{
    sf::Sprite new_sp;
    new_sp.setTexture(textures[JAILED_BABY_INDEX]);
    new_sp.scale(0.1f, 0.1f);
    new_sp.move(init_moves(x_pos, y_pos));
    babies_texture.push_back(new_sp);
}

void Map::init_star(int y_pos, int x_pos)
{
    sf::Sprite new_sp;
    new_sp.setTexture(textures[STAR_INDEX]);
    new_sp.scale(0.05f, 0.05f);
    new_sp.move(init_moves(x_pos, y_pos));
    stars.push_back(new_sp);
}

void Map::init_diamond(int y_pos, int x_pos)
{
    sf::Sprite new_sp;
    new_sp.setTexture(textures[DIAMOND_INDEX]);
    new_sp.scale(0.2f, 0.2f);
    new_sp.move(init_moves(x_pos, y_pos));
    diamonds.push_back(new_sp);
}

void Map::init_portal(int y_pos, int x_pos)
{
    sf::Sprite new_sp;
    new_sp.setTexture(textures[PORTAL_INDEX]);
    new_sp.scale(0.11f, 0.11f);
    new_sp.move(init_moves(x_pos, y_pos));
    portal = new_sp;
}

void Map::init_sprites(char object_char, int y_pos, int x_pos)
{
    sf::Sprite new_sp;
    if (object_char == PLAY_GROUND)
    {
        init_ground(y_pos, x_pos);
    }
    else if (object_char == F_ENEMIE)
    {
        init_f_enemy(y_pos, x_pos);
    }
    else if (object_char == S_ENEMIE)
    {
        init_s_enemy(y_pos, x_pos);
    }
    else if (object_char == JAILED_BABY)
    {
        init_baby(y_pos, x_pos);
    }
    else if (object_char == STAR)
    {
        init_star(y_pos, x_pos);
    }
    else if (object_char == DIAMOND)
    {
        init_diamond(y_pos, x_pos);
    }
    else if (object_char == PORTAL)
    {
        init_portal(y_pos, x_pos);
    }
}

void Map::load_baby_turtles()
{
    for (auto bt : babies_texture)
    {
        BabyTurtle *new_turtle = new BabyTurtle(ground);
        new_turtle->set_texture(bt);
        babies.push_back(new_turtle);
    }
}

Map::Map(sf::Sprite world, int mapCode)
{
    world_background = world;
    init_texture();
    load_map(mapCode);
}

Map::~Map()
{
    for (int i = 0; i < f_enemies.size(); i++)
        delete f_enemies[i];
    for (int i = 0; i < s_enemies.size(); i++)
        delete s_enemies[i];
    for (int i = 0; i < babies.size(); i++)
        delete babies[i];
}

void Map::load_map(int mapCode)
{
    int num_of_line = 0;
    std::fstream map_file;
    map_file.open(MAPS[mapCode]);
    std::string line;
    while (getline(map_file, line))
    {
        num_of_line++;
        for (int i = 0; i < line.size(); i++)
        {
            init_sprites(line[i], num_of_line, i);
        }
    }
    load_baby_turtles();
}

void Map::remove_object(std::string obj_name, int object_index)
{
    if (obj_name == "star")
        stars.erase(stars.begin() + object_index);
    else if (obj_name == "diamond")
        diamonds.erase(diamonds.begin() + object_index);
    else if (obj_name == "Enemy1")
    {
        if (f_enemies[object_index]->get_health() == 1)
        {
            delete f_enemies[object_index];
            f_enemies.erase(f_enemies.begin() + object_index);
        }
        else
            f_enemies[object_index]->update_health();
    }
    else if (obj_name == "Enemy2")
    {
        delete s_enemies[object_index];
        s_enemies.erase(s_enemies.begin() + object_index);
    }
}

void Map::free_baby(int baby_index)
{
    sf::Sprite baby_sprite = *babies[baby_index]->get_sprite();
    baby_sprite.scale(1.2f, 1.2f);
    baby_sprite.setTexture(textures[FREE_BABY_INDEX], true);
    babies[baby_index]->make_free(baby_sprite);
}

bool Map::rescued_all_babies()
{
    return babies.size() == 0;
}

void Map::render_f_enemy(Enemy1 *f_enemy, sf::RenderTarget &target)
{
    if (!f_enemy->is_in_world(world_background))
        f_enemy->go_back();
    for (auto g : ground)
        if (f_enemy->collided(g))
            f_enemy->go_back();
    bool on_ground = false;
    for (auto g : ground)
        if (f_enemy->is_on_ground(g))
        {
            on_ground = true;
            break;
        }
    if (!on_ground)
        f_enemy->go_back();
    for (auto b : blocks)
        if (f_enemy->collided(b))
            f_enemy->go_back();
    f_enemy->render(target);
}

void Map::render_s_enemy(Enemy2 *s_enemy, sf::RenderTarget &target)
{
    if (!s_enemy->is_in_world(world_background))
        s_enemy->go_back();
    for (auto g : ground)
        if (s_enemy->collided(g))
            s_enemy->go_back();
    bool on_ground = false;
    for (auto g : ground)
        if (s_enemy->is_on_ground(g))
        {
            on_ground = true;
            break;
        }
    if (!on_ground)
        s_enemy->go_back();
    for (auto b : blocks)
        if (s_enemy->collided(b))
            s_enemy->go_back();
    s_enemy->render(target);
}

void Map::render_baby(BabyTurtle *baby, sf::RenderTarget &target)
{
    if (!baby->is_in_world(world_background))
    {
        baby->go_back();
    }
    baby->set_on_ground(false);
    baby->get_sprite()->move(0, ACCELERATION * baby->get_fall_time());
    for (auto g : ground)
    {
        if (baby->collided(g))
        {
            baby->set_on_ground(true);
            baby->move_back();
            baby->set_fall_time(1);
        }
    }
    if (!baby->is_it_on_ground())
    {
        baby->get_sprite()->move(0, ACCELERATION * baby->get_fall_time());
        baby->update_fall_time();
    }
    baby->move();
    baby->render(target);
}

void Map::render(sf::RenderTarget &target)
{
    for (int i = ground.size() - 1; i >= 0; i--)
    {
        target.draw(ground[i]);
    }
    for (int i = 0; i < f_enemies.size(); i++)
    {
        render_f_enemy(f_enemies[i], target);
    }
    for (int i = 0; i < s_enemies.size(); i++)
    {
        render_s_enemy(s_enemies[i], target);
    }
    for (int i = 0; i < babies.size(); i++)
    {
        render_baby(babies[i], target);
        if (babies[i]->collided(portal))
        {
            delete babies[i];
            babies.erase(babies.begin() + i);
        }
    }
    for (sf::Sprite s : stars)
    {
        target.draw(s);
    }
    for (sf::Sprite d : diamonds)
    {
        target.draw(d);
    }
    for (sf::Sprite t : traps)
    {
        target.draw(t);
    }
    for (sf::Sprite b : blocks)
    {
        target.draw(b);
    }
    target.draw(portal);
}

sf::Sprite Map::getPortal()
{
    return portal;
}

std::vector<Enemy1 *> Map::getFEnemies()
{
    return f_enemies;
}

std::vector<Enemy2 *> Map::getSEnemies()
{
    return s_enemies;
}

std::vector<BabyTurtle *> Map::getJailedBabies()
{
    return babies;
}

std::vector<sf::Sprite> Map::getStars()
{
    return stars;
}

std::vector<sf::Sprite> Map::getDiamonds()
{
    return diamonds;
}

std::vector<sf::Sprite> Map::getGround()
{
    return ground;
}
