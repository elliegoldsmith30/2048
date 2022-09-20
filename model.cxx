#include "model.hxx"

using namespace ge211;


Model::Model()
        :board_(),
        winner_(false),
        positions{Position(1,0), Position(2,0), Position(3,0), Position(1,1), Position(2,1), Position(3,1), Position(1,2),
                    Position(2,2), Position(3,2), Position(1,3), Position(2,
                                                                          3),Position(3,3)},
        all_positions{Position(0,0), Position(0,1), Position(0,2), Position(0,3),
                      Position(1,0), Position(1,1), Position(1,2), Position(1,3),
                      Position(2,0), Position(2,1), Position(2,2), Position(2,3),
                     Position(3,0), Position(3,1), Position(3,2), Position(3,3) }


{
   random_spot();
   random_spot();
}

Model::Rectangle
Model:: board() const
{
    return board_.all_positions();
}

Tile
Model::operator[](Position pos)const
{
    return board_[pos];
}


void
Model::move_game(Dimensions dir)
{
    set_positions(dir);
    winner_ = false;
    merge1 = false;
    merge2 = false;
    moved = false;
    for (auto pos: positions) {
        // case 1
        if (board_[pos] == Tile::empty) {
            continue;
        }

        if (dir == Dimensions {0, -1}) {
            if (pos.y == 1) {
                tile_1(pos, dir);
                continue;
            } else if (pos.y == 2) {
                tile_2(pos, dir);
                continue;
            } else {
                tile_3(pos, dir);
                continue;
            }
        }


        if (dir == Dimensions {0, 1}) {
            if (pos.y == 2) {
                tile_1(pos, dir);
                continue;
            } else if (pos.y == 1) {
                tile_2(pos, dir);
                continue;
            } else {
                tile_3(pos, dir);
                continue;
            }
        }

        if (dir == Dimensions {1, 0}) {
            if (pos.x == 2) {
                tile_1(pos, dir);
                continue;
            } else if (pos.x == 1) {
                tile_2(pos, dir);
                continue;
            } else {
                tile_3(pos, dir);
                continue;
            }
        }

        if (dir == Dimensions {-1, 0}) {
            if (pos.x == 1) {
                tile_1(pos, dir);
                continue;
            } else if (pos.x == 2) {
                tile_2(pos, dir);
                continue;
            } else {
                tile_3(pos, dir);
                continue;
            }
        }
    }
    if(moved){
        random_spot();
    }

    int count = 0;
    for(auto pos: board_.all_positions()) {
        if (board_[pos] == Tile::empty) {
            count++;
        }
    }

    if(count == 0 && !moved && !options()){
        lost = true;
    }

}

void
Model::random_spot(){
    int count = 0;
    for(auto pos: board_.all_positions()) {
        if (board_[pos] == Tile::empty) {
            count++;
        }
    }
    ge211::Random_source<int> tile1(0,1);
    int tile2 = tile1.next();
    ge211::Random_source<int> ran(1, count);
    int ran_num = ran.next();
    int counter = 1;
    for(auto pos1:board_.all_positions()){
        if(board_[pos1]== Tile::empty){
            if (counter == ran_num) {
                if (tile2 == 0) {
                    board_[pos1] = Tile::two;
                    break;
                } else {
                    board_[pos1] = Tile::four;
                    break;
                }

            } else {
                counter++;
            }
        }
    }
}

void
Model::merge(Position eliminated, Position changed){
    Tile new_tile = add_tiles(board_[eliminated]);
    if(new_tile == Tile::twenty_forty_eight){
        winner_ = true;
    }
    board_.eliminate_(changed, board_[changed]);
    board_.eliminate_(eliminated, board_[eliminated]);
    board_.set_(changed, new_tile);
    score+= score_addition(new_tile);
}




Tile
Model::add_tiles(Tile tile){
    if(tile == Tile::two){
       return Tile::four;
    }
    else if(tile == Tile::four){
       return Tile::eight;
    }
    else if(tile == Tile::eight){
        return Tile::sixteen;
    }
    else if(tile == Tile::sixteen){
        return Tile::thirty_two;
    }
    else if(tile == Tile::thirty_two){
        return Tile::sixty_four;
    }

    else if(tile == Tile::sixty_four){
        return Tile::hundred_twenty_eight;
    }

    else if(tile == Tile::hundred_twenty_eight){
        return Tile::two_fifty_six;
    }

    else if(tile == Tile::two_fifty_six){
        return Tile::five_twelve;
    }

    else if(tile == Tile::five_twelve){
        return Tile::thousand_twenty_four;
    }
    else if(tile == Tile::thousand_twenty_four){
        return Tile::twenty_forty_eight;
    }
    else if(tile == Tile::twenty_forty_eight){
        return Tile::forty_ninety_six;
    }
    else if(tile == Tile::forty_ninety_six){
       return Tile::eighty_one_ninety_two;
    }
    else{
        return Tile::end;
    }
}



void
Model::set_positions(Dimensions dir)
{
    if (dir == Dimensions {-1, 0}) {
        positions[0] = Position(1, 0);
        positions[1] = Position(2, 0);
        positions[2] = Position(3, 0);
        positions[3] = Position(1, 1);
        positions[4] = Position(2, 1);
        positions[5] = Position(3, 1);
        positions[6] = Position(1, 2);
        positions[7] = Position(2, 2);
        positions[8] = Position(3, 2);
        positions[9] = Position(1, 3);
        positions[10] = Position(2, 3);
        positions[11] = Position(3, 3);

    }
    else if(dir == Dimensions{1,0}){
        positions[0] = Position(2, 0);
        positions[1] = Position(1, 0);
        positions[2] = Position(0, 0);
        positions[3] = Position(2, 1);
        positions[4] = Position(1, 1);
        positions[5] = Position(0, 1);
        positions[6] = Position(2, 2);
        positions[7] = Position(1, 2);
        positions[8] = Position(0, 2);
        positions[9] = Position(2, 3);
        positions[10] = Position(1, 3);
        positions[11] = Position(0, 3);
    }
    else if(dir == Dimensions{0,1}){
        positions[0] = Position(0, 2);
        positions[1] = Position(0, 1);
        positions[2] = Position(0, 0);
        positions[3] = Position(1, 2);
        positions[4] = Position(1, 1);
        positions[5] = Position(1, 0);
        positions[6] = Position(2, 2);
        positions[7] = Position(2, 1);
        positions[8] = Position(2, 0);
        positions[9] = Position(3, 2);
        positions[10] = Position(3, 1);
        positions[11] = Position(3, 0);
    }
    else{
        positions[0] = Position(0, 1);
        positions[1] = Position(0, 2);
        positions[2] = Position(0, 3);
        positions[3] = Position(1, 1);
        positions[4] = Position(1, 2);
        positions[5] = Position(1, 3);
        positions[6] = Position(2, 1);
        positions[7] = Position(2, 2);
        positions[8] = Position(2, 3);
        positions[9] = Position(3, 1);
        positions[10] = Position(3, 2);
        positions[11] = Position(3, 3);
    }
}


void
Model::tile_1(ge211::Posn<int> pos, Dimensions dir){
    // case 2
    if(board_[pos] == board_[pos+dir]){
        merge(pos, pos+dir);
        merge1 = true;
        moved = true;
        return;
    }


    // case 3
    if( board_[pos + dir]==Tile::empty){
        board_.set_(pos+dir, board_[pos]);
        board_.eliminate_(pos, board_[pos]);
        moved = true;
        return;
    }
    // case 4

    if(board_[pos] != board_[pos+dir]){
        return;
    }

}


void
Model::tile_2(ge211::Posn<int> pos, Dimensions dir){
    // case 5
    if(board_[pos +dir]==Tile::empty && board_[pos+dir+dir] == Tile::empty){
        board_.set_(pos+dir+dir, board_[pos]);
        board_.eliminate_(pos, board_[pos]);
        moved = true;
        return;
    }

    // case 6
    if(board_[pos] != board_[pos+dir+dir] && board_[pos+dir] == Tile::empty){
        board_.set_(pos+dir, board_[pos]);
        board_.eliminate_(pos, board_[pos]);
        moved = true;
        return;
    }

    // case 7
    if(board_[pos]!= board_[pos+dir] && board_[pos+dir]!= Tile::empty){
        return;
    }

    //case 8
    if(board_[pos] == board_[pos+dir+dir] && !merge1 && board_[pos+dir] ==
    Tile::empty){
        merge(pos, pos+dir+dir);
        moved = true;
        return;

    }

    // case 9
    if(board_[pos] == board_[pos+dir+dir] && merge1){
        board_.set_(pos+dir, board_[pos]);
        board_.eliminate_(pos, board_[pos]);
        moved = true;
        return;

    }

    // case 10
    if(board_[pos] == board_[pos+dir]){
        merge(pos, pos+dir);
        merge2 = true;
        moved = true;
        return;

    }

}


void
Model::tile_3(ge211::Posn<int> pos, Dimensions dir){

    // case 11
    if(board_[pos +dir]==Tile::empty && board_[pos+dir+dir] == Tile::empty &&
    board_[pos+dir+dir + dir] == Tile::empty){
        board_.set_(pos+dir+dir+dir, board_[pos]);
        board_.eliminate_(pos, board_[pos]);
        moved = true;
        return;
    }

    // case 12
    if(board_[pos] != board_[pos+dir+dir+dir] && board_[pos+dir] == Tile::empty
       && board_[pos +dir +dir] == Tile::empty){
        board_.set_(pos+dir+dir, board_[pos]);
        board_.eliminate_(pos, board_[pos]);
        moved = true;
        return;
    }

    // case 13
    if(board_[pos] == board_[pos+dir+dir+dir] && !merge1 &&  board_[pos+dir]
    == Tile::empty && board_[pos +dir +dir] == Tile::empty) {
        merge(pos, pos + dir + dir + dir);
        moved = true;
        return;
    }

    // case 14
    if(board_[pos] != board_[pos+dir] && board_[pos + dir] != Tile::empty){
        return;
    }

    // case 15
     if(board_[pos] != board_[pos+dir+dir] && board_[pos + dir] == Tile::empty){
        board_.set_(pos+dir, board_[pos]);
        board_.eliminate_(pos, board_[pos]);
        moved = true;
        return;
    }

    // case 16
    if(board_[pos] == board_[pos + dir + dir] && board_[pos + dir] ==
    Tile::empty && !merge2){
        merge(pos, pos+dir+dir);
        moved = true;
        return;
    }

    // case 17
    if(board_[pos] == board_[pos + dir + dir] && board_[pos + dir] ==
    Tile::empty){
        board_.set_(pos+dir, board_[pos]);
        board_.eliminate_(pos, board_[pos]);
        moved = true;
        return;
    }


    // case 18
    if(board_[pos] == board_[pos + dir]){
        merge(pos, pos+dir);
        moved = true;
        return;
    }

}

int
Model::score_addition(Tile tile){
    if(tile == Tile::four){
        return 4;
    }
    else if(tile == Tile::eight){
        return 8;
    }
    else if(tile == Tile::sixteen){
        return 16;
    }
    else if(tile == Tile::thirty_two){
        return 32;
    }

    else if(tile == Tile::sixty_four){
        return 64;
    }

    else if(tile == Tile::hundred_twenty_eight){
        return 128;
    }

    else if(tile == Tile::two_fifty_six){
        return 256;
    }

    else if(tile == Tile::five_twelve){
        return 512;
    }
    else if(tile == Tile::thousand_twenty_four){
        return 1024;
    }
    else if(tile == Tile::twenty_forty_eight){
        return 2048;
    }
    else if(tile == Tile::forty_ninety_six){
        return 4096;
    }
    else{
        return 8192;
    }
}


bool
Model::options() const
{
   if(board_[Position(0,0)] == board_[Position(1,0)]) {
       return true;
   }
    if(board_[Position(1,0)] == board_[Position(2,0)]) {
        return true;
    }
    if(board_[Position(2,0)] == board_[Position(3,0)]) {
        return true;
    }
    if(board_[Position(0,1)] == board_[Position(1,1)]) {
        return true;
    }
    if(board_[Position(1,1)] == board_[Position(2,1)]) {
        return true;
    }
    if(board_[Position(2,1)] == board_[Position(3,1)]) {
        return true;
    }
    if(board_[Position(0,2)] == board_[Position(1,2)]) {
        return true;
    }
    if(board_[Position(1,2)] == board_[Position(2,2)]) {
        return true;
    }
    if(board_[Position(2,2)] == board_[Position(3,2)]) {
        return true;
    }
    if(board_[Position(0,3)] == board_[Position(1,3)]) {
        return true;
    }
    if(board_[Position(1,3)] == board_[Position(2,3)]) {
        return true;
    }
    if(board_[Position(2,3)] == board_[Position(3,3)]) {
        return true;
    }

    if(board_[Position(0,0)] == board_[Position(0,1)]) {
        return true;
    }
    if(board_[Position(0,1)] == board_[Position(0,2)]) {
        return true;
    }
    if(board_[Position(0,2)] == board_[Position(0,3)]) {
        return true;
    }
    if(board_[Position(1,0)] == board_[Position(1,1)]) {
        return true;
    }
    if(board_[Position(1,1)] == board_[Position(1,2)]) {
        return true;
    }
    if(board_[Position(1,2)] == board_[Position(1,3)]) {
        return true;
    }
    if(board_[Position(2,0)] == board_[Position(2,1)]) {
        return true;
    }
    if(board_[Position(2,1)] == board_[Position(2,2)]) {
        return true;
    }
    if(board_[Position(2,2)] == board_[Position(2,3)]) {
        return true;
    }
    if(board_[Position(3,0)] == board_[Position(3,1)]) {
        return true;
    }
    if(board_[Position(3,1)] == board_[Position(3,2)]) {
        return true;
    }
    if(board_[Position(3,2)] == board_[Position(3,3)]) {
        return true;
    }
    return false;
}


void
Model::winner_setup(){

   for(auto pos:all_positions)
       if(board_[pos]!=Tile::empty){
           board_.eliminate_(pos, board_[pos]);
       }
    board_.set_(Position(0,0), Tile::thousand_twenty_four);
    board_.set_(Position(1,0), Tile::thousand_twenty_four);
}

void
Model::spec2_setup(){
    for(auto pos:all_positions)
        if(board_[pos]!=Tile::empty){
            board_.eliminate_(pos, board_[pos]);
        }
    board_.set_(Position(0,0), Tile::two);

}

void
Model::spec3_setup(){

    for(auto pos:all_positions)
        if(board_[pos]!=Tile::empty){
            board_.eliminate_(pos, board_[pos]);
        }
    board_.set_(Position(0,0), Tile::two);
    board_.set_(Position(2,0), Tile::four);
    board_.set_(Position(1,1), Tile::two);


}


void
Model::spec4_setup(){

    for(auto pos:all_positions)
        if(board_[pos]!=Tile::empty){
            board_.eliminate_(pos, board_[pos]);
        }
    board_.set_(Position(0,0), Tile::two);
    board_.set_(Position(2,0), Tile::two);


}

void
Model::spec5_setup(){

    for(auto pos:all_positions)
        if(board_[pos]!=Tile::empty){
            board_.eliminate_(pos, board_[pos]);
        }
    board_.set_(Position(0,0), Tile::two);
    board_.set_(Position(2,0), Tile::two);
    board_.set_(Position(1,1), Tile::four);
    board_.set_(Position(2,1), Tile::four);
}


void
Model::spec6_setup(){

    for(auto pos:all_positions)
        if(board_[pos]!=Tile::empty){
            board_.eliminate_(pos, board_[pos]);
        }
    board_.set_(Position(0,0), Tile::two);
    board_.set_(Position(1,0), Tile::two);
    board_.set_(Position(2,0), Tile::four);
    board_.set_(Position(3,0), Tile::four);


}

void
Model::loser_setup(){
    for(auto pos:all_positions)
        if(board_[pos]!=Tile::empty){
            board_.eliminate_(pos, board_[pos]);
        }
    board_.set_(Position(0,0), Tile::two);
    board_.set_(Position(1,0), Tile::four);
    board_.set_(Position(2,0), Tile::eight);
    board_.set_(Position(3,0), Tile::four);

    board_.set_(Position(0,1), Tile::sixteen);
    board_.set_(Position(1,1), Tile::two);
    board_.set_(Position(2,1), Tile::sixty_four);
    board_.set_(Position(3,1), Tile::thirty_two);

    board_.set_(Position(0,2), Tile::sixty_four);
    board_.set_(Position(1,2), Tile::thirty_two);
    board_.set_(Position(2,2), Tile::four);
    board_.set_(Position(3,2), Tile::eight);

    board_.set_(Position(0,3), Tile::hundred_twenty_eight);
    board_.set_(Position(1,3), Tile::two);
    board_.set_(Position(2,3), Tile::five_twelve);
    board_.set_(Position(3,3), Tile::two);

}


