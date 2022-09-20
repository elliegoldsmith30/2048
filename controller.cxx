#include "controller.hxx"

Controller::Controller()
        :model_(),
        view_(model_)
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

void
Controller::on_key(ge211::Key key)
{
    if (key == ge211::Key::left()) {
        model_.move_game({-1,0});

    } else if (key == ge211::Key::right()) {
        model_.move_game({1,0});

    } else if (key == ge211::Key::up()) {
        model_.move_game({0,-1});

    } else if (key == ge211::Key::down()) {
        model_.move_game({0,1});

    }
    else if(key == ge211::Key::code('a')){
        model_.winner_setup();
    }
    else if(key == ge211::Key::code('b')){
        model_.spec2_setup();
    }
    else if(key == ge211::Key::code('c')){
        model_.spec3_setup();
    }
    else if(key == ge211::Key::code('d')){
        model_.spec4_setup();
    }
    else if(key == ge211::Key::code('e')){
        model_.spec5_setup();
    }
    else if(key == ge211::Key::code('f')){
        model_.spec6_setup();
    }
    else if(key == ge211::Key::code('l')){
        model_.loser_setup();
    }




}

void
Controller::on_mouse_down(ge211::events::Mouse_button, ge211::Posn<int> p)
{
    model_.set_winner();
}

