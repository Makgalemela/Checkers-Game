
#include <iostream>
#include <fstream>
#include  <string>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <string>
#include "checkers.h"



using namespace std;
///The function read the board sizes and feed them to the game engine
vector<int> boardSizes(){


    int temp_size = 0;
    ifstream inFile;
    inFile.open("input.txt");
    vector<int> arrSizes;

    while (inFile.is_open() && inFile>>temp_size){

        if(temp_size%2 ==0){
            if(temp_size >5){
                if(temp_size <13){
                    arrSizes.push_back(temp_size);
                }
            }
        }

    }

    return arrSizes;

}

int main()
{
    srand(time(NULL));

    vector<int> boardsize(boardSizes());
    for(int i = 0 ; i < boardsize.size(); i++){

        checkers c(boardsize.at(i));
        c.startGame();

        while(c.startNewGame()==false){
             c.randomiser();
             c.secondAlgorithm();
        }
        c.finalScore();
        c.writeHistory(" ");

    }


    return 0;
}
