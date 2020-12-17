#ifndef CHECKERS_H
#define CHECKERS_H

#include <iostream>
#include <fstream>
#include  <string>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <string>

using namespace std;




/** \brief The struct is just a point on the board, i.e a square on the board, and it represent all
        charecteristics that a square might have.
 *
 * \param
 * \param
 * \return
 *
 */

struct point{
    //start
    int start_moves_row;
    int start_move_col;
    int start_number;


    //Single moves
    int single_move_row;
    int single_move_col;
    int single_move_col_l;
    int single_number;
    int single_number_l;
    //Jump moves
    int jump_move_row;
    int jump_move_col;
    int jump_move_col_l;
    int jump_number;
    int jump_number_l;
    string state;

 };


 ///this is a sole class that define all the methods of the game
 ///implimentation in checkers.cpp file
 class checkers
 {
    private:


    ///This is an array if all numbers that marks the boards.
    int boardMarkers[12][12];

    ///This is the actual board without numbers, the board mirrors boardmakers
    string gameBoard[12][12];


    /// This array stores the current player, more specifically details about the
    /// current players pieces position on the board
    vector<point> currentPlayerVault;

    /// This array stores allowed moves filtered from the currentPlayerVault
    vector<point> allowedMoves;

    ///This variable stored current board size
    int boardsize;

    /// This string stores the game log temporarily
    string logHistory;

    ///This next two variable stores the number of pieces each player/algorithm  has.
    int alg1;
    int alg2;
    /// The variable is set ti true if any of the algorithms cannot make move
    bool noMove;


 public:

     ///construct that takes the size of the board
     checkers(int boardsize);


     ///This is the first algorithm, it uses random number generator to select the valid move from the allowed moves

     void randomiser();

     /// This is the  second algorithm it chooses the first valid moves in the allowed moves
     void secondAlgorithm();

     /// This boolean function checks if the next anticipated moves is valid, if so the moves are stored in the allowedmoves array
     bool isMoveAllowed(int, int) const;

     /// This boolen in conjunction with isMoveAllowed(int, int) assert if the jump move is possible
     bool jumpAllowed(string, int , int) const;

     ///This function  get all pieces of the current player
     void currentPlayer(string);

     ///This function filters the allowed moves , that is all pieces that are allowed to move.
     void setAllowedMoves(string, string);

     /// This update player pieces position and number of pieces per players
     void update(point p);
     ///Initialise and start the game

     bool startNewGame();

     ///Compute the final score
     void finalScore();


     ///This function logs the game history
     void writeHistory(string);

     ///This function is used to start the game after initialising it
     void startGame();

     point initialPoint();
     ~checkers();
 };

#endif // CHECKERS_H
