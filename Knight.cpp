#include "Pieces.h"

Knight::Knight(std::string name, int id, std::string colour, Square* square,
		   ChessBoard* board): Piece(name, id, colour,square, board)
{
    unit_vector_moves.push_back(std::make_pair(2,1));
    unit_vector_moves.push_back(std::make_pair(1,2));
    unit_vector_moves.push_back(std::make_pair(-1,2));
    unit_vector_moves.push_back(std::make_pair(-2,1));
    unit_vector_moves.push_back(std::make_pair(-2,-1));
    unit_vector_moves.push_back(std::make_pair(-1,-2));
    unit_vector_moves.push_back(std::make_pair(1,-2));
    unit_vector_moves.push_back(std::make_pair(2,-1));
}

void Knight::set_squares_to_check() const
{
    int row , col;
    valid_moves.clear();
    std::list<std::pair<int,int>>::const_iterator iter;
    // incrementing own position once
    chessboard->board[square->row_pos][square->col_pos].alter_check_counter(colour,'1'); 

    for (iter=unit_vector_moves.begin(); iter!=unit_vector_moves.end(); ++iter)
    {
        row = square->row_pos;
        col = square->col_pos;
        
        row += iter->first;
		col += iter->second;
      
        if (within_limits(row,col))
        {
            chessboard->board[row][col].alter_check_counter(colour,'1');
            valid_moves.push_back(std::make_pair(row,col));
        }
    }
}

void Knight::reset_squares() const
{
    int row , col;

    std::list<std::pair<int,int>>::const_iterator iter;
    // incrementing own position once
    chessboard->board[square->row_pos][square->col_pos].alter_check_counter(colour,'0'); 

    for (iter=unit_vector_moves.begin(); iter!=unit_vector_moves.end(); ++iter)
    {
        row = square->row_pos;
        col = square->col_pos;
        
        row += iter->first;
		col += iter->second;
      
        if (within_limits(row,col))
        {
            chessboard->board[row][col].alter_check_counter(colour,'0');
        }
    }
}


void Knight::make_abstract() const {}

Knight::~Knight()
{}