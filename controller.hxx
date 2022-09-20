#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    Controller();

protected:
    void draw(ge211::Sprite_set& set) override;
    void on_key(ge211::Key) override;
    View::Dimensions initial_window_dimensions() const override;
    void on_mouse_down(ge211::events::Mouse_button, ge211::Posn<int>);

private:
    Model model_;
    View view_;
};
