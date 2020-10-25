#include "Pieces.h"

King::King(std::string name, int id, std::string colour, Square* square,
		   ChessBoard* board): Piece(name, id, colour,square, board)
{
    unit_vector_moves.push_back(std::make_pair(1,1));
    unit_vector_moves.push_back(std::make_pair(-1,1));
    unit_vector_moves.push_back(std::make_pair(1,-1));
    unit_vector_moves.push_back(std::make_pair(-1,-1));
    unit_vector_moves.push_back(std::make_pair(0,1));
    unit_vector_moves.push_back(std::make_pair(0,-1));
    unit_vector_moves.push_back(std::make_pair(1,0));
    unit_vector_moves.push_back(std::make_pair(-1,0));
}

void King::set_squares_to_check() const
{
    valid_moves.clear();
    int row , col;

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

void King::reset_squares() const
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


void King::make_abstract() const {}

King::~King()
{}