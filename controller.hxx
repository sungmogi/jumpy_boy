#pragma once

#include "model.hxx"
#include "view.hxx"
#include <game_config.hxx>

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    //Constructor
    Controller(Model& model);

protected:
    void draw(ge211::Sprite_set& set) override;

    //Space bar should be used to start game and reset after it is over.
    void on_key(ge211::Key) override;

    //Mouse position will be used to move the Boy left and right.
    void on_mouse_move(Position) override;

    ge211::Dims<int> initial_window_dimensions() const override;

    void on_frame(double dt) override;

private:
    Model& model_;
    View view_;
};
