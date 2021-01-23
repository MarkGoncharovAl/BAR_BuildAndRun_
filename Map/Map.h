#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>
#include "Map_Prototypes.h"
#include "../Help/Help.hpp"
#include "../Common_libs/errors.hpp"

namespace M
{

    class Map : public sf::Drawable, public sf::Transformable
    {
    public:
        /////////////////////////////////////////////////////
        // Constructor
        // file - where is current_picture (Start folder is the project folder)
        // new_map - the base of map (choose from Map/Map_properties.h)
        /////////////////////////////////////////////////////
        Map(const std::string &file, const Map_Prototype &new_map) noexcept;
        Map(const std::string &file) noexcept;

        void create_map(const M::Map_Prototype &new_map) noexcept;

        /////////////////////////////////////////////////////
        // Return absolute coordinates of the desired
        //    window based coordinates
        //
        // Was done faster and simpler but now - use only for fast purposes (dangerous)
        /////////////////////////////////////////////////////
        inline sf::Vector2i AbsCoords(int x, int y) const noexcept { return sf::Vector2i(x / map_.block_size_.x, y / map_.block_size_.y); }
        inline sf::Vector2i AbsCoords(float x, float y) const noexcept { return AbsCoords(static_cast<int>(x), static_cast<int>(y)); }
        inline sf::Vector2i AbsCoords(sf::Vector2f coords) const noexcept { return AbsCoords(static_cast<int>(coords.x), static_cast<int>(coords.y)); }

        /////////////////////////////////////////////////////
        // Check: are coordinates empty
        /////////////////////////////////////////////////////
        bool is_solid(const sf::Vector2f &coords) noexcept;

        bool is_sand(const sf::Vector2f &coords) noexcept;
        bool is_accel(const sf::Vector2f &coords) noexcept;
        bool is_restart(const sf::Vector2f &coords) noexcept;
        /////////////////////////////////////////////////////
        // Check: is the full rect empty
        /////////////////////////////////////////////////////
        bool is_solid(const sf::FloatRect &rect) noexcept;

        bool is_finish(sf::FloatRect &&rect) noexcept;

        /////////////////////////////////////////////////////
        // Create random blocks
        // num_block    - the type of new block
        // count_blocks - amount of new blocks
        /////////////////////////////////////////////////////
        bool create_random(int num_block, std::size_t count_blocks, const sf::IntRect &rect) noexcept;

        bool change_rect(int num_block, const sf::IntRect &rect) noexcept;

        /////////////////////////////////////////////////////
        // Change currrent texture and properties of block
        // position (INT) - the poistion of BLOCK (not coordinate)
        // new_text       - the number of texture
        //
        // return true if block was changed - false if not
        /////////////////////////////////////////////////////
        bool change_block(const sf::Vector2i &position, int new_text) noexcept;

        M::BLOCKS get_type_block(const sf::Vector2i &block) noexcept;

        Map_Prototype get_map_prototype() const noexcept { return map_; }

        inline float get_size_x() const noexcept { return static_cast<float>(map_.total_size_.x); }
        inline float get_size_y() const noexcept { return static_cast<float>(map_.total_size_.y); }

    private:
        /////////////////////////////////////////////////////
        // Complexity function that called itself.
        // Don't use without understanding what happening
        /////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

        sf::VertexArray vertices_;
        sf::Texture tileset_;
        Map_Prototype map_;
    };

} // namespace M