#include "MapPrototypes.hpp"

sfC::MapPrototype::MapPrototype(const sf::Vector2i &count_blocks, const sf::Vector2i &block_size, const Matrix_t<int> map_blocks)
    : count_blocks_(count_blocks),
      total_size_(count_blocks.x * block_size.x, count_blocks.y * block_size.y),
      block_size_(block_size),
      blocks_(map_blocks)
{
}

void sfC::MapPrototype::dump_interrior(std::ofstream &out) const
{
    out << count_blocks_.x << "\t" << count_blocks_.y << std::endl;
    out << total_size_.x << "\t" << total_size_.y << std::endl;
    out << block_size_.x << "\t" << block_size_.y << std::endl;
    blocks_.dump_interrior(out);
}

sfC::BlockPrototype::BlockPrototype(const sf::Vector2i &tile_coords, const sf::Vector2i &size, TypeBlock type)
    : tile_coords_(tile_coords),
      size_(size),
      type_(type)
{
}