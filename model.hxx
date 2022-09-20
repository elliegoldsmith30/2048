#pragma once

#include "tile.hxx"
#include "board.hxx"

#include <ge211.hxx>

#include <iostream>
#include <vector>


class Model
{

public:

    using Dimensions = Board::Dimensions;
    using Position = Board::Position;
    using Rectangle = Board::Rectangle;
    explicit Model();
    Rectangle board() const;
    Tile operator[](Position) const;
    void move_game(Dimensions dir);
    bool winner() const
    { return winner_; }
    void set_positions(Dimensions dir);
    void set_winner()
    { winner_ = false;}
    int get_score() const
    { return score;}
    bool get_lost() const
    { return lost;}
    bool options () const;
    void winner_setup();
    void spec2_setup();
    void spec3_setup();
    void spec4_setup();
    void spec5_setup();
    void spec6_setup();
    void loser_setup();
    Board get_board(){
        return board_;
    }


private:
    Board board_;
    bool winner_;
    Position positions[12];
    Position all_positions[16];
    bool merge1 = false;
    bool merge2 = false;
    void random_spot();
    void merge(Position eliminated, Position changed);
    Tile add_tiles(Tile tile);
    void tile_1(ge211::Posn<int> pos, Dimensions dir);
    void tile_2(ge211::Posn<int> pos, Dimensions dir);
    void tile_3(ge211::Posn<int> pos, Dimensions dir);
    int score = 0;
    int score_addition(Tile tile);
    bool moved = false;
    bool lost = false;

};


