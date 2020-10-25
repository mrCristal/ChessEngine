#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <string>
#include "Pieces.h"

class Piece;

struct Square//(z,n)
{
	private:

	int white_under_check; // keeps count of how many pieces can move there directly;
	int black_under_check; // keeps count of how many pieces can move there directly;

	public:

	const int row_pos;
	const int col_pos;
	Piece* piece;

	void alter_check_counter(const std::string colour, const char direction);
	int get_colour_checks(std::string colour) const;
	void reset_checks();

	Square(int x, int y);
	virtual ~Square() {};
};

class ChessBoard
{// ChessBoard responsible to check that proposed move is on a legitimate square
 // i.e. square is either empty or piece on given square is taken
 // this check happens after Piece move check'

	int letter_offset;
	int number_offset;
	std::string colour_to_move;

	std::pair<int,int> to_row_col(const std::string location) const;
	
	void undo_move(const int row0, const int col0, const int row1, const int col1, bool restore_piece);

	void alternate_colour_to_move();

	void reset_all_squares();

	void check_all_squares();

	bool is_check(const std::string colour) const; // checks for check after every move
	
	bool is_checkmate(std::string colour);

	bool is_stalemate(std::string colour); 

	bool free_sqaures_to_location(int const x0, int const y0, int const x1, int const y1) const;

	public:
	Square board[8][8]={
						{{0,0},{0,1},{0,2},{0,3},{0,4},{0,5},{0,6},{0,7}},
						{{1,0},{1,1},{1,2},{1,3},{1,4},{1,5},{1,6},{1,7}},
						{{2,0},{2,1},{2,2},{2,3},{2,4},{2,5},{2,6},{2,7}},
						{{3,0},{3,1},{3,2},{3,3},{3,4},{3,5},{3,6},{3,7}},
						{{4,0},{4,1},{4,2},{4,3},{4,4},{4,5},{4,6},{4,7}},
						{{5,0},{5,1},{5,2},{5,3},{5,4},{5,5},{5,6},{5,7}},
						{{6,0},{6,1},{6,2},{6,3},{6,4},{6,5},{6,6},{6,7}},
						{{7,0},{7,1},{7,2},{7,3},{7,4},{7,5},{7,6},{7,7}}	
						};
						
	Piece* buffer_piece; // used to store a captured piece in case the move needs to be reverted, e.g. when checking for checkmate/stalemate
	
	int moves_made;
	
	bool square_is_free_to_move(int const x,int const y) const;
	
	void resetBoard();
	
	void submitMove(const std::string from, const std::string to); 

	void print_board() const;

	Square operator () (int x, int y); // not used anymore

	ChessBoard();

	virtual ~ChessBoard();
};
#endif