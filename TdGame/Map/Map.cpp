#include "Map.h"


bool Map::LoadMap(const std::string& path)
{
     std::ifstream file;
     file.open(path);
     if (!file.good())return false;
     TileMap tile_map_tmp;
     int idx_x=-1, idx_y=-1;
     std::string str_line;
     while (std::getline(file, str_line))
     {
          str_line=trim_str(str_line);
          if (str_line.empty())continue;
          idx_x=-1;
          idx_y++;
          tile_map_tmp.emplace_back();
          std::string str_tile;
          std::stringstream str_stream(str_line);
          while (std::getline(str_stream, str_tile,','))
          {
                idx_x++;
               tile_map_tmp[idx_y].emplace_back();
               Tile& tile = tile_map_tmp[idx_y].back();
               LoadTileFromString(tile, str_tile);
          }
     }
     file.close();
     if (tile_map_tmp.empty()||tile_map_tmp[0].empty())return false;
     tile_map=tile_map_tmp;
     return true;
}

std::string Map::trim_str(const std::string& str)
{
     //因为地图的csv格式是“ 6、57、4、-1 ”，两端会有空格，所以要截取中间部分
     size_t begin_idx = str.find_first_not_of(" \t");
     if (begin_idx == std::string::npos)return "";
     size_t end_idx = str.find_last_not_of(" \t");
     size_t idx_range = end_idx - begin_idx + 1;//注意这里一定要加1
     return str.substr(begin_idx, idx_range);
}

void Map::LoadTileFromString(Tile& tile, const std::string& str)
{
     std::string str_tidy=trim_str(str);
     std::string str_val;
     std::vector<int>values;
     std::stringstream str_stream(str_tidy);
     while (std::getline(str_stream,str_val,'\\'))
     {
          int val;
          try
          {
               val=std::stoi(str_val);
          }
          catch (const std::invalid_argument&)
          {
               val=-1;
          }
          values.push_back(val);
     }
    tile.terrian=(values.size()<1||values[0]<0)?0:values[0];
     tile.decoration=(values.size()<2)?-1:values[1];
     tile.direction=static_cast<Tile::Direction>(values.size()<3||values[2]<0?0:values[2]);
     tile.special_flag=(values.size()<=3)?-1:values[3];
}

size_t Map::get_height() const
{
     return tile_map.size();
}

size_t Map::get_width() const
{
     if (tile_map.empty())return 0;
     return tile_map[0].size();
}



void Map::generate_map_cache()
{
     for (int y=0; y<get_height(); y++)
     {
          for (int x=0; x<get_width(); x++)
          {
               const Tile&tile=tile_map[y][x];
               if (tile.special_flag<0)continue;
               if (tile.special_flag==0)
               {
                    idx_home.x=x;
                    idx_home.y=y;
               }
          }
     }
}



