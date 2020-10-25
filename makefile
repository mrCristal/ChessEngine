ChessBoard.o: ChessBoard.h ChessBoard.cpp
	g++ -Wall -g -c ChessBoard.cpp -o ChessBoard.o

Square.o: ChessBoard.h Square.cpp
	g++ -Wall -g -c Square.cpp -o Square.o

Piece.o: Pieces.h Piece.cpp
	g++ -Wall -g -c Piece.cpp -o Piece.o

Pawn.o: Pieces.h Pawn.cpp
	g++ -Wall -g -c Pawn.cpp -o Pawn.o

Bishop.o: Pieces.h Bishop.cpp
	g++ -Wall -g -c Bishop.cpp -o Bishop.o

Rook.o: Pieces.h Rook.cpp
	g++ -Wall -g -c Rook.cpp -o Rook.o

Knight.o: Pieces.h Knight.cpp
	g++ -Wall -g -c Knight.cpp -o Knight.o

Queen.o: Pieces.h Queen.cpp
	g++ -Wall -g -c Queen.cpp -o Queen.o

King.o: Pieces.h King.cpp
	g++ -Wall -g -c King.cpp -o King.o

maintest: ChessBoard.o Square.o Piece.o Pawn.o Bishop.o Knight.o Rook.o Queen.o King.o maintest.cpp
	g++ -Wall -g ChessBoard.o Square.o Piece.o Pawn.o Bishop.o Knight.o Rook.o Queen.o King.o maintest.cpp -o maintest | c++filt

chess: ChessBoard.o Square.o Piece.o Pawn.o Bishop.o Knight.o Rook.o Queen.o King.o ChessMain.cpp
	g++ -Wall -g ChessBoard.o Square.o Piece.o Pawn.o Bishop.o Knight.o Rook.o Queen.o King.o ChessMain.cpp -o chess 
