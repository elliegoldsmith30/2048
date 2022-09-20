

#pragma once

#include "tile.hxx"

#include <ge211.hxx>

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "position_set.hxx"

/// Represents the state of the board.
class Board
{
public:
    /// Board dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// Board positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    /// Board rectangles will use `int` coordinates.
    using Rectangle = ge211::Rect<int>;

    // Defined and documented below.
    class reference;

private:
    //
    // PRIVATE DATA MEMBERS
    //

    Dimensions dims_;
    Position_set two_;
    Position_set four_;
    Position_set eight_;
    Position_set sixteen_;
    Position_set thirty_two_;
    Position_set sixty_four_;
    Position_set hundred_twenty_eight_;
    Position_set two_fifty_six_;
    Position_set five_twelve_;
    Position_set thousand_twenty_four_;
    Position_set twenty_forty_eight_;
    Position_set forty_ninety_six_;
    Position_set eighty_one_ninety_two_;

public:
    //
    // PUBLIC CONSTRUCTOR & FUNCTION MEMBERS
    //

    explicit Board();

    /// Returns the same `Dimensions` value passed to the
    /// constructor.
    Dimensions dimensions() const;

    /// Returns whether the given position is in bounds.
    bool good_position(Position) const;

    Tile operator[](Position pos) const;


    //
    // PUBLIC CONSTRUCTOR & FUNCTION MEMBERS
    //

    reference operator[](Position pos);
    Rectangle all_positions() const;
    bool same_board(Board, Board);
    class multi_reference;
    multi_reference at_set(Position_set set);
    void set_(Position where, Tile who);
    void eliminate_(Position where, Tile who);

private:
    //
    // PRIVATE HELPER FUNCTION MEMBERS
    //
    Tile get_(Position where) const;

    void bounds_check_(Position where) const;

#ifdef CS211_TESTING
    friend struct Test_access;
#endif
};


//
// FREE FUNCTIONS FOR WORKING WITH THE CLASS
//

/// Inequality for boards.
bool
operator!=(Board const&, Board const&);


//
// HELPER CLASSES
//


class Board::reference
{
    Board& board_;
    Position pos_;

public:
    /// Assigns the value of `that` to the object of `this`.
    reference& operator=(reference const&) noexcept;
    /// Assigns to the object of the reference.
    reference& operator=(Tile) noexcept;
    /// Returns the value of the reference.
    operator Tile() const noexcept;

private:
    friend class Board;

    reference(Board&, Position) noexcept;
};

class Board::multi_reference
{
    Board& board_;
    Position_set pos_set_;

public:
    multi_reference& operator=(Tile) noexcept;

private:
    friend class Board;

    multi_reference(Board&, Position_set) noexcept;
};

