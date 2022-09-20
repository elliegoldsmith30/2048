#pragma once

#include "model.hxx"
#include <string>

class View
{
public:
    using Dimensions = ge211::Dims<int>;
    using Position = ge211::Posn<int>;
    using Rectangle = ge211::Rect<int>;
    explicit View(Model const&);

    void draw(ge211::Sprite_set& set);

    Position
    board_to_screen(Model::Position board_pos) const;

    Model::Position
    screen_to_board(Position screen_pos) const;
    Dimensions initial_window_dimensions() const;


private:
    Model const& model_;
    ge211::Rectangle_sprite w;
    ge211::Rectangle_sprite h;
    ge211::Rectangle_sprite base;
    ge211::Rectangle_sprite two;
    ge211::Rectangle_sprite four;
    ge211::Rectangle_sprite eight;
    ge211::Rectangle_sprite sixteen;
    ge211::Rectangle_sprite thirty_two;
    ge211::Rectangle_sprite sixty_four;
    ge211::Rectangle_sprite hundred_twenty_eight;
    ge211::Rectangle_sprite two_fifty_six;
    ge211::Rectangle_sprite five_twelve;
    ge211::Rectangle_sprite thousand_twenty_four;
    ge211::Rectangle_sprite twenty_forty_eight;
    ge211::Rectangle_sprite forty_ninety_six;
    ge211::Rectangle_sprite eighty_one_ninety_two;
    ge211::Rectangle_sprite winner_sprite;
    ge211::Font tile_font;
    ge211::Font tile_font2;
    ge211::Font tile_font3;
    ge211::Font tile_font4;
    ge211::Font tile_font5;
    ge211::Text_sprite congrats;
    ge211::Text_sprite you_win;
    ge211::Text_sprite continue_p;
    ge211::Text_sprite more;
    ge211::Text_sprite number_two;
    ge211::Text_sprite number_four;
    ge211::Text_sprite number_eight;
    ge211::Text_sprite number_sixteen;
    ge211::Text_sprite number_thirty_two;
    ge211::Text_sprite number_sixty_four;
    ge211::Text_sprite number_hundred_twenty_eight;
    ge211::Text_sprite number_two_fifty_six;
    ge211::Text_sprite number_five_twelve;
    ge211::Text_sprite number_thousand_twenty_four;
    ge211::Text_sprite number_twenty_forty_eight;
    ge211::Text_sprite number_forty_ninety_six;
    ge211::Text_sprite number_eighty_one_ninety_two;
    ge211::Text_sprite score_num;
    ge211::Text_sprite score2;
    ge211::Rectangle_sprite score_box;
    ge211::Text_sprite loser;
    ge211::Text_sprite loser_score;
    ge211::Text_sprite loser_score2;




    void
    add_tile_sprite_(ge211::Sprite_set&, Position)const;
};
