#include "header.h"

int main()
{
    //constants
    PlayerBoard one;          //CALC - Board of PLAYER1
    PlayerBoard two;          //CALC - Board of PLAER2
    PlayerBoard oneGuess;     //CALC - Guessed board state of P2 by P1
    PlayerBoard twoGuess;     //CALC - Guessed board state of P1 by P2
    int turn;                 //CALC - Which player's turn - start with P1
    char choice;              //IN - To play multiplayer or machine
    vector<Point> potentials; //CALC - List of potentials areas to shoot
    bool state;               //CALC - State of the game
    int machinestate;         //CALC - State of the machine - HUNT / TARGET

    //PROCESSING: Initialize variables - turn always starts with PLAYER1
    //             - state of the program is alive in beginning - state of
    //            the machine is to HUNT for a shot first
    turn = PLAYER1;
    state = true;
    machinestate = HUNT;

    //PROCESSING: Gives all elements in the four boards an initial value
    //            of spaces
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            one.board[i][j] = ' ';
            two.board[i][j] = ' ';
            oneGuess.board[i][j] = ' ';
            twoGuess.board[i][j] = ' ';
        }
    }

    //initFleet - Initializes all ships in the fleet with the appropriate
    //            information
    initFleet(one);
    initFleet(two);

    //INPUT & OUTPUT: Prompt the user for whether he or she wants to play
    //                multiplayer or against a machine and store it
    cout << "Human(H) or machine(M)? ";
    cin >> choice;
    cout << endl;

    //initBoard - Ships are set on the board based on user prompts
    initBoard(one, two, choice);

    //PROCESSING: For the user who wants to play multiplayer
    if(choice == 'H')
    {
        //PROCESSING: Runs while the state of the game is still active
        while(state)
        {
            //OUTPUT: Display the user turn
            cout << endl << endl << endl;
            cout << "Player " << turn << ": " << endl;

            if(turn == PLAYER1)
            {
                //hitormiss - Takes in shot and puts that shot on the board
                //            along with whether it was a hit
                hitormiss(two, twoGuess);

                //displayBoards - Displays the board of the user and the
                //                guessed board of the opponent's
                displayBoards(one.board, twoGuess.board);

                //gameWon - Returns whether the game has been won by the
                //          current player based on ships left
                if(gameWon(two))
                {
                    //OUTPUT: Display the message telling the user that he
                    //        or she has won the game
                    cout << "You sunk the fleet!!! You win!!!" << endl;

                    //PROCESSING: Change the state of the game to end the
                    //            program
                    state = false;
                }

                //PROCESSING: Switches the turn to the other player
                turn = PLAYER2;
            }
            else if(turn == PLAYER2)
            {
                //hitormiss - Takes in shot and puts that shot on the board
                //            along with whether it was a hit
                hitormiss(one, oneGuess);

                //displayBoards - Displays the board of the user and the
                //                guessed board of the opponent's
                displayBoards(two.board, oneGuess.board);

                //gameWon - Returns whether the game has been won by the
                //          current player based on ships left
                if(gameWon(one))
                {
                    //OUTPUT: Display the message telling the user that he
                    //        or she has won the game
                    cout << "You sunk the fleet!!! You win!!!" << endl;

                    //PROCESSING: Change the state of the game to end the
                    //            program
                    state = false;
                }

                //PROCESSING: Switches the turn to the other player
                turn = PLAYER1;
            }
        }
    }
    //PROCESSING: For players who want to play against a machine
    else if(choice == 'M')
    {
        //PROCESSING: Runs while the state of the game is still active
        while(state)
        {
            //OUTPUT: Display the user turn
            cout << "Player " << turn << ": " << endl;

            if(turn == PLAYER1)
            {
                //hitormiss - Takes in shot and puts that shot on the board
                //            along with whether it was a hit
                hitormiss(two, twoGuess);

                //displayBoards - Displays the board of the user and the
                //                guessed board of the opponent's
                displayBoards(one.board, twoGuess.board);

                //gameWon - Returns whether the game has been won by the
                //          current player based on ships left
                if(gameWon(two))
                {
                    //OUTPUT: Display the message telling the user that he
                    //        or she has won the game
                    cout << "You sunk the fleet!!! You win!!!" << endl;

                    //PROCESSING: Change the state of the game to end the
                    //            program
                    state = false;
                }

                //PROCESSING: Switches the turn to the other player
                turn = PLAYER2;
            }
            else if(turn == PLAYER2)
            {
                //computerMode - Will switch between Hunt mode and Target
                //               mode based on the machinestate
                computerMode(one, oneGuess, potentials, machinestate);

                //displayBoards - Displays the board of the user and the
                //                guessed board of the opponent's
                displayBoards(two.board, oneGuess.board);

                //gameWon - Returns whether the game has been won by the
                //          current player based on ships left
                if(gameWon(one))
                {
                    //OUTPUT: Display the message telling the user that he
                    //        or she has won the game
                    cout << "You sunk the fleet!!! You win!!!" << endl;

                    //PROCESSING: Change the state of the game to end the
                    //            program
                    state = false;
                }

                //PROCESSING: Switches the turn to the other player
                turn = PLAYER1;
            }
        }
    }
}
