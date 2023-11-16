
#pragma once

#include <ge211.hxx>

class Game_config{
  public:
    //Constructor
    Game_config();

    ge211::Dims<int> scene_dims;

    ge211::Dims<int> block_dims;

    ge211::Dims<int> obs_dims;

    int block_num;

    int obs_num;

    int boy_radius;
};