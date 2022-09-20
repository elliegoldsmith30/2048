#include "board.hxx"
#include <algorithm>


using namespace ge211;

Board::Board()
        : dims_(4,4)
{
    if (dims_.width < 2 || dims_.height < 2) {
        throw Client_logic_error("Board::Board: dims too small");
    }

    if (dims_.width > Position_set::coord_limit ||
        dims_.height > Position_set::coord_limit) {
        throw Client_logic_error("Board::Board: dims too large");
    }
}

Board::Dimensions
Board::dimensions() const
{
    return dims_;
}

bool
Board::good_position(Position pos) const
{
    return 0 <= pos.x && pos.x < dims_.width &&
           0 <= pos.y && pos.y < dims_.height;
}

Tile
Board::operator[](Position pos) const
{
    bounds_check_(pos);
    return get_(pos);
}

Board::reference
Board::operator[](Position pos)
{
    bounds_check_(pos);
    return reference(*this, pos);
}


Board::Rectangle
Board::all_positions() const
{
    return Rectangle::from_top_left(the_origin, dims_);
}

bool
Board::same_board(Board b1, Board b2)
{
    return b1.two_ == b2.two_ &&
           b1.four_ == b2.four_ &&
            b1.eight_ == b2.eight_ &&
            b1.sixteen_ == b2.sixteen_ &&
            b1.thirty_two_ == b2.thirty_two_ &&
            b1.sixty_four_ == b2.sixty_four_ &&
            b1.hundred_twenty_eight_ == b2.hundred_twenty_eight_ &&
            b1.two_fifty_six_ == b2.two_fifty_six_ &&
            b1.five_twelve_ == b2.five_twelve_ &&
            b1.thousand_twenty_four_ == b2.thousand_twenty_four_ &&
            b1.twenty_forty_eight_ == b2.twenty_forty_eight_ &&
            b1.forty_ninety_six_ == b2.forty_ninety_six_ &&
            b1.eighty_one_ninety_two_ == b2.eighty_one_ninety_two_ ;
}


Tile
Board::get_(Position pos) const
{
    if (two_[pos]) {
        return Tile::two;
    } else if (four_[pos]) {
        return Tile::four;
    } else if (eight_[pos]) {
        return Tile::eight;
    }
    else if (sixteen_[pos]) {
        return Tile::sixteen;
    }
    else if (thirty_two_[pos]) {
        return Tile::thirty_two;
    }
    else if (sixty_four_[pos]) {
        return Tile::sixty_four;
    }
    else if (hundred_twenty_eight_[pos]) {
        return Tile::hundred_twenty_eight;
    }
    else if (two_fifty_six_[pos]) {
        return Tile::two_fifty_six;
    }
    else if (five_twelve_[pos]) {
        return Tile::five_twelve;
    }
    else if (thousand_twenty_four_[pos]) {
        return Tile::thousand_twenty_four;
    }
    else if (twenty_forty_eight_[pos]) {
        return Tile::twenty_forty_eight;
    }
    else if (twenty_forty_eight_[pos]) {
        return Tile::twenty_forty_eight;
    }
    else if (forty_ninety_six_[pos]) {
        return Tile::forty_ninety_six;
    }
    else if (eighty_one_ninety_two_[pos]) {
        return Tile::eighty_one_ninety_two;
    }
    else {
        return Tile::empty;
    }

}

void
Board::set_(Position pos, Tile tile)
{
    if(tile == Tile::two){
        two_[pos] = true;
    }
    else if(tile == Tile::four){
        four_[pos] = true;
    }
    else if(tile == Tile::eight){
        eight_[pos] = true;
    }
    else if(tile == Tile::sixteen){
        sixteen_[pos] = true;
    }
    else if(tile == Tile::thirty_two){
        thirty_two_[pos] = true;
    }

    else if(tile == Tile::sixty_four){
        sixty_four_[pos] = true;
    }

    else if(tile == Tile::hundred_twenty_eight){
        hundred_twenty_eight_[pos] = true;
    }

    else if(tile == Tile::two_fifty_six){
        two_fifty_six_[pos] = true;
    }

    else if(tile == Tile::five_twelve){
        five_twelve_[pos] = true;
    }
    else if(tile == Tile::thousand_twenty_four){
        thousand_twenty_four_[pos] = true;
    }
    else if(tile == Tile::twenty_forty_eight){
        twenty_forty_eight_[pos] = true;
    }
    else if(tile == Tile::forty_ninety_six){
        forty_ninety_six_[pos] = true;
    }
    else if(tile == Tile::eighty_one_ninety_two){
        eighty_one_ninety_two_[pos] = true;
    }


}

void
Board::eliminate_(Position pos, Tile tile)
{
    if(tile == Tile::two){
        two_[pos] = false;
    }
    else if(tile == Tile::four){
        four_[pos] = false;
    }
    else if(tile == Tile::eight){
        eight_[pos] = false;
    }
    else if(tile == Tile::sixteen){
        sixteen_[pos] = false;
    }
    else if(tile == Tile::thirty_two){
        thirty_two_[pos] = false;
    }

    else if(tile == Tile::sixty_four){
        sixty_four_[pos] = false;
    }

    else if(tile == Tile::hundred_twenty_eight){
        hundred_twenty_eight_[pos] = false;
    }

    else if(tile == Tile::two_fifty_six){
        two_fifty_six_[pos] = false;
    }

    else if(tile == Tile::five_twelve){
        five_twelve_[pos] = false;
    }
    else if(tile == Tile::thousand_twenty_four){
        thousand_twenty_four_[pos] = false;
    }
    else if(tile == Tile::twenty_forty_eight){
        twenty_forty_eight_[pos] = false;
    }
    else if(tile == Tile::forty_ninety_six){
        forty_ninety_six_[pos] = false;
    }
    else if(tile == Tile::eighty_one_ninety_two){
        eighty_one_ninety_two_[pos] = false;
    }


}



void
Board::bounds_check_(Position pos) const
{
    if (!good_position(pos)) {
        throw Client_logic_error("Board: position out of bounds");
    }
}



Board::reference::reference(Board& board, Position pos) noexcept
        : board_(board),
          pos_(pos)
{ }

Board::reference&
Board::reference::operator=(reference const& that) noexcept
{
    *this = Tile(that);
    return *this;
}

Board::reference&
Board::reference::operator=(Tile tile) noexcept
{
    board_.set_(pos_, tile);
    return *this;
}

Board::reference::operator Tile() const noexcept
{
    return board_.get_(pos_);
}

Board::multi_reference
Board::at_set(Position_set pos_set)
{
    return multi_reference(*this, pos_set);
}

Board::multi_reference::multi_reference(
        Board& board,
        Position_set pos_set) noexcept
        : board_(board),
          pos_set_(pos_set)
{ }

Board::multi_reference&
Board::multi_reference::operator=(Tile tile) noexcept
{
    return *this;
}

