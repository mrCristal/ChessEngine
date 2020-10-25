#include "ChessBoard.h"

Square::Square(int x, int y): white_under_check(0), black_under_check(0),  row_pos(x), col_pos(y), piece(nullptr) {}

void Square::alter_check_counter(std::string colour, char direction)
{
    if (colour=="White")
    {
        if (direction=='1')
        {
            black_under_check+=1;

        }
        else
        {
            if (black_under_check>0) // extra precaution
                black_under_check-=1;
        }
    }
    else
    {
        if (direction=='1')
        {
            white_under_check+=1;
        }
        else
        {
            if (white_under_check>0)
                white_under_check-=1;
        }
    }
}

int Square::get_colour_checks(std::string colour) const
{
    if (colour=="White")
        return white_under_check;
    
    return black_under_check;
}

void Square::reset_checks()
{
    white_under_check = 0;
    black_under_check = 0;
}
