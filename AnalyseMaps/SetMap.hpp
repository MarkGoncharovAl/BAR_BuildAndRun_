#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../Map/Map.hpp"
#include "../Help/Text/Text.hpp"
#include "../Help/Picture/Picture.hpp"
#include "../Help/FastDraw.hpp"

namespace sfDATA
{
    class SetMap_t
    {
    public:
        static void PrepareData (std::vector<std::string>& maps);
        static std::string GetText ();
        static void IncreaseMap ();
        static void DecreaseMap ();
        static inline bool IsIncludeDirect (float x , float y) { return direct_back.is_include (x , y); }
        static void DrawEverything (sfC::Window& window);

        static void PrepareCreateMap (sfC::Window& , sfC::Map&);

        enum class OutT {Continue, Error, Changed, Exit};
        static OutT AnalysePrepareCreateMap (sfC::Window&);

    private:
        static sfC::Text_t main_text;

        static size_t cur_map;
        static sfC::Text_t cur_text;

        static sfC::Picture_t direct_back;
    };
}