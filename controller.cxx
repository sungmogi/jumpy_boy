#include "controller.hxx"

Controller::Controller(Model& model)
        : model_(model),
          view_(model)
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

void
Controller::on_key(ge211::Key key)
{
    if (key == ge211::Key::code(' ')) {
        model_.boy.live = true;
        if (model_.is_game_over) {
            model_.reset_game();
        }
    }
}

void
Controller::on_mouse_move(Position mouse_posn)
{
    if (model_.boy.live) {
        model_.boy.center.x = mouse_posn.x;
    }
}

ge211::Dims<int>
Controller::initial_window_dimensions() const
{
    return model_.config.scene_dims;
}

void
Controller::on_frame(double dt)
{
    model_.on_frame(dt);
}