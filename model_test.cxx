#include "model.hxx"
#include <catch.hxx>
using namespace ge211;


TEST_CASE("can win game"){
    Model m;
    CHECK(m.winner() == false);
    m.winner_setup();
    m.move_game({-1,0});
    CHECK(m.winner() == true);
}


TEST_CASE("can lose game"){
    Model m;
    CHECK(!m.get_lost());
    m.loser_setup();
    m.move_game({-1,0});
    CHECK(m.get_lost());
}

TEST_CASE("tiles merge/do not merge"){
    Model m;
    m.spec4_setup();
    m.move_game({-1,0});
    Board b1(m.get_board());
    CHECK(b1[ge211::Posn<int>(0,0)] == Tile::four);
    m.spec3_setup();
    m.move_game({-1,0});
    b1 = m.get_board();
    CHECK(b1[ge211::Posn<int>(0,0)] == Tile::two);
    CHECK(b1[ge211::Posn<int>(1,0)] == Tile::four);
}


TEST_CASE("tiles slide to wall and stop moving at wall"){
    Model m;
    m.spec2_setup();
    m.move_game({-1,0});
    Board b1(m.get_board());
    CHECK(b1[ge211::Posn<int>(0,0)] == Tile::two);

    m.spec3_setup();
    m.move_game({-1,0});
    b1 = m.get_board();
    CHECK(b1[ge211::Posn<int>(0,1)] == Tile::two);
}

TEST_CASE("score changes"){
    Model m;
    CHECK(m.get_score() == 0);
    m.spec4_setup();
    m.move_game({-1,0});
    CHECK(m.get_score() == 4);
}








