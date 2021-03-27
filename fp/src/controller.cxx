#include "controller.hxx"

Controller::Controller(int start)
        :model_(start)
        ,view_(model_)
        ,mouse_{0,0}
{
}

void Controller::draw(ge211::Sprite_set& sprites)
{
    background_color = ge211::Color::from_rgba(120,120,120,0.8);
    view_.draw(sprites, mouse_);
}

ge211::Dimensions Controller::initial_window_dimensions() const
{
    return view_.window_dims();
}

std::string Controller::initial_window_title() const
{
    return view_.window_title();
}

void Controller::on_mouse_up(ge211::Mouse_button, ge211::Position pos)
{
    int c;
    c = view_.nearest_city(pos);

    if (model_.player_path().size() == model_.cities().size()+1) {
        if (model_.player_dist() > model_.shortest_dist() + 0.5) {
            if (pos.x<200&&pos.y>850) view_.short_switch();
            else {
                model_ = Model(model_.cities().size());
                view_.button_switch();
                if(view_.isactivated())view_.short_switch();
            }
        } else {
            if (model_.cities().size()<10) {
                model_ = Model(model_.cities().size()+ 1);
                view_.setCorrect();
                if (view_.getbutton()) {
                    view_.button_switch();
                }
            } else {
                view_.setWin();
            }
        }
    }
    else if (model_.contains_all_cities()) {
        if (c == model_.player_path()[0]) {
            model_.add_to_player_path(c);
            model_.pauseplaytime();
            if (model_.player_dist() > model_.shortest_dist() + 0.5) {
                view_.button_switch();
            } else {
                view_.setCorrect();
            }
        } else {
            model_.remove_from_player_path(c);
        }
    } else if (model_.is_in_path(c)) {
        model_.remove_from_player_path(c);
    } else {
        model_.add_to_player_path(c);
    }
}

void Controller::on_mouse_move(ge211::Position pos)
{
    mouse_ = pos;
}