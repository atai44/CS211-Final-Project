#include "view.hxx"
#include <math.h>

using namespace ge211;

Color const red {200,20,0};
Color const green{0,128,0};
View::View(Model const& model)
        : model_(model)
{

}

void View::draw(ge211::Sprite_set& set, ge211::Position pos)
{


    if(gamewon) drawWin(set);

    set.add_sprite(bfd_time_label, {0,0});
    bfd_time.reconfigure(ge211::Text_sprite::Builder(sans30) << model_.bf_time());
    set.add_sprite(bfd_time, {0,40});

    set.add_sprite(ptimelabel_, {650,0});
    ptime_.reconfigure(ge211::Text_sprite::Builder(sans30) << model_
    .getplaytime());
    set.add_sprite(ptime_, {650, 40});

    for (int i = 0; i < model_.cities().size(); ++i) {
        if (model_.is_in_path(i)) {
            set.add_sprite(visited_city_token_, {model_.cities()[i].x-5,
                                                 model_.cities()[i].y-5}, 1);
        } else {
            set.add_sprite(unvisited_city_token_, {model_.cities()[i].x-5,
                                                   model_.cities()[i].y-5}, 1);
        }
    }

    if (correct) {
        set.add_sprite(correctmsg, {300,300}, 2);
    }

    if(activated) {
        drawshort(set);
    }

    else {
        if (model_.player_path().size() > 1) {
            for (int k = 0; k < model_.player_path().size() - 1; ++k) {
                drawLine(set, model_.cities()[model_.player_path()[k]],
                         model_.cities
                                       ()[model_.player_path()[k + 1]]);
            }
        }

        if (model_.player_path().size() > 0 &&
            model_.player_path().size() <= model_.cities().size()) {
            drawLine(set,
                     model_.cities()[model_.player_path()[
                             model_.player_path().size() - 1]],
                     pos);
        }
    }


    bfd_.reconfigure(
            ge211::Text_sprite::Builder(sans30) << model_.shortest_dist());

    pd_.reconfigure(
            ge211::Text_sprite::Builder(sans30) << model_.player_dist());

    if (button) {
        set.add_sprite(button_, {0,850});
        set.add_sprite(bfd_, {30,850}, 1);
        set.add_sprite(bfd_label_, {0, 800}, 1);
    }


    set.add_sprite(pd_, {700, 850}, 1);
    set.add_sprite(pd_label_, {700, 800}, 1);
}

int View::nearest_city(ge211::Position mypos) const
{
    int ret;
    double dist = INT_MAX;
    for (int i = 0; i < model_.cities().size(); ++i) {
        if ((model_.cities()[i].x - mypos.x)*(model_.cities()[i].x - mypos.x)
         + (model_.cities()[i].y - mypos
        .y)*(model_.cities()[i].y - mypos.y) < dist) {
            ret = i;
            dist = (model_.cities()[i].x - mypos.x)*(model_.cities()[i].x - mypos.x)
                   + (model_.cities()[i].y - mypos
                    .y)*(model_.cities()[i].y - mypos.y);
        }
    }
    return ret;
}

void View::drawLine(ge211::Sprite_set& set, ge211::Position pos1,
        ge211::Position pos2)
{

    double dist = sqrt(pow(pos1.x-pos2.x, 2)+pow(pos1.y-pos2.y,2));
    int half = (int) dist/2;
    int x = (pos1.x+pos2.x)/2 - half;
    int y =(pos1.y+pos2.y)/2;
    double d=0;
    if (pos2.x-pos1.x>0) {
        d = 180 / 3.14159265 * asin((pos2.y - pos1.y) / dist);
    }
    if (pos2.x-pos1.x<0) {
        d = -180 / 3.14159265 * asin((pos2.y - pos1.y) / dist);
    }

    my_trans = Transform::scale_x(dist) * Transform::rotation(d);

    set.add_sprite(line_, {x,y}, 1, my_trans);
}

void View::drawWin(ge211::Sprite_set& set)
{
    set.add_sprite(win_, {200,200}, 2);
}

void View::drawshort(ge211::Sprite_set &set)
{
    for (int j = 0; j < model_.cities().size()-1; ++j) {
      drawLine(set, model_.cities()[model_.shortest_path()[j]], model_.cities
      ()[model_.shortest_path()[j+1]]);
    }
    drawLine(set, model_.cities()[model_.shortest_path()[model_.cities().size
    ()-1]], model_.cities()[0]);
}

Dimensions View::window_dims() const
{
    return {900, 900};
}

std::string View::window_title() const
{
    return "Salesman";
}
