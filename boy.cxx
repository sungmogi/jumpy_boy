
#include "boy.hxx"

Boy::Boy(Position start, Game_config const& game_config)
        :
          center(start),
          live(false),
          radius(game_config.boy_radius),
          velocity({0,0})
{}

Position
Boy::top_left() const
{
    Position boy_tl = center.left_by(radius);
    boy_tl = boy_tl.up_by(radius);
    return boy_tl;
}

Boy
Boy::next() const
{
    Boy result(*this);
    result.center = result.center.down_by(result.velocity.height /4);
    return result;
}

Position
Boy::feet_position() const
{
    return {center.x, center.y + radius};
}

bool
Boy::on_block(const Block& block)
{
    int lowest_x = block.top_left().x;
    int highest_x = block.top_right().x;
    int top_y = block.top_left().y;
    bool in_range_y = (feet_position().y < top_y + 5) && (feet_position().y
            > top_y - 1);
    if ((center.x >= lowest_x) && (center.x <= highest_x) && (in_range_y) &&
         (velocity.height >= 0)){
        return true;
    }
    return false;
}

bool
Boy::hit_bottom(const Game_config& config)
{
    return feet_position().y > config.scene_dims.height;
}

bool
Boy::hit_obstacle(Block const& block)
{
    if (center.x - radius > block.x + block.width){
        return false;
    }
    if (center.x + radius < block.x){
        return false;
    }
    if (center.y - radius > block.y + block.height){
        return false;
    }
    if (center.y + radius < block.y){
        return false;
    }
    return true;
}

