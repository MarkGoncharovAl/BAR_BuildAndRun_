#include "MapPrototypes.hpp"

#include "SetMap.hpp"

std::vector<std::string> sfDATA::MapPrototypes_t::maps;
constexpr char sfDATA::MapPrototypes_t::main_file [];

bool sfDATA::MapPrototypes_t::insert_map (const std::string& name , const sfC::MapPrototype& map)
{
    std::vector<std::string>::iterator cur_iter = std::find (maps.begin () , maps.end () , name);

    if (cur_iter != maps.end ())
    {
        write_map_into_file ("../MapTiles/" + name + ".txt" , map);
        return true;
    }
    else if (maps.size () <= max_size)
    {
        maps.push_back (name);
        write_name_new_map (name);
        write_map_into_file ("../MapTiles/" + name + ".txt" , map);
        return true;
    }

    return false;
}

void sfDATA::MapPrototypes_t::write_map_into_file (const std::string& file , const sfC::MapPrototype& map)
{
    std::ofstream out (file , std::ios::out);

    map.dump_interrior (out);
    if (!out.good ())
    {
        LOG_error << "File wasn't writen down properly!";
        exit (EXIT_FAILURE);
    }

    out.close ();
}

void sfDATA::MapPrototypes_t::write_name_new_map (const std::string& file)
{
    std::fstream cur_file (sfDATA::MapPrototypes_t::main_file , std::ios::app);
    cur_file << file << std::endl;
    cur_file.close ();
}

void sfDATA::MapPrototypes_t::PrepareData ()
{
    std::ifstream cur_file (sfDATA::MapPrototypes_t::main_file , std::ios::in);
    if (!cur_file.is_open ())
    {
        LOG_error << std::string ("Can't open the main file ") + sfDATA::MapPrototypes_t::main_file;
        exit (EXIT_FAILURE);
    }
    while (!cur_file.eof ())
    {
        std::string cur_str;
        cur_file >> cur_str;
        if (cur_str.empty ())
            break;

        sfDATA::MapPrototypes_t::maps.push_back (cur_str);
    }

    cur_file.close ();

    SetMap_t::PrepareData (maps);
}