#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include "../Common_libs/Matrix/Matrix.hpp"

namespace sfC
{

    class MapPrototype
    {
    public:
        MapPrototype(const sf::Vector2i &count_blocks, const sf::Vector2i &block_size, const Matrix_t<int> map_blocks);
        MapPrototype(const MapPrototype &other) = default;
        MapPrototype() = default;

        sf::Vector2i GetCount() const { return count_blocks_; }
        sf::Vector2i GetTotalSize() const { return total_size_; }
        sf::Vector2i GetBlockSize() const { return block_size_; }

        Matrix_t<int>::SetterRaw_t operator[](int num) { return blocks_[num]; }
        Matrix_t<int>::GetterRaw_t operator[](int num) const { return blocks_[num]; }

        ////////
        // DANGEROUS!!!!!!!!!!!!!!!!!!!! Rewrite create_from_empty and this!
        ///////
        MapPrototype &operator=(const MapPrototype &other) = default;

        void dump_interrior(std::ofstream &out) const;

    private:
        sf::Vector2i count_blocks_;
        sf::Vector2i total_size_;
        sf::Vector2i block_size_; // the one block size
        Matrix_t<int> blocks_;
    };

    class BlockPrototype
    {
    public:
        enum class TypeBlock
        {
            Field = 0,
            Wall,
            Target,
            Sand,
            Acceleration,
            Restart
        };

        BlockPrototype(const sf::Vector2i &tile_coords, const sf::Vector2i &size, TypeBlock type);

        constexpr TypeBlock GetType() const noexcept { return type_; }

        sf::Vector2i GetTileCoord() const { return tile_coords_; }
        sf::Vector2i GetSize() const { return size_; }

    private:
        const sf::Vector2i tile_coords_;
        const sf::Vector2i size_;
        const TypeBlock type_;
    };

} // namespace sfC

namespace sfCON
{
    constexpr int num_blocks = 6;
    static const std::array<sfC::BlockPrototype, num_blocks> sort_Block =
        {
            sfC::BlockPrototype(sf::Vector2i(115, 397), sf::Vector2i(32, 32), sfC::BlockPrototype::TypeBlock::Field),
            sfC::BlockPrototype(sf::Vector2i(1, 847), sf::Vector2i(32, 32), sfC::BlockPrototype::TypeBlock::Wall),
            sfC::BlockPrototype(sf::Vector2i(339, 283), sf::Vector2i(32, 32), sfC::BlockPrototype::TypeBlock::Target),
            sfC::BlockPrototype(sf::Vector2i(396, 734), sf::Vector2i(32, 32), sfC::BlockPrototype::TypeBlock::Sand),
            sfC::BlockPrototype(sf::Vector2i(396, 846), sf::Vector2i(32, 32), sfC::BlockPrototype::TypeBlock::Acceleration),
            sfC::BlockPrototype(sf::Vector2i(404, 912), sf::Vector2i(32, 32), sfC::BlockPrototype::TypeBlock::Restart)};

} // namespace sfCON