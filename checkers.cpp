#include "checkers.h"

checkers::checkers(int boardsize){
     this->boardsize=boardsize;
     logHistory ="";
 }



//set all initial points

point checkers::initialPoint(){

    point p;

    p.jump_move_col =-1;
    p.jump_move_row = -1;
    p.jump_number =-1;
    p.single_move_col = -1;
    p.single_move_row = -1;
    p.single_number = -1;
    p.start_move_col = -1;
    p.start_moves_row = -1;
    p.start_number = -1;
    p.state = "free";

    p.jump_number_l =-1;
    p.single_number_l =-1;

    return p;

}
//update the board

bool checkers::startNewGame(){

    if(noMove ==true) return true;
    return false;
}


void checkers::finalScore(){



    writeHistory("tp1 "+ to_string(alg1));
   writeHistory("tp2 "+ to_string(alg2));

   if(alg1 < alg2)  writeHistory("wp1");
   else if(alg1 >alg2)  writeHistory("wp2");
   else if(alg1 ==alg2)  writeHistory("d");

}
void checkers::update(point p){



    ///we update base on hierachy;
     gameBoard[p.start_moves_row][p.start_move_col] ="free";
    if(p.jump_number > 0){
       gameBoard[p.jump_move_row][p.jump_move_col] = p.state;
       gameBoard[p.single_move_row][p.single_move_col] = "free";
       logHistory += to_string(p.start_number)+"x"+to_string(p.single_number) +"("+ to_string(p.jump_number)+")";
       if(p.state == "p2") alg1--;
       else alg2--;

    }
    else if(p.jump_number_l >0){
         gameBoard[p.jump_move_row][p.jump_move_col_l] = p.state;
         gameBoard[p.single_move_row][p.single_move_col_l] = "free";
         logHistory += to_string(p.start_number)+"x"+to_string(p.single_number_l)+ "("+ to_string(p.jump_number_l)+")";
         if(p.state == "p2") alg1--;
         else alg2--;
    }
    else if(p.single_number_l >0){
         gameBoard[p.single_move_row][p.single_move_col_l] = p.state;
         logHistory += to_string(p.start_number)+"-"+to_string(p.single_number_l);
    }
    else if(p.single_number > 0){
           gameBoard[p.single_move_row][p.single_move_col] = p.state;
           logHistory += to_string(p.start_number)+"-"+to_string(p.single_number);
    }


}


void checkers::setAllowedMoves(string anotherPlayer, string direction){


    for(unsigned i = 0 ; i < currentPlayerVault.size(); i++){

        /// playing and playing

        point p(currentPlayerVault.at(i));


        if(direction == "down"){

            p.single_move_row = p.start_moves_row +1;
            p.jump_move_row = p.single_move_row+1;
        }

        else  if(direction == "up"){

            p.single_move_row = p.start_moves_row -1;;
            p.jump_move_row = p.single_move_row-1;
        }

        if(isMoveAllowed(p.single_move_row,p.single_move_col)){
            point point_(p);
            point_.single_number = boardMarkers[p.single_move_row][p.single_move_col];
           // cout<<"Point -> 1 "<<point_.single_number<<endl;
            allowedMoves.push_back(point_);
        }

        if(isMoveAllowed(p.single_move_row , p.single_move_col_l)) {
            point point_(p);
            point_.single_number_l = boardMarkers[p.single_move_row][p.single_move_col_l];
           // cout<<"Point -> 2 "<<point_.single_number_l<<endl;
            allowedMoves.push_back(point_);

        }

        ///jump moves


        if(isMoveAllowed(p.jump_move_row , p.jump_move_col)  && jumpAllowed(anotherPlayer,p.single_move_row, p.single_move_col)){
            point point_(p);
            point_.single_number = boardMarkers[p.jump_move_row][p.jump_move_col];
            //point_.single_number_l = boardMarkers[p.single_move_row][p.single_move_col_l];
            point_.jump_number = boardMarkers[p.single_move_row][p.single_move_col];
            // cout<<"Point -> 1 "<<point_.single_number<<endl;
            allowedMoves.push_back(point_);
        }


        if(isMoveAllowed(p.jump_move_row , p.jump_move_col_l)  && jumpAllowed(anotherPlayer,p.single_move_row, p.single_move_col_l)){

            point point_(p);
            point_.single_number_l= boardMarkers[p.jump_move_row][p.jump_move_col_l];
            //point_.single_number_l = boardMarkers[p.single_move_row][p.single_move_col_l];
            point_.jump_number_l = boardMarkers[p.single_move_row][p.single_move_col_l];
            // cout<<"Point -> 2 "<<point_.single_number_l<<endl;
            allowedMoves.push_back(point_);
        }


    }

}
//

void checkers::currentPlayer(string player){
    currentPlayerVault.clear();
    allowedMoves.clear();
    for(int i = 0; i <boardsize ; i++){
        for(int j = 0;  j<boardsize;j++){
            if(gameBoard[i][j]==player){
                    point p(initialPoint());
                        ///initial position of the player
                        p.start_moves_row =i;
                        p.start_move_col =j;
                        ///single move moves columns , left and right
                        p.single_move_col = j+1;
                        p.single_move_col_l = j-1;
                        ///move when jumping
                        p.jump_move_col = j+2;
                        p.jump_move_col_l = j-2;
                        ///initial number
                        p.start_number = boardMarkers[i][j];
                        ///state is player
                        p.state = player;
                        currentPlayerVault.push_back(p);
            }
       }
    }

}



bool checkers::isMoveAllowed(int row , int col) const{
    int size_ = boardsize -1;

    if(col >= 0 && col <= size_ && row >= 0 && row <=size_){
        if(gameBoard[row][col]=="free"){
            return true;
        }
    }

    return false;
}
//

bool  checkers::jumpAllowed(string anotherPlayer, int row, int col) const{
     int size_ = boardsize -1;

    if(col >= 0 && col <= size_ && row >= 0 && row <=size_){
        if(gameBoard[row][col]==anotherPlayer){
            return true;
        }
    }
    return false;
}




 void checkers::startGame(){

     ///board numbers

     int pieces = 0;
     if(boardsize ==6) pieces =6;
     else if(boardsize == 8)  pieces = 12;
     else if(boardsize ==10 ) pieces =20;
     else if(boardsize =12 ) pieces = 30;
    int numb = 0;
    alg1 = alg2 = pieces;
    noMove = false;
    writeHistory(to_string(boardsize));
    ///board numbers initialised
     for(int i = 0; i <boardsize ; i++){
         for(int j = 0;  j<boardsize;j++){

            if(i%2 ==0 && j%2 !=0) {
                 numb = numb+1;
                boardMarkers[i][j] = numb;
                if(pieces > 0){
                    gameBoard[i][j] = "p1";
                    pieces = pieces-1;
                }
                else if(pieces == 0 && i >=((boardsize/2)-1)&& i <= boardsize/2){
                    gameBoard[i][j]="free";
                }
                else{
                    gameBoard[i][j]="p2";
                }
            }else if(i%2 != 0 && j%2 ==0){
                 numb = numb+1;
                boardMarkers[i][j] = numb;
                if(pieces > 0){
                    gameBoard[i][j] = "p1";
                    pieces = pieces-1;
                }
                else if(pieces == 0 && i >=((boardsize/2)-1 )&& i <= boardsize/2){
                    gameBoard[i][j]="free";
                }
                else{
                    gameBoard[i][j]="p2";
                }
            }
            else{
                boardMarkers[i][j]=-10;
                gameBoard[i][j]="undifined";
            }
         }
     }



    //    for(int i = 0; i <boardsize ; i++){
    //      for(int j = 0;  j<boardsize;j++){
    //          cout<<boardMarkers[i][j]<<' ';
    //      }
    //      cout<<endl;
    //  }



 }
 checkers::~checkers()
 {
 }





////Algorithms

void checkers::randomiser(){
    logHistory ="";
    currentPlayer("p1");
    setAllowedMoves("p2","down");
    int numberOfAllowedMoves = allowedMoves.size();

    if(numberOfAllowedMoves > 0){
        int x = rand()%numberOfAllowedMoves;
         point p(allowedMoves.at(x));
         update(p);
    }
    else
    {
        noMove = true;
    }

    if(logHistory.length() > 0) writeHistory("p1 "+logHistory);

}


///algorithm two


///



void checkers::secondAlgorithm(){
    logHistory = "";
    currentPlayer("p2");
    setAllowedMoves("p1","up");
    int numberOfAllowedMoves = allowedMoves.size();
    if(numberOfAllowedMoves > 0){
        noMove=false;
        int x = 0;
        point p(allowedMoves.at(x));
        update(p);
    }
    if(logHistory.length() > 0) writeHistory("p2 "+logHistory);
}


void checkers::writeHistory(string nLine){
    ofstream out("results.txt" , std::ios_base::app);
    out<<nLine<<endl;
}
