#pragma once

#include "model.hxx"
#include "view.hxx"

class Controller : public ge211::Abstract_game
{
public:
    explicit Controller(int start);

protected:
    //draws the cities and either the player's path or the shortest path
    void draw(ge211::Sprite_set&) override ;

    //add a city if not in path, remove a city if in path, or toggle drawing
    // the shortest path on and off after the loop is complete
    void on_mouse_up(ge211::Mouse_button, ge211::Position) override;

    //changes the position of mouse_ so that we can connect a line from the
    // last visited city
    void on_mouse_move(ge211::Position) override;

    ge211::Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;

private:
    Model model_;
    View view_;
    ge211::Position mouse_;
};