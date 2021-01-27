#include "Map.hpp"
#include "../Common_libs/Errors/Errors.hpp"
/*
bool M::is_solid(const int type)
{
	return (type >= (1 << 7));
}
*/

sfC::Map::Map(const std::string &file, const MapPrototype &new_map)
    : vertices_(),
      tileset_(),
      map_(new_map)
{
    // load the tileset texture
    if (!tileset_.loadFromFile(file))
        ERROR(std::string("Can not load image from file ") + file);

    // resize the vertex array to fit the level size
    vertices_.setPrimitiveType(sf::Quads);
    vertices_.resize(map_.GetCount().x * map_.GetCount().y * 4);

    // populate the vertex array, with one quad per tile
    for (int i = 0; i < map_.GetCount().x; ++i)
        for (int j = 0; j < map_.GetCount().y; ++j)
        {

            // get the current tile number
            const int tile_number = map_[j][i];
            // get a pointer to the current tile's quad
            sf::Vertex *quad = &vertices_[4 * (i + j * map_.GetCount().y)];

            const float cur_texture_size_x = static_cast<float>(sfCON::sort_Block[tile_number].GetSize().x);
            const float cur_texture_size_y = static_cast<float>(sfCON::sort_Block[tile_number].GetSize().y);

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * cur_texture_size_x, j * cur_texture_size_y);
            quad[1].position = sf::Vector2f((i + 1) * cur_texture_size_x, j * cur_texture_size_y);
            quad[2].position = sf::Vector2f((i + 1) * cur_texture_size_x, (j + 1) * cur_texture_size_y);
            quad[3].position = sf::Vector2f(i * cur_texture_size_x, (j + 1) * cur_texture_size_y);

            //here is some magic - it concerned with 1 thing:
            //function M::Map::change_block won't do anything at all
            //if old type of block is equal to new - blocks are similar
            //that's why i have to rewrite type of block in order to
            //push function to work!!!
            if (tile_number == 0)
                map_[j][i] = 1;
            else
                map_[j][i] -= 1;
            change_block(sf::Vector2i(i, j), tile_number);
        }
}

sfC::Map::Map(const std::string &file)
    : vertices_(),
      tileset_(),
      map_()
{
    // load the tileset texture
    if (!tileset_.loadFromFile(file))
        ERROR(std::string("Can not load image from file ") + file);
}

void sfC::Map::create_map(const MapPrototype &new_map)
{
    this->map_ = new_map;

    // resize the vertex array to fit the level size
    vertices_.setPrimitiveType(sf::Quads);
    vertices_.resize(map_.GetCount().x * map_.GetCount().y * 4);

    // populate the vertex array, with one quad per tile
    for (int i = 0; i < map_.GetCount().x; ++i)
        for (int j = 0; j < map_.GetCount().y; ++j)
        {

            // get the current tile number
            const int tile_number = map_[j][i];
            // get a pointer to the current tile's quad
            sf::Vertex *quad = &vertices_[4 * (i + j * map_.GetCount().y)];

            const float cur_texture_size_x = static_cast<float>(sfCON::sort_Block[tile_number].GetSize().x);
            const float cur_texture_size_y = static_cast<float>(sfCON::sort_Block[tile_number].GetSize().y);

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * cur_texture_size_x, j * cur_texture_size_y);
            quad[1].position = sf::Vector2f((i + 1) * cur_texture_size_x, j * cur_texture_size_y);
            quad[2].position = sf::Vector2f((i + 1) * cur_texture_size_x, (j + 1) * cur_texture_size_y);
            quad[3].position = sf::Vector2f(i * cur_texture_size_x, (j + 1) * cur_texture_size_y);

            //here is some magic - it concerned with 1 thing:
            //function M::Map::change_block won't do anything at all
            //if old type of block is equal to new - blocks are similar
            //that's why i have to rewrite type of block in order to
            //push function to work!!!
            if (tile_number == 0)
                map_[j][i] = 1;
            else
                map_[j][i] -= 1;
            change_block(sf::Vector2i(i, j), tile_number);
        }
}

void sfC::Map::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &tileset_;

    // draw the vertex array
    target.draw(vertices_, states);
}

bool sfC::Map::change_block(const sf::Vector2i &position, int new_tex)
{
    if (map_[position.y][position.x] == new_tex)
        return false;

    map_[position.y][position.x] = new_tex;
    sf::Vertex *quad = &vertices_[4 * (position.x + position.y * map_.GetCount().y)];

    const float cur_texture_size_x = static_cast<float>(sfCON::sort_Block[new_tex].GetSize().x);
    const float cur_texture_size_y = static_cast<float>(sfCON::sort_Block[new_tex].GetSize().y);

    const sf::Vector2f cur_texture(sfCON::sort_Block[new_tex].GetTileCoord());

    quad[0].texCoords = cur_texture;
    quad[1].texCoords = cur_texture + sf::Vector2f(cur_texture_size_x, 0.f);
    quad[2].texCoords = cur_texture + sf::Vector2f(cur_texture_size_x, cur_texture_size_y);
    quad[3].texCoords = cur_texture + sf::Vector2f(0.f, cur_texture_size_y);
    return true;
}

bool sfC::Map::is_solid(const sf::Vector2f &coords) const
{
    sf::Vector2i cur_block = AbsCoords(coords.x, coords.y);
    return sfCON::sort_Block[map_[cur_block.y][cur_block.x]].GetType() == sfC::BlockPrototype::TypeBlock::Wall;
}
bool sfC::Map::is_sand(const sf::Vector2f &coords) const
{
    sf::Vector2i cur_block = AbsCoords(coords.x, coords.y);
    return sfCON::sort_Block[map_[cur_block.y][cur_block.x]].GetType() == sfC::BlockPrototype::TypeBlock::Sand;
}
bool sfC::Map::is_accel(const sf::Vector2f &coords) const
{
    sf::Vector2i cur_block = AbsCoords(coords.x, coords.y);
    return sfCON::sort_Block[map_[cur_block.y][cur_block.x]].GetType() == sfC::BlockPrototype::TypeBlock::Acceleration;
}
bool sfC::Map::is_restart(const sf::Vector2f &coords) const
{
    sf::Vector2i cur_block = AbsCoords(coords.x, coords.y);
    return sfCON::sort_Block[map_[cur_block.y][cur_block.x]].GetType() == sfC::BlockPrototype::TypeBlock::Restart;
}

bool sfC::Map::is_solid(const sf::FloatRect &rect) const
{
    sf::IntRect rect_int(int(rect.left), int(rect.top), int(rect.width + rect.left), int(rect.height + rect.top));
    sf::Vector2i left_top = AbsCoords(rect_int.left, rect_int.top);
    sf::Vector2i right_bot = AbsCoords(rect_int.width, rect_int.height);

    for (int i = left_top.x; i <= right_bot.x; ++i)
    {
        for (int j = left_top.y; j <= right_bot.y; ++j)
        {
            if (sfCON::sort_Block[map_[j][i]].GetType() == sfC::BlockPrototype::TypeBlock::Wall)
                return true;
        }
    }
    return false;
}

bool sfC::Map::is_finish(sf::FloatRect &&rect) const
{
    sf::IntRect rect_int(int(rect.left), int(rect.top), int(rect.width + rect.left), int(rect.height + rect.top));
    sf::Vector2i left_top = AbsCoords(rect_int.left, rect_int.top);
    sf::Vector2i right_bot = AbsCoords(rect_int.width, rect_int.height);

    for (int i = left_top.x; i <= right_bot.x; ++i)
    {
        for (int j = left_top.y; j <= right_bot.y; ++j)
        {
            if (map_[j][i] == static_cast<int>(sfC::BlockPrototype::TypeBlock::Target))
                return true;
        }
    }
    return false;
}

bool sfC::Map::change_rect(int num_block, const sf::IntRect &rect)
{
    if (num_block > sfCON::num_blocks)
        return false;

    int width = rect.left + rect.width;
    int height = rect.top + rect.height;

    for (int i = rect.left; i < width; ++i)
    {
        for (int j = rect.top; j < height; ++j)
        {
            change_block(sf::Vector2i(i, j), num_block);
        }
    }
    return true;
}

sfC::BlockPrototype::TypeBlock sfC::Map::get_type_block(const sf::Vector2i &block) const
{
    return static_cast<sfC::BlockPrototype::TypeBlock>(this->map_[block.y][block.x]);
}