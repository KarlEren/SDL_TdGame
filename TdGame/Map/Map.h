#pragma once
#include "tile.h"
#include <SDL.h>
#include <string>
#include <fstream>
#include <sstream>
class Map
{
public:
    Map()=default;
    ~Map()=default;
    bool LoadMap(const std::string& path);
private:
    TileMap tile_map;
    SDL_Point idx_home={0};//防守点位
    std::string trim_str(const std::string& str);
    void LoadTileFromString(Tile&tile,const std::string& str);
    void generate_map_cache();
    size_t get_width()const;
    size_t get_height()const;
    
};
