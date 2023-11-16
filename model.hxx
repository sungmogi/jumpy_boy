#pragma once

#include <ge211.hxx>
#include <boy.hxx>
#include <game_config.hxx>

using Block = ge211::Rect<int>;

class Model
{
public:
    //Constructor
    explicit Model(Game_config const& config = Game_config());

    Game_config const config;

    //Will be displayed as game is played as well as when it is over.
    int score;

    std::vector<Block> blocks;

    std::vector<Block> obs;

    //The bottom most block when game is reset. Boy will be initialized to be on
    //top of this.
    Block first_block;

    Boy boy;

    //Will be set to true when Boy hits bottom or obstacle.
    bool is_game_over;

    //As Boy moves upwards, more block will be generated.
    void generate_block_on_top();

    //As Boy moves upwards, more obstacles will be generated.
    void generate_ob_on_top();

    //This will let Boy bounce and move, as well as updating the position of
    // the blocks and obstacles. This will also be used to set game as over.
    void on_frame(double dt);

    //When game is over, this will be called when player presses space bar.
    // This will set the game as not over and reset the blocks and obstacles.
    void reset_game();

    //This will be called when the player hits the bottom or the obstacle.
    void game_over_state();

private:
    //These will help me calculate the velocity of Boy. dt will be used to
    // update elapsed_time and elapsed_time will be used to calculate
    // set_vel_y. Set_vel_y will be used to update the velocity.y of Boy.
    double elapsed_time;
    double set_vel_y(double el_time);

};
