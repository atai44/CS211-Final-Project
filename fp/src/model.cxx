#include "model.hxx"
#include <bits/stdc++.h>

using namespace ge211;

Model::Model(int n)
{
    srand(std::time(0));
    for (int i = 0; i < n; ++i) {
        Position tpos{rand() % 790+10, rand() % 740+60};
        bool far = true;
        do {
            tpos.x = rand()%790+10;
            tpos.y = rand()%740+60;
            far = true;
            for (int j = 0; j < i; ++j) {
                if ((tpos.x - cities_[j].x)*(tpos.x - cities_[j].x) + (tpos.y
                - cities_[j].y)*(tpos.y - cities_[j].y) < 400) far = false;
            }
        } while (!far);
        if (far) cities_.push_back(tpos);
    }
    dist_matrix();
    find_shortest_path_bf();
    playtime.reset();
}

double Model::getplaytime() const
{
    return playtime.elapsed_time().seconds();
}

void Model::find_shortest_path_bf()
{
    Timer mytime;
    for (int i = 1; i < cities_.size(); ++i) current_path.push_back(i);

    do {
        double dist = 0;

        int k = 0;
        for (int i = 0; i < current_path.size(); i++) {
            dist += dist_mat_[k][current_path[i]];
            k = current_path[i];
        }
        dist += dist_mat_[k][0];
        if (dist < shortest_dist_) {
            shortest_dist_ = dist;
            shortest_path_ = current_path;
        }
    } while (std::next_permutation(current_path.begin(), current_path.end()));
    shortest_path_.insert(shortest_path_.begin(),0);
    shortest_path_.push_back(0);
    bf_time_ = mytime.reset().seconds();
}



void Model::add_to_player_path(int ind)
{
    player_path_.push_back(ind);
    player_dist_ = path_distance(player_path());
}

void Model::remove_from_player_path(int targ)
{
    for (auto i = 0; i<player_path().size(); ++i) {
        if (player_path_[i] == targ) player_path_.erase(player_path_.begin
        ()+i);
    }
    player_dist_ = path_distance(player_path());
}

bool Model::is_in_path(int j) const
{
    for (int i = 0; i < player_path_.size(); ++i) {
        if(player_path_[i] == j) return true;
    }
    return false;
}

double Model::distance(int n, int m) const
{
    return sqrt((cities_[n].x-cities_[m].x)*(cities_[n].x-cities_[m].x) +
    (cities_[n].y-cities_[m].y)*(cities_[n].y-cities_[m].y));
}

void Model::dist_matrix()
{
    for (int i = 0; i<cities_.size(); ++i) {
        std::vector<double> row;
        for (int j = 0; j < cities_.size(); ++j) {
            row.push_back(distance(i,j));
        }
        dist_mat_.push_back(row);
    }
}

double Model::path_distance(std::vector<int> vec) const
{
    double ret=0;
    if (vec.size()>1) {
        for (int i = 0; i < vec.size() - 1; ++i) {
            ret = ret + dist_mat_[vec[i]][vec[i + 1]];
        }
    }
    return ret;
}

bool Model::contains_all_cities() const
{
    return player_path_.size() == cities_.size();
}