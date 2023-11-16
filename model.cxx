#include "model.hxx"

//construct model with dimensions
static Position
above_block(
        Block const& block, Game_config const& config)
{
    // TODO: replace this with your code:
    Position block_tl = block.top_left();
    block_tl = block_tl.up_by(config.boy_radius);
    block_tl = block_tl.right_by(block.width / 2);

    return block_tl;
}

Model::Model(Game_config const& config)
        :
          score {0},
          first_block(config.scene_dims.width/2 - config.block_dims.width/2,
                      config
          .scene_dims.height * 5/6,
                      config.block_dims.width, config.block_dims.height),
          boy(above_block(first_block, config), config),
          is_game_over (false)

{
    ge211::Random_source<int> source(ge211::unbounded);
    for (int i = 0; i < config.block_num; i++){
        int block_x = source(0, config.scene_dims.width - config.block_dims
                .width);
        int block_y = config.scene_dims.height / config.block_num * i;
        int block_w = config.block_dims.width;
        int block_h = config.block_dims.height;
        Block new_block = Block::from_top_left({block_x, block_y},
                                               {block_w, block_h});
        if (i == config.block_num -1) {
            new_block = first_block;
        }
        blocks.push_back(new_block);
    }

    for (int i = 0; i <config.obs_num; i++) {
        int obs_x = source(0, config.scene_dims.width - config.obs_dims.width);

        int obs_y = source(0, config.scene_dims.height - config.obs_dims
        .height);
        int obs_w = config.obs_dims.width;
        int obs_h = config.obs_dims.height;
        Block new_obs = Block::from_top_left({obs_x, obs_y},
                                             {obs_w, obs_h});
        obs.push_back(new_obs);
    }
}

void
Model::generate_block_on_top()
{
    ge211::Random_source<int> source(ge211::unbounded);
    int block_x = source(0, config.scene_dims.width - config.block_dims
                                                            .width);

    int block_y = 0;
    int block_w = config.block_dims.width;
    int block_h = config.block_dims.height;
    Block new_block = Block::from_top_left({block_x, block_y},
                                           {block_w, block_h});
    blocks.push_back(new_block);
}

void
Model::generate_ob_on_top()
{
    ge211::Random_source<int> source(ge211::unbounded);
    int obs_x = source(0, config.scene_dims.width - config.obs_dims.width);

    int obs_w = config.obs_dims.width;
    int obs_h = config.obs_dims.height;
    Block new_obs = Block::from_top_left({obs_x, 0}, {obs_w, obs_h});
    obs.push_back(new_obs);
}

double
Model::set_vel_y(double el_time)
{
    double v = -10;
    double gravity = 10;
    v += gravity * el_time;
    return v;
}

void
Model::game_over_state()
{
    is_game_over = true;
    blocks.clear();
    obs.clear();
    boy = Boy(above_block(first_block, config), config);
}

void
Model::on_frame(double dt)
{
    if (boy.live) {
        Boy next_boy = boy.next();
        elapsed_time += dt;
        //boy jumping up and down
        boy.velocity.height = set_vel_y(elapsed_time);
        //boy hits left side
        if (boy.top_left().x <= 0){
            boy.center.x = boy.radius;
        }
        //boy hits right side
        if (boy.center.x + boy.radius > config.scene_dims.width){
            boy.center.x = config.scene_dims.width - boy.radius;
        }
        //boy hits bottom
        if (next_boy.hit_bottom(config)) {
            elapsed_time = 0;
            game_over_state();
        }
        //boy hits another block
        for (Block &block : blocks){
            if (next_boy.on_block(block)){
                for (Block &block_to_move : blocks){
                    block_to_move.y += config.scene_dims.height / config
                            .block_num;
                }
                for (Block &obs_to_move : obs){
                    obs_to_move.y += config.scene_dims.height / config
                            .block_num;
                }
                elapsed_time = 0;
                boy.velocity.height = set_vel_y(elapsed_time);
                generate_block_on_top();

                score += config.scene_dims.height / config
                        .block_num;
            }
            if (block.top_left().y > config.scene_dims.height){
                block = blocks.back();
                blocks.pop_back();
            }
        }
        for (Block &ob : obs){
            if (next_boy.hit_obstacle(ob)){
                game_over_state();
            }
            else if (ob.top_left().y > config.scene_dims.height){
                ob = obs.back();
                obs.pop_back();
            }
        }
        if (obs.size() < static_cast<std::size_t>(config.obs_num) &&
        !is_game_over){
            generate_ob_on_top();
        }
        boy = boy.next();
    }
}

void
Model::reset_game()
{
    is_game_over = false;
    score = 0;
    boy = Boy(above_block(first_block, config), config);
    blocks.clear();
    obs.clear();
    ge211::Random_source<int> source(ge211::unbounded);
    for (int i = 0; i < config.block_num; i++){
        int block_x = source(0, config.scene_dims.width - config.block_dims
        .width);
        int block_y = config.scene_dims.height / config.block_num * i;
        int block_w = config.block_dims.width;
        int block_h = config.block_dims.height;
        Block new_block = Block::from_top_left({block_x, block_y},
                                               {block_w, block_h});
        if (i == config.block_num -1) {
            new_block = first_block;
        }
        blocks.push_back(new_block);
    }
    for (int i = 0; i <config.obs_num; i++) {
        int obs_x = source(0, config.scene_dims.width -
        config.obs_dims.width);
        int obs_y = source(0, config.scene_dims.height -
        config.obs_dims.height);
        int obs_w = config.obs_dims.width;
        int obs_h = config.obs_dims.height;
        Block new_obs = Block::from_top_left({obs_x, obs_y},
                                             {obs_w, obs_h});
        obs.push_back(new_obs);
    }
}