#include "Pieces.h"

Bishop::Bishop(std::string name, int id, std::string colour, Square* square,
		   ChessBoard* board): Piece(name, id, colour,square, board)
{
    unit_vector_moves.push_back(std::make_pair(1,1));
    unit_vector_moves.push_back(std::make_pair(-1,1));
    unit_vector_moves.push_back(std::make_pair(1,-1));
    unit_vector_moves.push_back(std::make_pair(-1,-1));
}

void Bishop::make_abstract() const {}

Bishop::~Bishop()
{}