#ifndef HEADER_H
#define HEADER_H
/**************************************************************************
 *   Author    :  John Chen
 *   Final Prjt:  Battleship
 *   CLASS     :  CS 002
 *   SECTION   :  MTRF: 7a - 12p
 *   Due Date  :  7/29/19
 *************************************************************************/
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <iomanip>
using namespace std;
/**************************************************************************
 *
 * BATTLESHIP
 * ________________________________________________________________________
 * This program accepts either a choice between a game between the user and
 * the computer or against another person. The game board is initialized
 * with ships in their positions and then the two players take turns
 * shooting at random points on the board until all the ships are
 * destroyed.
 * ________________________________________________________________________
 * INPUT:
 *   choice: To play against a machine or multiplayer -> input from user
 *   row: Row of the ship or shot-> input from user
 *   col: Column of the ship or shot -> input from user
 *   orientation: Orientation of the ship -> input from user
 *
 * OUTPUT:
 *   Will output many things: valid ship placement, shot hit or not, game
 *   won or not, and grid of shots and ships.
 *************************************************************************/
//Global constants
const int CARRIER = 5;
const int BATTLESHIP = 4;
const int CRUISER = 3;
const int SUBMARINE = 3;
const int DESTROYER = 2;
const int FLEET_SIZE = 5;
const string MEASURING_STICK(41, '-');
const int PLAYER1 = 1;
const int PLAYER2 = 2;
const int HUNT = 0;
const int TARGET = 1;

struct Point
{
    int ROW;
    int COL;
};

struct Ship
{
    string name;
    int size;
    int hitcount = 0;
    vector<Point> cells;
};

struct PlayerBoard
{
    char board[10][10];
    Ship fleet[FLEET_SIZE];
};

/**************************************************************************
* updateUnsolved
*  This function receives an unsolved string and replaces all instances
*  of the guessed character within the unsolved string by comparing it to
*  the phrase.
*   - returns string -> This will be dashes with replaced letters
* ************************************************************************/
string updateUnsolved(string phrase,   //IN - the actual phrase inputted
                      string unsolved, //IN - the updated guessed string
                      char guess);     //IN - the guessed letter

/**************************************************************************
* displayBoards
*  This function receives two board arrays and then outputs two grids in a
*  formatted style with numbers and letters.
*   - returns nothing -> This will be two grids
* ************************************************************************/
void displayBoards(char one[][10],  //IN - the board array of player one
                   char two[][10]); //IN - the board arary of player two

/**************************************************************************
* initFleet
*  This function receives a PlayerBoard and then it will initialize it with
*  all the ships by prompting the user for the location and orientation.
*   - returns nothing -> Will return the initialized PlayerBoard by
*                        reference
* ************************************************************************/
void initFleet(PlayerBoard &p); //OUT - the new initialized board

/**************************************************************************
* spaceOccupied
*  This function receives a PlayerBoard along with the location, size, and
*  orientation of the ship. Then, it will output whether the ship can be
*  placed there in that way.
*   - returns bool -> Will be whether the space is occupied or not
* ************************************************************************/
bool spaceOccupied(const PlayerBoard &p, //IN - the board of the player
                   int row,              //IN - the row of the ship
                   int col,              //IN - the col of the ship
                   char orientation,     //IN - the orientaion of the ship
                   int size);            //IN - the size of the ship

/**************************************************************************
* getValidShipInfo
*  This function receives a PlayerBoard along with the location, size, and
*  orientation of the ship. Then, it will continually prompt the user for a
*  valid ship location by calling the spaceOccupied function. Will also be
*  doing the automatic inputs for the machine.
*   - returns nothing -> Returns a valid ship location and orientation by
*                        reference
* ************************************************************************/
void getValidShipInfo(int &row,          //OUT - the ship's row
                      int &col,          //OUT - the ship's col
                      char &orientation, //OUT - the ship's orientation
                      PlayerBoard &p,    //IN - the board of the player
                      int index,         //IN - the ship's index
                      char choice);      //IN - machine or not

/**************************************************************************
* setShip
*  This function receives a PlayerBoard and the ship's index then it will
*  set the ship on the board.
*   - returns nothing -> Sets a ship on the board
* ************************************************************************/
void setShip(PlayerBoard &p, //OUT - the new board with the ship on it
             int index,      //IN - the ship's index
             char choice);   //IN - multiplayer or machine

/**************************************************************************
* initBoard
*  This function receives two PlayerBoards, one for each user, and then it
*  will initialize the boards by calling the setShip functions for all the
*  ships in the fleet.
*   - returns nothing -> Returns the two player's boards by reference
* ************************************************************************/
void initBoard(PlayerBoard &one, //OUT - the new initialized board
               PlayerBoard &two, //OUT - the new initialized board
               char choice);     //IN - multiplyaer or mchine

/**************************************************************************
* hitormiss
*  This function receives two PlayerBoards, one for the enemy and one for
*  the guessing by the user, and then it will prompt for the location to
*  fire at. It will put the result on the board and output an appropriate
*  message to the user.
*   - returns nothing -> Returns the two boards by reference
* ************************************************************************/
void hitormiss(PlayerBoard &p,       //OUT - the board of the enemy
               PlayerBoard &pguess); //OUT - the guessing board for user

/**************************************************************************
* gameWon
*  This function receives a PlayerBoard and checks if all the ships are
*  destroyed then outputs whether the game has been won by the user.
*   - returns bool -> This will be whether the user won the game or not
* ************************************************************************/
bool gameWon(const PlayerBoard &p); //IN - the board of the user

/**************************************************************************
* computerMode
*  This function receives two PlayerBoards, one for the enemy and one for
*  the guessed state of the enemy, as well as a vector of potentials and
*  the machine state. Then, it will fire a shot based on random numbers or
*  from the list of potential shots.
*   - returns nothing -> This will be a shot at the board
* ************************************************************************/
void computerMode(PlayerBoard &p,            //OUT - the board of the enemy
                  PlayerBoard &pguess,       //OUT - the guessing board
                  vector<Point> &potentials, //OUT - list of possible shots
                  int &mstate);              //OUT - the machine state

/**************************************************************************
* machineTest
*  This function receives two PlayerBoards, one for the enemy and one for
*  the guessed state of the enemy, along with the firing location. Then, it
*  will output whether a ship has been hit by the shot.
*   - returns bool -> This will be whethe the machine hit a ship
* ************************************************************************/
bool machineTest(PlayerBoard &p,      //OUT - the board of the enemy
                 PlayerBoard &pguess, //OUT - the guessing board by user
                 int row,             //IN - row of the shot
                 int col);            //IN - col of the shot

/**************************************************************************
* Target
*  This function receives a Playerboard and checks the next Point from the
*  list of potential shots to the board also returning a valid shot.
*   - returns nothing -> This will be a shot at the board by reference
* ************************************************************************/
void Target(vector<Point> &potentials, //IN - list of potential shots
            const PlayerBoard &p,      //IN - board of the enemy
            int &row,                  //OUT - Returns row of valid shot
            int &col);                 //OUT - Returns col of valid shot

/**************************************************************************
* Hunt
*  This function receives a PlayerBoards and shoots randomly at the board
*  and returns the location by reference as long as it has not already been
*  shot at.
*   - returns nothing -> This will be a shot at the board by reference
* ************************************************************************/
void Hunt(const PlayerBoard &p, //IN - board of the enemy
          int &row,             //OUT - row of random valid shot
          int &col);            //OUT - col of random valid shot

#endif // HEADER_H
