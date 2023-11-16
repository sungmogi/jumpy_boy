#pragma once
#include <ge211.hxx>
#include <game_config.hxx>

using Position = ge211::Posn<int>;
using Velocity = ge211::Dims<int>;
using Block = ge211::Rect<int>;


class Boy
{
public:
    //constructor
    Boy(Position start, Game_config const& config);

    //Center of Boy
    Position center;

    //This will be used in Model. The game can only be played when Boy is live.
    bool live;

    //radius of Boy. This can be changed in game_config.
    int radius;

    //Initialized to {0,0}. When Boy is live, on_frame will update velocity.
    Velocity velocity;

    //I will use this in view when adding boy sprite.
    Position top_left() const;

    //This will be used to check if the bottom (feet) of the boy hits a block or
    // the bottom of the screen.
    Position feet_position() const;

    //Similar to brickout. This will be used in model to check if the boy will
    // be in a special condition (e.g. hitting bottom) and to update the boy.
    Boy next() const;



    //This will be called in model.on_frame.
    bool on_block(Block const& block);

    //Will be called in model.on_frame.
    bool hit_bottom(Game_config const& config);

    //Will be called in model.on_frame.
    bool hit_obstacle(Block const& block);
};


