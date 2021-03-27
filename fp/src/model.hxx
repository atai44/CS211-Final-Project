#pragma once

#include <ge211.hxx>
#include <vector>
#include <climits>

//
// TODO: Sketch the structure of your model and declare its operations.
//

class Model
{
public:

    //Constructs a model with n cities
    //the constructor will initialize an array of Positions with random
    // positions (as long as they aren't too close). Also will calculate the
    // shortest path
    Model(int n);

    std::vector<ge211::Position> cities() const {
        return cities_;
    }

    std::vector<int> player_path() const {
        return player_path_;
    }

    std::vector<int> shortest_path() const {
        return shortest_path_;
    }

    double bf_time() const {
        return bf_time_;
    }


    double shortest_dist() const {
        return shortest_dist_;
    }

    double player_dist() const {
        return player_dist_;
    }

    //finds the shortest path by brute force
    // Also tracks time to compute and stores the shortest distance
    void find_shortest_path_bf();

    //adds a city with the index as the input; responsible for live updates of
    // player_dist_
    void add_to_player_path(int);

    //removes the city with index int from path
    //also responsible for updating player_dist_
    void remove_from_player_path(int);

    //returns whether a city is in the player path
    bool is_in_path(int) const;

    //Returns whether player_path_ contains every city
    bool contains_all_cities() const;

    //calculates the distance of a path visiting the cities represented by
    // the input vector, in order
    double path_distance(std::vector<int>) const;

    //calculates the distance between two cities, given their indices
    double distance(int, int) const;

    //access the player timer
    double getplaytime() const;

    //pause the player timer
    void pauseplaytime() {
        playtime.pause();
    }

private:

    /// Members
    std::vector<ge211::Position> cities_ = {};
    std::vector<int> player_path_ = {};
    std::vector<int> shortest_path_ = {};
    std::vector<int> current_path = {};
    double bf_time_=0;
    double shortest_dist_ = INT_MAX;
    double player_dist_ = 0;
    std::vector<std::vector<double> > dist_mat_;
    ge211::Pausable_timer playtime;

    /// Helpers
    //compute a matrix of distances between the cities
    void dist_matrix();

};