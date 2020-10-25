#include "ChessBoard.h"
#include <utility> //contains the std::pair
#include <typeinfo>

ChessBoard::ChessBoard(): letter_offset(65), number_offset(49), colour_to_move("White"), buffer_piece(nullptr), moves_made(0)
{ 
    //print_board();

    int id = 1;
    
    for (int col = 0; col < 8; col++)
	{
        board[1][col].piece = new Pawn("Pawn",id,"White",&board[1][col], this);id+=1;
        board[6][col].piece = new Pawn("Pawn",id,"Black",&board[6][col], this);id+=1;
	}    
    
    board[0][2].piece = new Bishop("Bishop",id,"White",&board[0][2], this);id+=1;
    board[0][5].piece = new Bishop("Bishop",id,"White",&board[0][5], this);id+=1;
    board[7][2].piece = new Bishop("Bishop",id,"Black",&board[7][2], this);id+=1;
    board[7][5].piece = new Bishop("Bishop",id,"Black",&board[7][5], this);id+=1;

    board[0][1].piece = new Knight("Knight",id,"White",&board[0][1], this);id+=1;
    board[0][6].piece = new Knight("Knight",id,"White",&board[0][6], this);id+=1;
    board[7][1].piece = new Knight("Knight",id,"Black",&board[7][1], this);id+=1;
    board[7][6].piece = new Knight("Knight",id,"Black",&board[7][6], this);id+=1;

    board[0][0].piece = new Rook("Rook",id,"White",&board[0][0], this);id+=1;
    board[0][7].piece = new Rook("Rook",id,"White",&board[0][7], this);id+=1;
    board[7][0].piece = new Rook("Rook",id,"Black",&board[7][0], this);id+=1;
    board[7][7].piece = new Rook("Rook",id,"Black",&board[7][7], this);id+=1;

    board[0][3].piece = new Queen("Queen",id,"White",&board[0][3], this);id+=1;
    board[7][3].piece = new Queen("Queen",id,"Black",&board[7][3], this);id+=1;

    board[0][4].piece = new King("King",id,"White",&board[0][4], this);id+=1;
    board[7][4].piece = new King("King",id,"Black",&board[7][4], this);id+=1;
    
    check_all_squares();

    std::cout<<"A new chess game is started!"<<std::endl;

}

bool ChessBoard::square_is_free_to_move(int const x, int const y) const
{
    return (board[x][y].piece!=nullptr);
}

void ChessBoard::resetBoard()
{
    reset_all_squares();

    if (buffer_piece != nullptr)
        delete buffer_piece;

    for (int row =0; row<8; row++)
    {
        for (int col = 0; col<8; col++)
        {
            if (board[row][col].piece!=nullptr)
            {
                delete board[row][col].piece; 
                board[row][col].piece = nullptr;
            }
        }
    }

    int id = 1;
    
    for (int col = 0; col < 8; col++)
	{
        board[1][col].piece = new Pawn("Pawn",id,"White",&board[1][col], this);id+=1;
        board[6][col].piece = new Pawn("Pawn",id,"Black",&board[6][col], this);id+=1;
	}    
    
    board[0][2].piece = new Bishop("Bishop",id,"White",&board[0][2], this);id+=1;
    board[0][5].piece = new Bishop("Bishop",id,"White",&board[0][5], this);id+=1;
    board[7][2].piece = new Bishop("Bishop",id,"Black",&board[7][2], this);id+=1;
    board[7][5].piece = new Bishop("Bishop",id,"Black",&board[7][5], this);id+=1;

    board[0][1].piece = new Knight("Knight",id,"White",&board[0][1], this);id+=1;
    board[0][6].piece = new Knight("Knight",id,"White",&board[0][6], this);id+=1;
    board[7][1].piece = new Knight("Knight",id,"Black",&board[7][1], this);id+=1;
    board[7][6].piece = new Knight("Knight",id,"Black",&board[7][6], this);id+=1;

    board[0][0].piece = new Rook("Rook",id,"White",&board[0][0], this);id+=1;
    board[0][7].piece = new Rook("Rook",id,"White",&board[0][7], this);id+=1;
    board[7][0].piece = new Rook("Rook",id,"Black",&board[7][0], this);id+=1;
    board[7][7].piece = new Rook("Rook",id,"Black",&board[7][7], this);id+=1;

    board[0][3].piece = new Queen("Queen",id,"White",&board[0][3], this);id+=1;
    board[7][3].piece = new Queen("Queen",id,"Black",&board[7][3], this);id+=1;

    board[0][4].piece = new King("King",id,"White",&board[0][4], this);id+=1;
    board[7][4].piece = new King("King",id,"Black",&board[7][4], this);id+=1;
    
    check_all_squares();

    std::cout<<"A new chess game is started!"<<std::endl;

    print_board();

    colour_to_move = "White";
}

bool ChessBoard::free_sqaures_to_location(int const row0, int const col0, int const row1, int const col1) const // checks for empty squares UP TO location,
{
    if (board[row0][col0].piece->piece_name == "Knight") // no need to check space to new position for knights
        return true;

    int increment;

    if ((row1-row0!=0) && (col1-col0!=0)) // i.e. not plain vertical or horizontal move
    {
        int increment_2;

        if (row0>row1)
            increment = -1;
        else 
            increment = 1;
        
        if (col0>col1)
            increment_2 = -1;
        else  
            increment_2 = 1;

        int col = col0, row = row0;
        
        col+=increment_2;
        row+=increment;

        while((col!=col1) && (row!=row1) ) // techincallu only once condition is enough since its a diagonal
        {
            if (board[row][col].piece != nullptr)
            {
                return false;
            }

            col+=increment_2;
            row+=increment;
        }
        return true;
    }

    if (row0==row1) // if the move is strictly horizontal
    {
        if (col0>col1)
            increment = -1;
        else
            increment = 1;
        
        int col = col0;
        col+=increment;

        while(col!=col1)
        {

            if ( board[row0][col].piece != nullptr)
            {
                return false;
            }
            col+=increment;
        }
        return true;
    }

    if (col0==col1) // if the move is strictly vertical
    {
        if (row0>row1)
            increment = -1;
        else
        	increment = 1;

        int row = row0;
        row+=increment;
        //std::cout<<"For piece at "<<row0<<" "<<col0<<" the move is to "<<row1<<" "<<col0
          //  <<" with rwo at "<<row<<" after the change"<<std::endl;

        while(row!=row1)
        {   //std::cout<<"YOU GOT LOLED AGIAN"<<std::endl;

            if ( board[row][col0].piece != nullptr)
            {
                return false; 
            }
            row+=increment;
        }

        return true;
    }

    std::cerr<<"Failure of free squares check"<<std::endl;
    return false;

}   

void ChessBoard::print_board() const
{
    std::cout<<"        A       B       C      D       E       F       G       H   "<<std::endl;
    std::cout<<"    |^^^^^^||^^^^^^||^^^^^^||^^^^^^||^^^^^^||^^^^^^||^^^^^^||^^^^^^|"<<std::endl;
    for(int row = 7; row>-1;row--)
    {    
        std::cout<<"  "<<row+1<<" ";
        for (int col = 0; col<8;col++)
        {
            if (board[row][col].piece!=nullptr)
            {
                std::cout<<"|  "<<board[row][col].piece->colour.c_str()[0]<<board[row][col].piece->piece_name.c_str()[0]<<"  |";
            }
            else
            {
            	std::cout<<"|      |";
            }
        }
        std::cout<<std::endl;
        if (row==0)
        {
            std::cout<<"    |______||______||______||______||______||______||______||______|"<<std::endl;
        }
        else
            std::cout<<"    |------||------||------||------||------||------||------||------|"<<std::endl;
    }
}

std::pair<int,int> ChessBoard::to_row_col(const std::string location) const
{
    int x, y;
    
    if ( ((int)location[0]>72) ||((int)location[0]<65) )
    {
        x = -1;
    }
    else {x = (int)location[0] - letter_offset;}
    
    if ( ((int)location[1]>56) ||((int)location[1]<49) )
    {
        y = -1;
    }
    else {y = (int)location[1] - number_offset;}

    return std::make_pair(y,x);
}

Square ChessBoard::operator () (int x, int y)
{
    if ((x<0)||(x>7)||(y<0)||(y>7))
    {
        Square temp(-1,-1);
        return temp;
    }
    else
    {return board[x][y];}
}

bool ChessBoard::is_check(const std::string colour) const
{
    for (int row = 0; row<8; row++)
    {
        for (int col = 0; col<8; col++)
        {
            if (board[row][col].piece!=nullptr)
            {
                if ((board[row][col].piece->piece_name=="King")&&(board[row][col].piece->colour==colour))
                {	// checking the count on the square where the respective king is
                    if (board[row][col].get_colour_checks(colour) != 0) 
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool ChessBoard::is_checkmate(std::string colour)
{
    if (!is_check(colour))
        return false;
    
    bool restore_piece = false;

    // for all pieces of side in check need to try all possible moves
    // in case the move does not lead to uncheck, move has to be reverted back
    // in case where a piece of the opposing side is captured and the move does not lead to uncheck, 
    // the captured piece has to be stored in a buffer of some sort with all (or at least colour and piece type) attributes
    std::list<std::pair<int,int>>::const_iterator iter;
    std::list<std::pair<int,int>> piece_moves_list;

    for (int row = 0; row<8; row++)
    {
        for (int col = 0; col<8; col++)
        {
            if (board[row][col].piece==nullptr)
                continue;

            if (board[row][col].piece->colour!=colour)
                continue;
                
            piece_moves_list = board[row][col].piece->valid_moves;

            for (iter = piece_moves_list.begin();iter != piece_moves_list.end(); iter++)
            {
                if ((!board[row][col].piece->move_is_valid(*iter))||(!free_sqaures_to_location(row,col,iter->first,iter->second)))
                        {continue;}

                if (board[iter->first][iter->second].piece!=nullptr)
                {
                    if (board[iter->first][iter->second].piece->colour==colour)
                        continue;

                    else 
                        {
                            restore_piece = true;
                        }
                }
                
                reset_all_squares();
                board[row][col].piece->move(*iter);
                check_all_squares();
                if (is_check(colour))
                {
                    undo_move(row,col,iter->first,iter->second,restore_piece);
                    restore_piece = false;
                }
                else
                {
                    undo_move(row,col,iter->first,iter->second,restore_piece);
                    restore_piece = false;
                    print_board();
                    return false;
                }                                        
            }
            
        }
    }
    return true;
}

bool ChessBoard::is_stalemate(std::string colour) 
{
    if (is_check(colour))
        return false;
    
    bool restore_piece = false;

    std::list<std::pair<int,int>>::const_iterator iter;
    std::list<std::pair<int,int>> piece_moves_list;

    for (int row = 0; row<8; row++)
    {
        for (int col = 0; col<8; col++)
        {
            if (board[row][col].piece==nullptr)
                continue;

            if ( (board[row][col].piece->colour==colour) )
            {
                piece_moves_list = board[row][col].piece->valid_moves;

                for (iter = piece_moves_list.begin();iter != piece_moves_list.end(); iter++)
                {
                    if ((!board[row][col].piece->move_is_valid(*iter))||(!free_sqaures_to_location(row,col,iter->first,iter->second)))
                        {continue;}

                    if (board[iter->first][iter->second].piece!=nullptr)
                    {
                        if (board[iter->first][iter->second].piece->colour==colour)
                            continue;

                        else 
                        {
                            restore_piece = true;
                        }
                    }

                    reset_all_squares();
                    board[row][col].piece->move(*iter);
                    check_all_squares();
                    
                    if (!is_check(colour))
                    {
                        undo_move(row,col,iter->first,iter->second,restore_piece);
                        restore_piece = false;
                        return false;
                    }
                    else
                    {
                        undo_move(row,col,iter->first,iter->second,restore_piece);
                        restore_piece = false;
                    }                                        
                }
            }
        }
    }
    return true;
}

void ChessBoard::undo_move(const int row0, const int col0, const int row1, const int col1, bool restore_piece)
{
	reset_all_squares();
    board[row1][col1].piece->move_count-=2;
	board[row1][col1].piece->move(std::make_pair(row0,col0));
	if ((restore_piece)&&(buffer_piece!=nullptr))  //extra precaution
	{
		board[row1][col1].piece = buffer_piece;
		buffer_piece->square = &board[row1][col1];
		buffer_piece = nullptr;
	}
    else
        {board[row1][col1].piece=nullptr;} //extra precaution

	check_all_squares();
}

void ChessBoard::alternate_colour_to_move()
{
    if (colour_to_move=="White")
    {
        colour_to_move="Black";
    }
    else
    {
        colour_to_move="White";
    }
}

void ChessBoard::reset_all_squares()
{
    for (int row = 0; row<8; row++)
    {
        for (int col = 0; col<8; col++)
        {
            board[row][col].reset_checks();
        }
    }
}

void ChessBoard::check_all_squares()
{
    for (int row = 0; row<8; row++)
    {
        for (int col = 0; col<8; col++)
        {
            if (board[row][col].piece!=nullptr)
            {
                board[row][col].piece->set_squares_to_check();
            }
        }
    }
}

void ChessBoard::submitMove(const std::string from, const std::string to)
{
    std::cout<<colour_to_move<<" to move"<<std::endl;
    
    std::pair<int,int> source = to_row_col(from), dest = to_row_col(to);
    // some sanity checks first
    // moves have to be within bounds
    std::cout<<"\n                        ==="<<from<<" "<<to<<"==="<<std::endl;
    if  ( (source.first==-1) || (source.second==-1) || (dest.first==-1) || (dest.second==-1) )
         {
             std::cout<<"Invalid move entered. Please try again!"<<std::endl;
             return;
         }
    // there has to a piece on source squre
    if (board[source.first][source.second].piece==nullptr)
    {
        std::cout<<"There is no piece at position "<<from<<"!"<<std::endl;
        return;
    }
    // it has to be the right side moving
    if (board[source.first][source.second].piece->colour!=colour_to_move)
    {
        std::cout<<"It is not "<<board[source.first][source.second].piece->colour<<"'s turn to move!"<<std::endl;
        return;
    }

    if ((source.first==dest.first)&&(source.second==dest.second))
    {
        std::cout<<"Cannot move piece to the locaiton it is currently at!"<<std::endl;
        return;
    }

    // piece checks that move is valid for itself
    if (board[source.first][source.second].piece->move_is_valid(dest)) // check against valid_moves list!!!
    {
        // if not a knight check for free square to location
        if (board[source.first][source.second].piece->piece_name!="Knight")
        {
            if ( !free_sqaures_to_location(source.first, source.second, dest.first, dest.second) )
            {
                std::cout<<board[source.first][source.second].piece->piece_name<<"s cannot jump over pieces!"<<std::endl;
                return;
            }
        }

        if (board[source.first][source.second].piece->piece_name=="King")
        {
            if ( board[dest.first][dest.second].get_colour_checks(colour_to_move)!=0 )
            {
                std::cout<<"Cannot move King into check!"<<std::endl;
                return;
            }
        }


        // if moving to non empty square check for different colours
        if (board[dest.first][dest.second].piece!=nullptr)
        {
            if (board[dest.first][dest.second].piece->colour==board[source.first][source.second].piece->colour)
            {
                std::cout<<"Cannot capture pieces of own side!"<<std::endl;
                return;
            } 
        }

        reset_all_squares();
        std::cout<<colour_to_move<<"'s "<<board[source.first][source.second].piece->piece_name<<" moves from "<<from<<" to "<<to;
        if (board[dest.first][dest.second].piece!=nullptr)
        {
            std::cout<<" taking "<<board[dest.first][dest.second].piece->colour<<"'s "<<board[dest.first][dest.second].piece->piece_name;
            buffer_piece = nullptr;
        }

        std::cout<<std::endl;

        board[source.first][source.second].piece->move(dest);

        check_all_squares();
        alternate_colour_to_move(); // switch turns
        print_board();

        if (is_check(colour_to_move))
            std::cout<<colour_to_move<<"'s in check!"<<std::endl;

        if (is_stalemate(colour_to_move))
        {
            std::cout<<colour_to_move<<" is in stalemate. Programme ended"<<std::endl;
            for (int row = 0; row<8; row++)
            {
                for (int col = 0; col<8; col++)
                {
                    if (board[row][col].piece!=nullptr)
                    {
                        delete board[row][col].piece; // if square has 0 checks it will stay at 0, not decremented
                    }
                }
            }
            exit(0);
        }

        if (is_checkmate(colour_to_move))
        {
            std::cout<<colour_to_move<<" is in checkmate. Programme ended"<<std::endl;
            for (int row = 0; row<8; row++)
            {
                for (int col = 0; col<8; col++)
                {
                    if (board[row][col].piece!=nullptr)
                    {
                        delete board[row][col].piece; // if square has 0 checks it will stay at 0, not decremented
                    }
                }
            }
            exit(0);
        }
        moves_made+=1;
        return;

    }// here move is invalid
    std::cout<<board[source.first][source.second].piece->colour<<"'s "
        <<board[source.first][source.second].piece->piece_name<<" cannot move to "<<to<<std::endl;
        return;
}


ChessBoard::~ChessBoard()
{
    if (buffer_piece != nullptr)
        delete buffer_piece;

    for (int row =0; row<8; row++)
    {
        for (int col = 0; col<8; col++)
        {
            if (board[row][col].piece!=nullptr)
            {
                delete board[row][col].piece;
            }
        }
    }
}