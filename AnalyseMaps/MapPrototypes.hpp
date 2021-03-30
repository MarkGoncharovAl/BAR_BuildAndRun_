#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Map/MapPrototypes.hpp"

namespace sfDATA
{
    class MapPrototypes_t
    {
    public:
        ////////////////////
        // return true if map was pushed
        // return false if stack is full
        ////////////////////
        static bool insert_map (const std::string& name , const sfC::MapPrototype& map);
        static void write_map_into_file (const std::string& file , const sfC::MapPrototype& map);
        static void write_name_new_map (const std::string& file);


        static void PrepareData ();
        static inline size_t GetSizeMaps () { return maps.size (); }
        static inline const std::string& GetNameMap (size_t num) { return maps[num]; }

    private:
        static constexpr char main_file [] = "../MapTiles/!FULL-DATA.txt";
        static std::vector<std::string> maps;
        static constexpr size_t max_size = 128;
    };
}