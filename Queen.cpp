#include "Pieces.h"

Queen::Queen(std::string name, int id, std::string colour, Square* square,
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

void Queen::make_abstract() const {}

Queen::~Queen()
{}