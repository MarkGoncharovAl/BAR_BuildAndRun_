#include "Map.h"
/*
bool M::is_solid(const int type)
{
	return (type >= (1 << 7));
}
*/

M::Map::Map(const std::string &file, const M::Map_Prototype &new_map) noexcept : vertices_(),
                                                                                 tileset_(),
                                                                                 map_(new_map)
{
    // load the tileset texture
    if (!tileset_.loadFromFile(file))
        ERROR(std::string("Can not load image from file ") + file);

    // resize the vertex array to fit the level size
    vertices_.setPrimitiveType(sf::Quads);
    vertices_.resize(map_.count_blocks_.x * map_.count_blocks_.y * 4);

    // populate the vertex array, with one quad per tile
    for (int i = 0; i < map_.count_blocks_.x; ++i)
        for (int j = 0; j < map_.count_blocks_.y; ++j)
        {

            // get the current tile number
            const int tile_number = map_.blocks_[j][i];
            // get a pointer to the current tile's quad
            sf::Vertex *quad = &vertices_[4 * (i + j * map_.count_blocks_.y)];

            const float cur_texture_size_x = static_cast<float>(sort_Block[tile_number].size_.x);
            const float cur_texture_size_y = static_cast<float>(sort_Block[tile_number].size_.y);

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
                map_.blocks_[j][i] = 1;
            else
                map_.blocks_[j][i] -= 1;
            change_block(sf::Vector2i(i, j), tile_number);
        }
}

M::Map::Map(const std::string &file) noexcept : vertices_(),
                                                tileset_(),
                                                map_()
{
    // load the tileset texture
    if (!tileset_.loadFromFile(file))
        ERROR(std::string("Can not load image from file ") + file);
}
void M::Map::create_map(const M::Map_Prototype &new_map) noexcept
{
    this->map_ = new_map;

    // resize the vertex array to fit the level size
    vertices_.setPrimitiveType(sf::Quads);
    vertices_.resize(map_.count_blocks_.x * map_.count_blocks_.y * 4);

    // populate the vertex array, with one quad per tile
    for (int i = 0; i < map_.count_blocks_.x; ++i)
        for (int j = 0; j < map_.count_blocks_.y; ++j)
        {

            // get the current tile number
            const int tile_number = map_.blocks_[j][i];
            // get a pointer to the current tile's quad
            sf::Vertex *quad = &vertices_[4 * (i + j * map_.count_blocks_.y)];

            const float cur_texture_size_x = static_cast<float>(sort_Block[tile_number].size_.x);
            const float cur_texture_size_y = static_cast<float>(sort_Block[tile_number].size_.y);

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
                map_.blocks_[j][i] = 1;
            else
                map_.blocks_[j][i] -= 1;
            change_block(sf::Vector2i(i, j), tile_number);
        }
}

void M::Map::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &tileset_;

    // draw the vertex array
    target.draw(vertices_, states);
}
bool M::Map::change_block(const sf::Vector2i &position, int new_tex) noexcept
{
    if (map_.blocks_[position.y][position.x] == new_tex)
        return false;

    map_.blocks_[position.y][position.x] = new_tex;
    sf::Vertex *quad = &vertices_[4 * (position.x + position.y * map_.count_blocks_.y)];

    const float cur_texture_size_x = static_cast<float>(sort_Block[new_tex].size_.x);
    const float cur_texture_size_y = static_cast<float>(sort_Block[new_tex].size_.y);

    const sf::Vector2f cur_texture(sort_Block[new_tex].tile_coords_);

    quad[0].texCoords = cur_texture;
    quad[1].texCoords = cur_texture + sf::Vector2f(cur_texture_size_x, 0.f);
    quad[2].texCoords = cur_texture + sf::Vector2f(cur_texture_size_x, cur_texture_size_y);
    quad[3].texCoords = cur_texture + sf::Vector2f(0.f, cur_texture_size_y);
    return true;
}

bool M::Map::is_solid(const sf::Vector2f &coords) noexcept
{
    sf::Vector2i cur_block = AbsCoords(coords.x, coords.y);
    return sort_Block[map_.blocks_[cur_block.y][cur_block.x]].is_solid();
}
bool M::Map::is_sand(const sf::Vector2f &coords) noexcept
{
    sf::Vector2i cur_block = AbsCoords(coords.x, coords.y);
    return sort_Block[map_.blocks_[cur_block.y][cur_block.x]].is_sand();
}
bool M::Map::is_accel(const sf::Vector2f &coords) noexcept
{
    sf::Vector2i cur_block = AbsCoords(coords.x, coords.y);
    return sort_Block[map_.blocks_[cur_block.y][cur_block.x]].is_accel();
}
bool M::Map::is_restart(const sf::Vector2f &coords) noexcept
{
    sf::Vector2i cur_block = AbsCoords(coords.x, coords.y);
    return sort_Block[map_.blocks_[cur_block.y][cur_block.x]].is_restart();
}

bool M::Map::is_solid(const sf::FloatRect &rect) noexcept
{
    sf::IntRect rect_int(int(rect.left), int(rect.top), int(rect.width + rect.left), int(rect.height + rect.top));
    sf::Vector2i left_top = AbsCoords(rect_int.left, rect_int.top);
    sf::Vector2i right_bot = AbsCoords(rect_int.width, rect_int.height);

    for (int i = left_top.x; i <= right_bot.x; ++i)
    {
        for (int j = left_top.y; j <= right_bot.y; ++j)
        {
            if (sort_Block[map_.blocks_[j][i]].is_solid())
                return true;
        }
    }
    return false;
}

bool M::Map::is_finish(sf::FloatRect &&rect) noexcept
{
    sf::IntRect rect_int(int(rect.left), int(rect.top), int(rect.width + rect.left), int(rect.height + rect.top));
    sf::Vector2i left_top = AbsCoords(rect_int.left, rect_int.top);
    sf::Vector2i right_bot = AbsCoords(rect_int.width, rect_int.height);

    for (int i = left_top.x; i <= right_bot.x; ++i)
    {
        for (int j = left_top.y; j <= right_bot.y; ++j)
        {
            if (map_.blocks_[j][i] == M::BLOCKS::Target)
                return true;
        }
    }
    return false;
}

bool M::Map::create_random(int num_block, std::size_t count_blocks, const sf::IntRect &rect) noexcept
{
    if (num_block > M::num_blocks)
        return false;

    for (std::size_t i = 0; i < count_blocks; ++i)
    {
        change_block(sf::Vector2i(rect.top + rand() % rect.height, rect.left + rand() % rect.width), num_block);
    }
    return true;
}
bool M::Map::change_rect(int num_block, const sf::IntRect &rect) noexcept
{
    if (num_block > M::num_blocks)
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

M::BLOCKS M::Map::get_type_block(const sf::Vector2i &block) noexcept
{
    return static_cast<M::BLOCKS>(this->map_.blocks_[block.y][block.x]);
}