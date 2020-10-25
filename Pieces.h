#ifndef PIECES_H
#define PIECES_H

#include "ChessBoard.h"
#include <iostream>
#include <list>
#include <utility> //contains the std::pair

class ChessBoard;
class Square;

class Piece
{// piece is reponsible to check if proposed move is valid for its type

	virtual void make_abstract() const = 0; // not supposed to anything except make this abstract

	protected:
	
	int move_count; // counts the nr of moves the piece made; mainly useful for
					// castling and 2 square move by the pawn if first move

	std::list <std::pair<int,int>> unit_vector_moves;
	mutable std::list <std::pair<int,int>> valid_moves; 

	// checks that proposed move is within the piece's legal moves
	// need a first check on ChessBoard to see if values are in range
	virtual bool move_is_valid(std::pair <int,int> to_location) const;

	// sets all the squares attackable from new position to check
	virtual void set_squares_to_check() const;

	// resets all the squares reachable from current position to UNcheck
	virtual void reset_squares() const;

	// changes the square pointer
	virtual void move(std::pair <int,int> to_location);

	bool within_limits(const int num1, const int num2) const;

	const int piece_id;
	Square* square;
	ChessBoard* const chessboard;

 	public:

	const std::string piece_name;

	const std::string colour;

	friend class ChessBoard;	

	Piece(std::string name, int id, std::string colour, Square* square, ChessBoard* board);
	
	virtual void print_characteristics(); // to be used for debugging

	virtual ~Piece(); // can you do =0 for destructor??
};



class Pawn: public Piece
{
	// only pawns have attacking moves that are not the same as 'normal' moves
	std::list <std::pair<int,int>> attack_moves; 

	bool move_is_valid(std::pair <int,int> to_location) const final;

	void set_squares_to_check() const final;

	void reset_squares() const final;

	int bl_inv() const; // inverts the direction for black pawns only since they are facing the other way

	void make_abstract() const;

	public:

	Pawn(std::string name, int id, std::string colour, Square* square, ChessBoard* board);

	friend class ChessBoard;
	friend class Square;

	virtual ~Pawn();
};

class Bishop: public Piece
{
	void make_abstract() const;

	public:
	Bishop(std::string name, int id, std::string colour, Square* square, ChessBoard* board);

	friend class ChessBoard;

	virtual ~Bishop();
};

class Rook: public Piece
{
	void make_abstract() const;

	public:
	Rook(std::string name, int id, std::string colour, Square* square, ChessBoard* board);

	friend class ChessBoard;

	virtual ~Rook();
};

class Knight: public Piece
{
	void set_squares_to_check() const final;

	void reset_squares() const final;

	void make_abstract() const final;
	//strictly speaking knight does not have unit vector moves any more, it can make
	public:
	Knight(std::string name, int id, std::string colour, Square* square, ChessBoard* board);

	friend class ChessBoard;

	virtual ~Knight();
};

class Queen: public Piece
{
	void make_abstract() const;

	public:
	Queen(std::string name, int id, std::string colour, Square* square, ChessBoard* board);

	friend class ChessBoard;

	virtual ~Queen();
};

class King: public Piece
{
	void set_squares_to_check() const final;

	void reset_squares() const final;

	void make_abstract() const final;
	
	public:
	King(std::string name, int id, std::string colour, Square* square, ChessBoard* board);

	friend class ChessBoard;

	virtual ~King();
};

#endif