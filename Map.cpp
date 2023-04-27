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
        new_sp.setTexture(textures[F_ENEMIE_INDEX]);
        new_sp.scale(0.1f, 0.1f);
        new_sp.move(initMoves(x_pos, y_pos));
        f_enemies.push_back(new_sp);
    }
    else if (object_char == S_ENEMIE)
    {
        new_sp.setTexture(textures[S_ENEMIE_INDEX]);
        new_sp.scale(0.1f, 0.1f);
        new_sp.move(initMoves(x_pos, y_pos));
        s_enemies.push_back(new_sp);
    }
    else if (object_char == STAR)
    {
        new_sp.setTexture(textures[STAR_INDEX]);
        new_sp.scale(0.1f, 0.1f);
        new_sp.move(initMoves(x_pos, y_pos));
        stars.push_back(new_sp);
    }
    else if (object_char == DIAMOND)
    {
        new_sp.setTexture(textures[DIAMOND_INDEX]);
        new_sp.scale(0.1f, 0.1f);
        new_sp.move(initMoves(x_pos, y_pos));
        diamonds.push_back(new_sp);
    }
    else if (object_char == PORTAL)
    {
        new_sp.setTexture(textures[PORTAL_INDEX]);
        new_sp.scale(0.1f, 0.1f);
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

Map::Map()
{
    initTexture();
    load_map();
}

Map::~Map()
{
}

// FUNCS
void Map::render(sf::RenderTarget &target)
{
    for (int i = ground.size() - 1; i >= 0; i--)
    {
        target.draw(ground[i]);
    }
    for (sf::Sprite fe : f_enemies)
    {
        target.draw(fe);
    }
    for (sf::Sprite se : s_enemies)
    {
        target.draw(se);
    }
    for (sf::Sprite jb : jailed_babies)
    {
        target.draw(jb);
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
    target.draw(portal);
}
