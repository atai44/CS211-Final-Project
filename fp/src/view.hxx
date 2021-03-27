#pragma once

#include "model.hxx"

#include <string>

extern ge211::Color const red,green;

class View
{
public:

    explicit View(Model const&);

    void draw(ge211::Sprite_set& set, ge211::Position);

    ge211::Dimensions window_dims() const;

    std::string window_title() const;

    //given a position (by mouse click), return index of nearest city
    int nearest_city(ge211::Position) const;

    //toggles whether we show the shortest path
    void short_switch() {
        activated = !activated;
    }

    //tells us whether we are currently showing shortest path
    bool isactivated() {
        return activated;
    }

    //toggles whether we display the button that toggles shortest path, also
    // toggles whether we display the distance
    void button_switch() {
        button = !button;
    }

    bool getbutton() {
        return button;
    }

    void drawWin(ge211::Sprite_set& set);

    //controls the player winning the game
    void setWin() {
        gamewon = true;
    }

    //toggles whether the "Correct!" message is displayed
    void setCorrect() {
        correct = !correct;
    }

private:

    bool activated=false;
    bool button = false;
    bool gamewon = false;
    bool correct = false;

    Model const& model_;

    //sprites for the cities
    ge211::Circle_sprite const unvisited_city_token_ {10, red};
    ge211::Circle_sprite const visited_city_token_ {10, green};

    //sprites for the information about brute force
    ge211::Font sans30{"sans.ttf",30};
    ge211::Text_sprite bfd_{std::to_string(model_.shortest_dist()), sans30};
    ge211::Text_sprite bfd_label_{"Shortest: (click below to show)",
                                 sans30};
    ge211::Text_sprite bfd_time{std::to_string(model_.bf_time()), sans30};
    ge211::Text_sprite bfd_time_label{"Time for brute force (s): ", sans30};

    //sprites for the information about the player
    ge211::Text_sprite pd_{std::to_string(model_.player_dist()), sans30};
    ge211::Text_sprite pd_label_{"Your Path:", sans30};
    ge211::Text_sprite ptime_{std::to_string(model_.getplaytime()), sans30};
    ge211::Text_sprite ptimelabel_{"Time elapsed (s): ", sans30};

    //winning sprite
    ge211::Font sans100{"sans.ttf",100};
    ge211::Text_sprite win_{"You Win!", sans100};

    //correct path sprite
    ge211::Text_sprite correctmsg{"Correct!", sans100};

    //line sprite
    ge211::Rectangle_sprite line_{{1,4}, green};

    //sprite for button to toggle showing shortest path
    ge211::Rectangle_sprite button_{{200,50}, green};

    ge211::Transform my_trans;

    //draws a line between two points
    void drawLine(ge211::Sprite_set& set, ge211::Position, ge211::Position);

    //draws the shortest path
    void drawshort(ge211::Sprite_set& set);
};