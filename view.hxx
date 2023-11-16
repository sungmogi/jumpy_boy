#pragma once

#include "model.hxx"
#include <boy.hxx>
#include <iostream>

class View
{
public:
    //Constructor
    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);

private:
    Model const& model_;

    //Font for displaying score
    ge211::Font sans28_{"sans.ttf", 28};

    ge211::Circle_sprite const boy_sprite;

    ge211::Text_sprite score_sprite_;

    ge211::Rectangle_sprite const block_sprite;

    ge211::Rectangle_sprite const first_block_sprite;

    ge211::Rectangle_sprite const obstacle_sprite;

    ge211::Image_sprite const background_sprite;
};
