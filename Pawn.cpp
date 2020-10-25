#include "Pieces.h"

Pawn::Pawn(std::string name, int id, std::string colour, Square* square,
		   ChessBoard* board): Piece(name, id, colour,square, board) 
	{
		unit_vector_moves.push_back(std::make_pair(0,1)); // technically not used here
		//unit_vector_moves.push_back(std::make_pair(0,2));
		attack_moves.push_back(std::make_pair(1,1)); // when capturing right
		attack_moves.push_back(std::make_pair(1,-1)); // when capturing left
	}

bool Pawn::move_is_valid(std::pair <int,int> to_location) const
{
	int row = square->row_pos, col = square->col_pos;

	// if standard move
	if ((row+1*bl_inv() == to_location.first) && (col == to_location.second) && within_limits(row+1*bl_inv(),col))
	{	// in this case the square to be moved to MUST be empty
		if (chessboard->board[row+1*bl_inv()][col].piece==nullptr)
			return true;
		
		return false;
	}
	else if ((row+2*bl_inv() == to_location.first) && (col == to_location.second) && (move_count==0)
			 && within_limits(row+2*bl_inv(),col)) 
	{
		if (chessboard->board[row+2*bl_inv()][col].piece==nullptr)
			return true;
		
		return false;
	}
	// if potentially a capture move
	else if (chessboard->board[to_location.first][to_location.second].piece!=nullptr)
	{
		std::list<std::pair<int,int>>::const_iterator iter;
    	for (iter = attack_moves.begin(); iter != attack_moves.end(); ++iter)
        {
            row = square->row_pos;
            col = square->col_pos;
			row += (iter->first*bl_inv());
            col += (iter->second*bl_inv());
            if (within_limits(row,col))
            {
                if ((row==to_location.first)&&(col==to_location.second))
                    {return true;}  
            }
        }
	}
	return false;
}

void Pawn::set_squares_to_check() const
{
	valid_moves.clear();
	int row = square->row_pos+1*bl_inv(), col = square->col_pos-1*bl_inv();
	
	if (within_limits(row,col))
	{
		chessboard->board[row][col].alter_check_counter(colour,'1');
		valid_moves.push_back(std::make_pair(row,col));
	}

	row = square->row_pos+1*bl_inv();
	col = square->col_pos+1*bl_inv();


	if (within_limits(row,col))
	{
		chessboard->board[row][col].alter_check_counter(colour,'1');
		valid_moves.push_back(std::make_pair(row,col));
	}
	
	valid_moves.push_back(std::make_pair(square->row_pos+1*bl_inv(),square->col_pos));
	valid_moves.push_back(std::make_pair(square->row_pos+2*bl_inv(),square->col_pos));

}

void Pawn::reset_squares()  const
{

	int row = square->row_pos+1*bl_inv(), col = square->col_pos-1*bl_inv();

	if (within_limits(row,col))
	{
		chessboard->board[row][col].alter_check_counter(colour,'0');}

	row = square->row_pos+1*bl_inv();
	col = square->col_pos+1*bl_inv();


	if (within_limits(row,col))
	{
		chessboard->board[row][col].alter_check_counter(colour,'0');}
}

int Pawn::bl_inv() const
{
	if (colour=="Black")
		return -1;
	return 1;
}

void Pawn::make_abstract() const {}

Pawn::~Pawn()
{}