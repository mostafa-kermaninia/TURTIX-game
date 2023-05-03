#include "Map.h"

// PRIVATE FUNCS
sf::Vector2f Map::initMoves(int x_pos, int y_pos)
{
    // adade zarb needs to be fixed
    x_pos *= 50;
    y_pos *= 50;
    return sf::Vector2f((float)x_pos, (float)y_pos);
}

void Map::load_texture(std::string file_name)
{

    sf::Texture new_texture;
    // LOAD TEXTURE FROM FILE
    if (!new_texture.loadFromFile(file_name))
    {
        std::cout << "ERROR::PLAYER::INITTEXTURE:: FILE RO NASHOD BEKHUNAMMMM!!! " << std::endl;
    }
    else
        textures.push_back(new_texture);
}

void Map::initTexture()
{
    // need change
    for (int i = 0; i < TEXTURE_NAME.size(); i++)
        load_texture(TEXTURE_SOURCE + TEXTURE_NAME[i]);
}

void Map::initSprites(char object_char, int y_pos, int x_pos)
{
    sf::Sprite new_sp;
    if (object_char == PLAY_GROUND)
    {
        new_sp.setTexture(textures[PLAY_GROUND_INDEX]);
        new_sp.scale(0.05f, 0.55f);
        new_sp.move(initMoves(x_pos, y_pos));
        ground.push_back(new_sp);
        sf::Sprite sec_sp;
        sec_sp.setTexture(textures[PLAY_GROUND_INDEX]);
        sec_sp.scale(0.05f, 0.55f);
        sec_sp.move(initMoves(x_pos, y_pos + 1));
        ground.push_back(sec_sp);
    }
    else if (object_char == F_ENEMIE)
    {
        Enemy1 *new_enemy = new Enemy1();
        new_sp.setTexture(textures[F_ENEMIE_INDEX]);
        new_sp.scale(0.1f, 0.08f);
        new_sp.move(initMoves(x_pos, y_pos));
        new_enemy->set_texture(new_sp);
        f_enemies.push_back(new_enemy);
    }
    else if (object_char == S_ENEMIE)
    {
        Enemy2 *new_enemy = new Enemy2(s_enemies.size() * DELAY);
        new_sp.setTexture(textures[S_ENEMIE_INDEX]);
        new_sp.scale(0.1f, 0.1f);
        new_sp.move(initMoves(x_pos, y_pos));
        new_enemy->set_texture(new_sp);
        s_enemies.push_back(new_enemy);
    }

    else if (object_char == JAILED_BABY)
    {
        BabyTurtle *new_turtle = new BabyTurtle();
        new_sp.setTexture(textures[JAILED_BABY_INDEX]);
        new_sp.scale(0.1f, 0.08f);
        new_sp.move(initMoves(x_pos, y_pos));
        new_turtle->set_texture(new_sp);
        babies.push_back(new_turtle);
    }

    else if (object_char == STAR)
    {
        new_sp.setTexture(textures[STAR_INDEX]);
        new_sp.scale(0.05f, 0.05f);
        new_sp.move(initMoves(x_pos, y_pos));
        stars.push_back(new_sp);
    }
    else if (object_char == DIAMOND)
    {
        new_sp.setTexture(textures[DIAMOND_INDEX]);
        new_sp.scale(0.2f, 0.2f);
        new_sp.move(initMoves(x_pos, y_pos));
        diamonds.push_back(new_sp);
    }
    else if (object_char == PORTAL)
    {
        new_sp.setTexture(textures[PORTAL_INDEX]);
        new_sp.scale(0.08f, 0.08f);
        new_sp.move(initMoves(x_pos, y_pos));
        portal = new_sp;
    }
    else if (object_char == TRAP)
    {
        new_sp.setTexture(textures[TRAP_INDEX]);
        new_sp.scale(0.15f, 0.2f);
        new_sp.move(initMoves(x_pos, y_pos));
        traps.push_back(new_sp);
        sf::Sprite sec_sp;
        sec_sp.setTexture(textures[PLAY_GROUND_INDEX]);
        sec_sp.scale(0.05f, 0.55f);
        sec_sp.move(initMoves(x_pos, y_pos + 1));
        ground.push_back(sec_sp);
    }
    else if (object_char == BLOCK)
    {
        new_sp.setTexture(textures[BLOCK_INDEX]);
        new_sp.scale(0.1f, 0.1f);
        new_sp.move(initMoves(x_pos, y_pos));
        blocks.push_back(new_sp);
    }
}

void Map::load_map()
{
    int num_of_line = 0;
    std::fstream map_file;
    map_file.open(maps[0]);
    std::string line;
    while (getline(map_file, line))
    {
        num_of_line++;
        for (int i = 0; i < line.size(); i++)
        {
            initSprites(line[i], num_of_line, i);
        }
    }
}

void Map::moveToPos(int xMove, int yMove, sf::Sprite &sprite)
{
    sprite.move(xMove, yMove);
}

Map::Map(sf::Sprite world)
{
    world_background = world;
    initTexture();
    load_map();
}

Map::~Map()
{
    for (int i = 0; i < f_enemies.size(); i++)
        delete f_enemies[i];
    for (int i = 0; i < s_enemies.size(); i++)
        delete s_enemies[i];
}

// FUNCS
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
    sf::Sprite baby_sprite = babies[baby_index]->get_sprite();
    baby_sprite.scale(1.2f, 1.2f);
    baby_sprite.setTexture(textures[FREE_BABY_INDEX], true);
    babies[baby_index]->make_free(baby_sprite);
}

void Map::render(sf::RenderTarget &target)
{
    for (int i = ground.size() - 1; i >= 0; i--)
    {
        target.draw(ground[i]);
    }
    for (int i = 0; i < f_enemies.size(); i++)
    {
        if (!f_enemies[i]->is_in_world(world_background))
            f_enemies[i]->go_back();
        for (auto g : ground)
            if (f_enemies[i]->collided(g))
                f_enemies[i]->go_back();
        for (auto b : blocks)
            if (f_enemies[i]->collided(b))
                f_enemies[i]->go_back();
        f_enemies[i]->render(target);
    }
    for (int i = 0; i < s_enemies.size(); i++)
    {
        if (!s_enemies[i]->is_in_world(world_background))
            s_enemies[i]->go_back();
        for (auto g : ground)
            if (s_enemies[i]->collided(g))
                s_enemies[i]->go_back();
        for (auto b : blocks)
            if (s_enemies[i]->collided(b))
                s_enemies[i]->go_back();
        s_enemies[i]->render(target);
    }
    for (int i = 0; i < babies.size(); i++)
    {
        if (!babies[i]->is_in_world(world_background))
            babies[i]->go_back();
        for (auto g : ground)
            if (babies[i]->collided(g))
                babies[i]->go_back();
        for (auto b : blocks)
            if (babies[i]->collided(b))
                babies[i]->go_back();
        babies[i]->render(target);
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
        target.draw(t);
    for (sf::Sprite b : blocks)
        target.draw(b);
    target.draw(portal);
}
