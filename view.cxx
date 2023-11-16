#include <view.hxx>

static ge211::Color const boy_color {0,255,0};
static ge211::Color const block_color {200,180,120};
static ge211::Color const first_block_color {200, 200, 200};
static ge211::Color const obstacle_color {255, 0,0};

View::View(Model const& m)
        : model_(m),
          boy_sprite(model_.boy.radius, boy_color),
          block_sprite(m.config.block_dims, block_color),
          first_block_sprite(m.config.block_dims, first_block_color),
          obstacle_sprite(m.config.obs_dims, obstacle_color),
          background_sprite("Jumpy_BG.PNG")

{}

void
View::draw(ge211::Sprite_set& set)
{
    ge211::Text_sprite::Builder score_builder(sans28_);
    score_builder << "Score: " << model_.score;
    score_sprite_.reconfigure(score_builder);
    if (!model_.is_game_over) {
        set.add_sprite(score_sprite_, {10, 0}, 5);
    }
    else {
        set.add_sprite(score_sprite_, {183, 120}, 5);

    }
    set.add_sprite(background_sprite, {0,0}, 1);
    set.add_sprite(boy_sprite, model_.boy.top_left() ,4);
    for (Block block : model_.blocks){
        if (block == model_.first_block) {
            set.add_sprite(first_block_sprite, {static_cast<int>(block.x),
                                          static_cast<int>(block.y)}, 3);
        }
        set.add_sprite(block_sprite, {block.x, block.y}, 2);
    }
    for (Block obs : model_.obs){
        set.add_sprite(obstacle_sprite, {obs.x, obs.y}, 4);
    }
}