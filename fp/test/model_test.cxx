#include "model.hxx"
#include <catch.hxx>
#include <iostream>

TEST_CASE("City Construction")
{
    Model m(4);
    CHECK(m.cities().size()==4);
}

TEST_CASE("Add and remove one city")
{
    Model m(4);
    m.add_to_player_path(0);
    CHECK(m.player_path().size() == 1);
    m.remove_from_player_path(0);
    CHECK(m.player_dist() == 0);
    CHECK(m.player_path().size() == 0);
}

TEST_CASE("test is_in_path and check that distances updating properly") {
    Model m(3);
    m.add_to_player_path(2);
    CHECK(m.is_in_path(2));
    m.add_to_player_path(1);
    CHECK(m.player_dist()==m.path_distance({2,1}));
    m.remove_from_player_path(2);
    CHECK(m.player_dist()==0);
    CHECK_FALSE(m.is_in_path(2));
}

TEST_CASE("testing path_distance") {
    //sometimes the tests will fail due to roundoff error, but if you look at
    // the debugger output the numbers are actually the same

    Model m(3);
    //check that an empty path has 0 length
    CHECK(m.path_distance({})==0);
    //check that a path with one city has 0 length
    CHECK(m.path_distance({0})==0);
    //check that a path is the same forwards and backwards
    CHECK(m.path_distance({0,1,2}) == m.path_distance({2,1,0}));
    //check path_distance against the distance function
    CHECK(m.path_distance({0,1,2}) == m.distance(0,1) + m.distance(1,2));
    CHECK(m.path_distance({0,1})==m.distance(0,1));
    //check path_distance against hard math (also implicitly testing the
    // distance function against the hard math since we've established that
    // path_distance agrees with distance function)
    CHECK(m.path_distance({0,1})==sqrt(pow(m.cities()[0].x-m.cities()[1].x,2)
    + pow(m.cities()[0].y-m.cities()[1].y,2)));
}

TEST_CASE("test that we're actually finding correct solution") {
    Model m(4);

    //check that the shortest path is the right size
    CHECK(m.shortest_path().size() == 5);
    //check that the shortest path ends at the starting city
    CHECK(m.shortest_path()[4]==0);
    //check that all the cities are in the path
    bool all_cities = true;
    bool inpath;
    for (int i = 0; i <4 ; ++i) {
        inpath = false;
        for (int j = 0; j < 4; ++j) {
            if (m.shortest_path()[j]==i) inpath = true;
        }
        if (!inpath) all_cities = false;
    }
    CHECK(all_cities);
    //check shortest distance against all possible
    CHECK(m.shortest_dist()<=m.path_distance({0,1,2,3,0}));
    CHECK(m.shortest_dist()<=m.path_distance({0,1,3,2,0}));
    CHECK(m.shortest_dist()<=m.path_distance({0,2,1,3,0}));
}

TEST_CASE("test contains_all_cities") {
    Model m(3);
    m.add_to_player_path(0);
    CHECK_FALSE(m.contains_all_cities());
    m.add_to_player_path(1);
    CHECK_FALSE(m.contains_all_cities());
    m.add_to_player_path(2);
    CHECK(m.contains_all_cities());
}

TEST_CASE("test the timers") {
    Model m(2);
    //check that for every case used in the game, we are actually recording
    // the time down and that it takes less than 0.5 seconds to compute

    //this can be used to determine the point at which brute force becomes
    // too slow-I previously determined this to be when N=11 on my computer,
    // but it might vary by machine.
    
    // The N=10 case takes around 0.13 seconds,
    // which is just barely noticeable, while the N=11 case takes just over
    // one second.

    // Just for fun, I tried going up to N=12, which took 16 seconds.

    //According to the way N! scales, N=13 would take a few minutes, N=14
    // would take 0.5 to 1 hr, N=15 would take several hours, and N=16 would
    // take almost a week
    for (int i = 3; i < 11; ++i) {
        m = Model(i);
        std::cout << "N=";
        std::cout << i;
        std::cout <<": ";
        std::cout << m.bf_time();
        std::cout << "seconds\n";
        CHECK(m.bf_time()>0);
        CHECK(m.bf_time()<0.5);
    }
}
//
// TODO: Write preliminary model tests.
//
// These tests should demonstrate at least six of the functional
// requirements.
//
