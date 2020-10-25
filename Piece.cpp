#include "Pieces.h"

Piece::Piece(std::string name, int id, std::string colour, Square* square, ChessBoard* board): 
       move_count(0), piece_id(id), square(square),chessboard(board), piece_name(name),colour(colour) {} 

bool Piece::move_is_valid(std::pair <int, int> to_location) const
{   // iterating through it's valid moves;
    int row, col;
    std::list<std::pair<int,int>>::const_iterator iter;

    for (iter = unit_vector_moves.begin(); iter != unit_vector_moves.end(); ++iter)
        {
            row = square->row_pos;
            col = square->col_pos;
            while (within_limits(row,col)) 
            {
                row += iter->first;
                col += iter->second;
                if ((row==to_location.first)&&(col==to_location.second))
                    return true;  
            }
        }
    return false;
}

void Piece::set_squares_to_check() const 
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
      
        while (within_limits(row,col)) 
        {
			if (chessboard->board[row][col].piece!=nullptr)
				{
                    chessboard->board[row][col].alter_check_counter(colour,'1');
                    valid_moves.push_back(std::make_pair(row,col));
                    break;
                } // cannot attack on vector anymore as most pieces cannot jump other pieces 
            
            chessboard->board[row][col].alter_check_counter(colour,'1');
            valid_moves.push_back(std::make_pair(row,col));

        	row += iter->first;
            col += iter->second;
        }
    }
}

void Piece::reset_squares() const 
{
    int row , col;

    std::list<std::pair<int,int>>::const_iterator iter;
    // decrementing own position once
    chessboard->board[square->row_pos][square->col_pos].alter_check_counter(colour,'0'); 

    for (iter=unit_vector_moves.begin(); iter!=unit_vector_moves.end(); ++iter)
    {
        row = square->row_pos;
        col = square->col_pos;
        
        row += iter->first;
		col += iter->second;
      
        while (within_limits(row,col)) 
        {
			if (chessboard->board[row][col].piece!=nullptr)
				{
                    chessboard->board[row][col].alter_check_counter(colour,'0');

                    break;
                } // cannot attack on vector anymore
            
            chessboard->board[row][col].alter_check_counter(colour,'0');
        	row += iter->first;
            col += iter->second;
        }
    }
}

void Piece::move(std::pair <int,int> to_location) 
{
    square->piece = nullptr; // set current square to point to no piece
	
	if (chessboard->board[to_location.first][to_location.second].piece!=nullptr)
	{
        chessboard->buffer_piece = chessboard->board[to_location.first][to_location.second].piece;
    }

	square = &(chessboard->board[to_location.first][to_location.second]); // adjust square pointer of piece object
	square->piece = this; // update piece pointer of new square;

    move_count+=1;
}

bool Piece::within_limits(const int num1, const int num2) const
{
    if ((num1<=7)&&(num2<=7)&&(num1>=0)&&(num2>=0))
        return true;
    
    return false;
}

void Piece::print_characteristics()  
{	
	std::cout<<"Piece name: "<<piece_name<<"; colour: "<<colour<<"; ID:"<<piece_id<<std::endl;
	std::cout<<"Current Position is: "<<square->row_pos<<","<<square->col_pos<<std::endl;
	std::cout<<"Moves made: "<<move_count<<std::endl;
}

Piece::~Piece()
{}