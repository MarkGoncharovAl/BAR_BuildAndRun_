#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>
#include "MapPrototypes.hpp"

namespace sfC
{

    class Map : public sf::Drawable, public sf::Transformable
    {
    public:
        /////////////////////////////////////////////////////
        // Constructor
        // file - where is current_picture (Start folder is the project folder)
        // new_map - the base of map (choose from Map/Map_properties.h)
        /////////////////////////////////////////////////////
        Map(const std::string &file, const MapPrototype &new_map);
        Map(const std::string &file);

        void create_map(const MapPrototype &new_map);

        /////////////////////////////////////////////////////
        // Return absolute coordinates of the desired
        //    window based coordinates
        //
        // Was done faster and simpler but now - use only for fast purposes (dangerous)
        /////////////////////////////////////////////////////
        sf::Vector2i AbsCoords(int x, int y) const { return sf::Vector2i(x / map_.GetBlockSize().x, y / map_.GetBlockSize().y); }
        sf::Vector2i AbsCoords(float x, float y) const { return AbsCoords(static_cast<int>(x), static_cast<int>(y)); }
        sf::Vector2i AbsCoords(sf::Vector2f coords) const { return AbsCoords(static_cast<int>(coords.x), static_cast<int>(coords.y)); }

        /////////////////////////////////////////////////////
        // Check: are coordinates empty
        /////////////////////////////////////////////////////
        bool is_solid(const sf::Vector2f &coords) const;

        bool is_sand(const sf::Vector2f &coords) const;
        bool is_accel(const sf::Vector2f &coords) const;
        bool is_restart(const sf::Vector2f &coords) const;
        /////////////////////////////////////////////////////
        // Check: is the full rect empty
        /////////////////////////////////////////////////////
        bool is_solid(const sf::FloatRect &rect) const;
        bool is_finish(sf::FloatRect &&rect) const;

        bool change_rect(int num_block, const sf::IntRect &rect);
        /////////////////////////////////////////////////////
        // Change currrent texture and properties of block
        // position (INT) - the poistion of BLOCK (not coordinate)
        // new_text       - the number of texture
        //
        // return true if block was changed - false if not
        /////////////////////////////////////////////////////
        bool change_block(const sf::Vector2i &position, sfC::BlockPrototype::TypeBlock new_text) { return change_block(position, static_cast<int>(new_text)); }
        bool change_block(const sf::Vector2i &position, int new_text);

        sfC::BlockPrototype::TypeBlock get_type_block(const sf::Vector2i &block) const;

        MapPrototype get_map_prototype() const { return map_; }
        sf::Vector2f GetSize() const { return sf::Vector2f(map_.GetTotalSize()); }

    private:
        /////////////////////////////////////////////////////
        // Complexity function that called itself.
        // Don't use without understanding what happening
        /////////////////////////////////////////////////////
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

        sf::VertexArray vertices_;
        sf::Texture tileset_;
        MapPrototype map_;
    };

} // namespace sfC