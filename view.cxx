#include <ge211_color.hxx>
#include "view.hxx"

static int const grid_size = 144;

View::View(Model const& model)
        : model_(model),
          w({grid_size*model_.board().dimensions().width, 4}, {160,160,160}),
          h({4, grid_size*model_.board().dimensions().height}, {160,160,160}),
          base({grid_size, grid_size}, {218,209,198}),
          two({grid_size-1, grid_size-1}, {211,211,211}),
          four({grid_size, grid_size}, {185,192,192}),
          eight({grid_size, grid_size}, {237,145,33}),
          sixteen({grid_size, grid_size}, {255,127,80}),
          thirty_two({grid_size, grid_size}, {254,92,92}),
          sixty_four({grid_size, grid_size}, {254,32,32}),
          hundred_twenty_eight({grid_size, grid_size}, {255,232,124}),
          two_fifty_six({grid_size, grid_size}, {253,208,23}),
          five_twelve({grid_size, grid_size}, {251,177,23}),
          thousand_twenty_four({grid_size, grid_size}, {232,163,23}),
          twenty_forty_eight({grid_size, grid_size}, {177,156,217}),
          forty_ninety_six({grid_size, grid_size}, {149,33,246}),
          eighty_one_ninety_two({grid_size, grid_size}, {121,61,244}),
          winner_sprite({grid_size*2, grid_size*2}, {0,0,0}),
          tile_font("sans.ttf", 100),
          tile_font2("sans.ttf", 80),
          tile_font3("sans.ttf", 60),
          tile_font4("sans.ttf", 40),
          tile_font5("sans.ttf", 15),
          congrats("Congrats!", tile_font4),
          you_win("You won",tile_font4),
          continue_p("Click anywhere to", tile_font4),
          more("continue playing", tile_font4),
          number_two("2", tile_font),
          number_four("4", tile_font),
          number_eight("8", tile_font),
          number_sixteen("16", tile_font2),
          number_thirty_two("32", tile_font2),
          number_sixty_four("64", tile_font2),
          number_hundred_twenty_eight("128", tile_font3),
          number_two_fifty_six("256", tile_font3),
          number_five_twelve("512", tile_font3),
          number_thousand_twenty_four("1024", tile_font4),
          number_twenty_forty_eight("2048", tile_font4),
          number_forty_ninety_six("4096", tile_font4),
          number_eighty_one_ninety_two("8192", tile_font4),
          score_num(std::to_string(model_.get_score()), tile_font5),
          score2("Score: ", tile_font5),
          score_box({grid_size*model_.board().dimensions().width, 20}, {160,160,160}),
          loser("You lost:(",tile_font4),
          loser_score("Score: ", tile_font4),
          loser_score2(" ", tile_font4)
{ }

void
View::draw(ge211::Sprite_set& set)
{

    for (int i = 0; i < model_.board().dimensions().height; i++) {
        set.add_sprite(w, board_to_screen({0, i}), 1);
    }
    for (int i = 0; i < model_.board().dimensions().width; i++) {
        set.add_sprite(h, board_to_screen({i, 0}), 1);
    }

    for (Position x: model_.board()) {
        Position screen_pos = board_to_screen(x);
        set.add_sprite(base, screen_pos, 0);
        add_tile_sprite_(set, x);
        if (model_.winner()) {
            {
                set.add_sprite(winner_sprite, {grid_size*model_.board().dimensions()
                                                               .width/4, grid_size*model_.board().dimensions().height/4 }, 5);
                set.add_sprite(congrats, {grid_size*model_.board().dimensions()
                                                          .width/4 + 50,
                                          grid_size*model_
                                                  .board().dimensions().height/4 }, 6);
                set.add_sprite(you_win, {grid_size*model_.board().dimensions()
                                                         .width/4 + 60, grid_size*model_
                        .board().dimensions().height/4 +50}, 6);
                set.add_sprite(continue_p, {grid_size*model_.board().dimensions()
                                                            .width/4 + 10, grid_size*model_
                        .board().dimensions().height/4  + 100}, 6);

                set.add_sprite(more, {grid_size*model_.board().dimensions()
                                                      .width/4, grid_size*model_
                        .board().dimensions().height/4  + 150}, 6);
            }
        }

        if(model_.get_lost()){
            set.add_sprite(winner_sprite, {grid_size*model_.board().dimensions()
                                                           .width/4, grid_size*model_.board().dimensions().height/4 }, 5);
            set.add_sprite(loser, {grid_size*model_.board().dimensions().width/4 + 50,grid_size*model_.board().dimensions().height/4 }, 6);

            set.add_sprite(loser_score, {grid_size*model_.board().dimensions
            ().width/4 + 50, grid_size*model_.board().dimensions().height/4
            +60}, 6);

            loser_score2 = ge211::Text_sprite(std::to_string(model_.get_score
                    ()),tile_font3);

            set.add_sprite(loser_score2, {grid_size*model_.board().dimensions
            ().width/4 + 110, grid_size*model_.board().dimensions().height/4  +
            130}, 6);
        }

        score_num = ge211::Text_sprite(std::to_string(model_.get_score()),
                                       tile_font5);
        set.add_sprite(score2, Position{400, -3}, 6);
        set.add_sprite(score_num, Position(470, -3), 6);
        set.add_sprite(score_box, Position(0,0), 5);
    }
}


View::Position
View::board_to_screen(Model::Position pos) const
{
    return {grid_size * pos.x, grid_size * pos.y};
}

Model::Position
View::screen_to_board(View::Position pos) const
{
    return {pos.x / grid_size, pos.y / grid_size};
}

void
View::add_tile_sprite_(
        ge211::Sprite_set& set,
        Position pos)const
{
    Position screen_pos = board_to_screen(pos);
    if(model_[pos] == Tile::two){
        set.add_sprite(number_two,screen_pos + Dimensions{45,-10}
        ,4 );
        set.add_sprite(two, screen_pos + Dimensions{2,2} ,3);
    }
    else if(model_[pos] == Tile::four){
        set.add_sprite(four, screen_pos+ Dimensions{2,2},3);
        set.add_sprite(number_four,screen_pos + Dimensions{45,-10}
                ,4 );
    }
    else if(model_[pos] == Tile::eight){
        set.add_sprite(eight, screen_pos+ Dimensions{2,2},3);
        set.add_sprite(number_eight,screen_pos + Dimensions{45,-10}
                ,4 );
    }

    else if(model_[pos] == Tile::sixteen){
        set.add_sprite(sixteen, screen_pos+ Dimensions{2,2},3);
        set.add_sprite(number_sixteen,screen_pos + Dimensions{28,-7}
                ,4 );
    }
    else if(model_[pos] == Tile::thirty_two){
        set.add_sprite(thirty_two, screen_pos+ Dimensions{2,2},3);
        set.add_sprite(number_thirty_two,screen_pos + Dimensions{28,-7}
                ,4 );
    }
    else if(model_[pos] == Tile::sixty_four){
        set.add_sprite(sixty_four, screen_pos+ Dimensions{2,2},3);
        set.add_sprite(number_sixty_four,screen_pos + Dimensions{28,-7}
                ,4 );
    }
    else if(model_[pos] == Tile::hundred_twenty_eight){
        set.add_sprite(hundred_twenty_eight, screen_pos+ Dimensions{2,2},3);
        set.add_sprite(number_hundred_twenty_eight,screen_pos +
        Dimensions{25,10}
                ,4 );
    }
    else if(model_[pos] == Tile::two_fifty_six){
        set.add_sprite(two_fifty_six, screen_pos+ Dimensions{2,2},3);
        set.add_sprite(number_two_fifty_six,screen_pos + Dimensions{15,10}
                ,4 );
    }
    else if(model_[pos] == Tile::five_twelve){
        set.add_sprite(five_twelve, screen_pos+ Dimensions{2,2},3);
        set.add_sprite(number_five_twelve,screen_pos + Dimensions{25,10}
                ,4 );
    }
    else if(model_[pos] == Tile::thousand_twenty_four){
        set.add_sprite(thousand_twenty_four, screen_pos+ Dimensions{2,2},3);
        set.add_sprite(number_thousand_twenty_four,screen_pos + Dimensions{28,
                                                                           20}
                ,4 );
    }
    else if(model_[pos] == Tile::twenty_forty_eight){
        set.add_sprite(twenty_forty_eight, screen_pos+ Dimensions{2,2},3);
        set.add_sprite(number_twenty_forty_eight,screen_pos + Dimensions{28,20}
                ,4 );
    }
    else if(model_[pos] == Tile::forty_ninety_six){
        set.add_sprite(forty_ninety_six, screen_pos+ Dimensions{2,2},3);
        set.add_sprite(number_forty_ninety_six,screen_pos + Dimensions{28,20}
                ,4 );
    }
    else if(model_[pos] == Tile::eighty_one_ninety_two){
        set.add_sprite(eighty_one_ninety_two, screen_pos+ Dimensions{2,2},3);
        set.add_sprite(number_eighty_one_ninety_two,screen_pos +
        Dimensions{28,20}
                ,4 );
    }

}

View::Dimensions
View::initial_window_dimensions() const
{
    return grid_size * model_.board().dimensions();
}




