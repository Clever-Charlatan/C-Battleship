#include "header.h"
/**************************************************************************
 *
 * FUNCTION displayBoards
 *
 * ________________________________________________________________________
 * This function receives two board arrays then outputs two grids with the
 * elements of those arrays in the grid - returns nothing.
 * ________________________________________________________________________
 * PRE-CONDITIONS
 *   The following need previously defined functions:
 *      one: the board array of player one
 *      two: the board arary of player two
 *
 * POST-CONDITIONS
 *      This function will output two board grids with board elements.
 *
 * ***********************************************************************/
void displayBoards(char one[][10],  //IN - the board array of player one
                   char two[][10])  //IN - the board arary of player two
{
    //Array of letters for the rows of the grid
    char letters[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

    //OUTPUT: Display that the left board is the user's and the right board
    //        is the enemy's
    cout << setw(18) << " " << "Your Board" << setw(42) << " "
         << "Enemy Board" << endl;
    cout << " ";

    //OUTPUT: Display the column numbers on top of each column 1-10
    for(int i = 1; i < 11; i++)
        cout << setw(4) << right << i;

    //PROCESSING: Separate the number/grid appropriately
    cout << setw(13) << " ";

    //OUTPUT: Display the column numbers on top of each column 1-10
    for(int i = 1; i < 11; i++)
        cout << setw(4) << right << i;

    //OUTPUT: Create a horizontal line for the grid
    cout << endl;
    cout << "  " << MEASURING_STICK << setw(12) << " " << MEASURING_STICK;
    cout << endl;

    //PROCESSING: Will cycle through all ten letters
    for(int ROW = 0; ROW < 10; ROW++)
    {
        //OUTPUT: Display the letter on the left
        cout << letters[ROW];

        //OUTPUT: Displaya the vertical lines and in between the elements
        //        of the board array
        for(int COL = 0; COL < 10; COL++)
        {
            cout << " | " << one[ROW][COL];
        }

        //OUTPUT: Final vertical line and a spacing between the two grids
        cout << " | " << setw(9) << " ";

        //OUTPUT: Display the letter on the left
        cout << letters[ROW];

        //OUTPUT: Displaya the vertical lines and in between the elements
        //        of the board array
        for(int COL = 0; COL < 10; COL++)
        {
            cout << " | " << two[ROW][COL];
        }

        //OUTPUT: Display the final vertical line
        cout << " | ";

        //OUTPUT: Create the bottom horizontal line for the grid
        cout << endl;
        cout << "  " << MEASURING_STICK << setw(12) << " "
             << MEASURING_STICK << endl;
    }
}

/**************************************************************************
 *
 * FUNCTION initFleet
 *
 * ________________________________________________________________________
 * This function receives a PlayerBoard of a user then initializes all
 * ships in the board to a name and size - returns nothing.
 * ________________________________________________________________________
 * PRE-CONDITIONS
 *   The following need previously defined functions:
 *      p: the new initialized board
 *
 * POST-CONDITIONS
 *      This function will initialize all ships in the board.
 *
 * ***********************************************************************/
void initFleet(PlayerBoard &p) //OUT - the new initialized board
{
    //PROCESSING: Initialize all ships in the fleet to their names and
    //            sizes
    p.fleet[0].name = "carrier";
    p.fleet[0].size = CARRIER;
    p.fleet[1].name = "battleship";
    p.fleet[1].size = BATTLESHIP;
    p.fleet[2].name = "cruiser";
    p.fleet[2].size = CRUISER;
    p.fleet[3].name = "submarine";
    p.fleet[3].size = SUBMARINE;
    p.fleet[4].name = "destroyer";
    p.fleet[4].size = DESTROYER;
}

/**************************************************************************
 *
 * FUNCTION spaceOccupied
 *
 * ________________________________________________________________________
 * This function receives a PlayerBoard, row, col, orientation, and size of
 * a ship then outputs whether space is occupied - returns bool.
 * ________________________________________________________________________
 * PRE-CONDITIONS
 *   The following need previously defined functions:
 *      p          : the board of the player
 *      row        : the row of the ship
 *      col        : the col of the ship
 *      orientation: the orientaion of the ship
 *      size       : the size of the ship
 *
 * POST-CONDITIONS
 *      This function will output whether the ship orientation is occupied.
 *
 * ***********************************************************************/
bool spaceOccupied(const PlayerBoard &p, //IN - the board of the player
                   int row,              //IN - the row of the ship
                   int col,              //IN - the col of the ship
                   char orientation,     //IN - the orientaion of the ship
                   int size)             //IN - the size of the ship
{
    //PROCESSING: Checks the first space without orientation
    if(p.board[row][col] != ' ')
    {
        //OUTPUT: Display an appropriate error message
        cout << "Error: Space already occupied." << endl;
        return true;
    }

    //PROCESSING: Based on whether the orientation is 'h' or 'v'
    if(orientation == 'h')
    {
        //PROCESSING: Checks if it will go out of bounds
        if(10 - col < size)
        {
            //OUTPUT: Display an appropriate error message
            cout << "Error: Ship placement is outside the board." << endl;
            return true;
        }

        //PROCESSING: Checks through all spaces that the ship could occupy
        for(int i = 0; i < size; i++)
        {
            if(p.board[row][col + i] != ' ')
            {
                //OUTPUT: Display an appropriate error message
                cout << "Error: Space already occupied." << endl;
                return true;
            }
        }
    }
    else if(orientation == 'v')
    {
        //PROCESSING: Checks if it will go out of bounds
        if(10 - row < size)
        {
            //OUTPUT: Display an appropriate error message
            cout << "Error: Ship placement is outside the board." << endl;
            return true;
        }

        //PROCESSING: Checks through all spaces that the ship could occupy
        for(int i = 0; i < size; i++)
        {
            if(p.board[row + i][col] != ' ')
            {
                //OUTPUT: Display an appropriate error message
                cout << "Error: Space already occupied." << endl;
                return true;
            }
        }
    }

    //PROCESSING: Default return statement
    return false;
}

/**************************************************************************
 *
 * FUNCTION getValidShipInfo
 *
 * ________________________________________________________________________
 * This function receives a PlayerBoard, row, col, orientation, and size of
 * a ship along with the ship's index and a choice between man or machine
 * then outputs a valid row, col, and orientation - returns nothing.
 * ________________________________________________________________________
 * PRE-CONDITIONS
 *   The following need previously defined functions:
 *      row        : the row of the ship
 *      col        : the col of the ship
 *      orientation: the orientaion of the ship
 *      p          : the board of the player
 *      index      : the index of the ship
 *      choice     : machine or another human
 *
 * POST-CONDITIONS
 *      This function will output a valid row, col, and orientaion of ship.
 *
 * ***********************************************************************/
void getValidShipInfo(int &row,          //OUT - the ship's row
                      int &col,          //OUT - the ship's col
                      char &orientation, //OUT - the ship's orientation
                      PlayerBoard &p,    //IN - the board of the player
                      int index,         //IN - the ship's index
                      char choice)       //IN - machine or not
{
    //constants
    char ROW;       //initially receives the row char
    char letters[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    int size;       //size of the ship

    //PROCESSING: Gets the size of the ship based on the ship's index
    size = p.fleet[index].size;

    //PROCESSING: Switch between human implementation of the ship and
    //            machine implementation of the ship
    if(choice == 'H')
    {
        do
        {
            //INPUT & OUTPUT: Prompt the user for the coordinates of the
            //                ship and the orientation and store them
            cout << "Enter the starting coordinates of your "
                 << p.fleet[index].name << ": ";
            cin >> ROW >> col;
            cout << endl;
            cout << "Enter the orientation of your " << p.fleet[index].name
                 << " (horizontal(h) or vertical(v)): ";
            cin >> orientation;
            cout << endl;

            //PROCESSING: Converts the char coordinate into an int
            //            coordinate by running through all of the
            //            possible letters
            for(int i = 0; i < 10; i++)
                if(letters[i] == ROW)
                    row = i;

            //PROCESSING: Columns will be one off of array due to display
            col--;
        }
        //PROCESSING: Runs until there is a location and orientation that
        //            is not invalid
        //spaceOccuped - Will return whether the spaces are occupied or not
        while(spaceOccupied(p, row, col, orientation, size));
    }
    else if(choice == 'M')
    {
        do
        {
            //constants
            int o;

            //PROCESSING: Randomly generate the values within the 0-9 range
            row = rand() % 10;
            col = rand() % 10;
            o = rand() % 2;

            //PROCESSING: Converts the random number to a character
            if(o == 0)
                orientation = 'h';
            else if(o == 1)
                orientation = 'v';
        }
        //PROCESSING: Runs until there is a location and orientation that
        //            is not invalid
        //spaceOccuped - Will return whether the spaces are occupied or not
        while(spaceOccupied(p, row, col, orientation, size));
    }
}

/**************************************************************************
 *
 * FUNCTION setShip
 *
 * ________________________________________________________________________
 * This function receives a PlayerBoard, index, and choice then outputs the
 * ne board of the player with the ship on it by regerence - returns
 * nothing.
 * ________________________________________________________________________
 * PRE-CONDITIONS
 *   The following need previously defined functions:
 *      p          : the board of the player
 *      index      : the index of the ship
 *      choice     : machine or another human
 *
 * POST-CONDITIONS
 *      This function will return the ne board with the ship on it by
 *      reference.
 *
 * ***********************************************************************/
void setShip(PlayerBoard &p, //OUT - the new board with the ship on it
             int index,      //IN - the ship's index
             char choice)    //IN - multiplayer or machine
{
    //constants
    int row;
    int col;
    char orientation;
    vector<Point> temp;

    //getValidShipInfo - Will return valid ship coordinates and orientation
    getValidShipInfo(row, col, orientation, p, index, choice);

    //PROCESSING: Switches based on the orientation of the ship
    if(orientation == 'h')
    {
        //PROCESSING: Cycles through the size of the ship
        for(int i = 0; i < p.fleet[index].size; i++)
        {
            //PROCESSING: Adds that Point to the vector of that ship and
            //            also assigns a ship value ('s') to that space
            p.fleet[index].cells.push_back({row, col+i});
            p.board[row][col + i] = 's';
        }
    }
    else if(orientation == 'v')
    {
        //PROCESSING: Cycles through the size of the ship
        for(int i = 0; i < p.fleet[index].size; i++)
        {
            //PROCESSING: Adds that Point to the vector of that ship and
            //            also assigns a ship value ('s') to that space
            p.fleet[index].cells.push_back({row + i, col});
            p.board[row + i][col] = 's';
        }
    }
}

/**************************************************************************
 *
 * FUNCTION initBoard
 *
 * ________________________________________________________________________
 * This function receives two PlayerBoards along with a choice then outputs
 * the two new initialized boards with ships on them - returns nothing.
 * ________________________________________________________________________
 * PRE-CONDITIONS
 *   The following need previously defined functions:
 *      one        : the board of the first player
 *      two        : the board of the second player
 *      choice     : machine or another human
 *
 * POST-CONDITIONS
 *      This function will return two boards with all ships on them.
 *
 * ***********************************************************************/
void initBoard(PlayerBoard &one, //OUT - the new initialized board
               PlayerBoard &two, //OUT - the new initialized board
               char choice)      //IN - multiplyaer or mchine
{
    //constants
    PlayerBoard temp;

    //PROCESSING: Initializes all elements of the temp board to spaces
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            temp.board[i][j] = ' ';

    //OUTPUT: Prompt the user to set the baord
    cout << "Player 1 set your board." << endl;

    //PROCESSING: Cycles through the size of the fleet
    for(int i = 0; i < FLEET_SIZE; i++)
    {
        //displayBoards - Will display the initial state of the two boards
        displayBoards(one.board, temp.board);

        //setShip - Will set a ship on the board
        setShip(one, i, 'H');
    }

    //displayBoards - Will display the final state of the two boards
    displayBoards(one.board, temp.board);

    //OUTPUT: Prompt the second player to set their board
    cout << endl << endl << endl;
    cout << "Player 2 set your board." << endl;

    //PROCESSING: Switches between a second human player or machine player
    if(choice == 'H')
    {
        //PROCESSING: Cycles through the size of the fleet
        for(int i = 0; i < FLEET_SIZE; i++)
        {
            //displayBoards - Will display the initial state of the two
            //                boards
            displayBoards(two.board, temp.board);

            //setShip - Will set a ship on the board
            setShip(two, i, choice);
        }

        //displayBoards - Will display the final state of the two boards
        displayBoards(two.board, temp.board);
    }
    else if(choice == 'M')
    {
        //PROCESSING: Cycles through the size of the fleet
        for(int i = 0; i < FLEET_SIZE; i++)
        {
            //displayBoards - Will display the initial state of the two
            //                boards
            displayBoards(two.board, temp.board);

            //setShip - Will set a ship on the board but by machine
            setShip(two, i, choice);
        }

        //displayBoards - Will display the final state of the two boards
        displayBoards(two.board, temp.board);
    }
}

/**************************************************************************
 *
 * FUNCTION hitormiss
 *
 * ________________________________________________________________________
 * This function receives two PlayerBoards then outputs the two new updated
 * boards with either a hit or miss on them - returns nothing.
 * ________________________________________________________________________
 * PRE-CONDITIONS
 *   The following need previously defined functions:
 *      p          : the board of the enemy
 *      pguess     : the guessing board for user
 *
 * POST-CONDITIONS
 *      This function will return two boards with hits or misses.
 *
 * ***********************************************************************/
void hitormiss(PlayerBoard &p,       //OUT - the board of the enemy
               PlayerBoard &pguess)  //OUT - the guessing board for user
{
    //constants
    char ROW;
    int row;
    int col;
    char letters[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    bool val;

    //PROCESSING: Initialize all variables
    row = -1;
    val = true;

    do
    {
        //INPUT & OUTPUT: Prompt the user for a location to fire at
        cout << "Fire a shot: ";
        cin >> ROW >> col;

        //PROCESSING: Converts the char coordinate into an int coordinate
        //            by running through all of the possible letters
        for(int i = 0; i < 10; i++)
            if(letters[i] == ROW)
                row = i;

        //PROCESSING: Decrements the column value because it is one less
        //            than the display compared to the array
        col--;

        //PROCESSING: If the shot is out of bounds or has already been hit,
        //            then it is invalid
        if(col < 0 || col > 9 || row == -1 || p.board[row][col] == 'H')
            //OUTPUT: Display an error message for invalid shot
            cout << "Invalid" << endl;
        else
            val = false;
    }
    //PROCESSING: Runs while the val is true or the shot is invalid
    while(val);

    //PROCESSING: Switches based on whehter the shot has hit a ship or not
    if(p.board[row][col] == 's')
    {
        //OUTPUT: Display to user that he or she has hit a ship
        cout << "Hit!!!" << endl;

        //PROCESSING: Assign to both boards that ship has been hit
        pguess.board[row][col] = 'H';
        p.board[row][col] = 'H';

        //PROCESSING: Will cycle through all the ships in the fleet
        for(int i = 0; i < FLEET_SIZE; i++)
        {
            //PROCESSING: Will calculate the size of the ship
            int len;
            len = p.fleet[i].size;

            //PROCESSING: Cycles through all elements of the ship on board
            for(unsigned long j = 0; j < static_cast<unsigned long>(len);
                j++)
            {
                //PROCESSING: If a ship vector element matches the hit
                //            target, then its hitcount will e increased
                if(p.fleet[i].cells.at(j).ROW == row
                        && p.fleet[i].cells.at(j).COL == col)
                {
                    p.fleet[i].hitcount++;

                    //PROCESSING: Checks if hitcount is equal to size to
                    //            see if it has been sunk
                    if(p.fleet[i].hitcount == p.fleet[i].size)
                        //OUTPUT: Display that the ship has been sunk
                        cout << "You sunk the " << p.fleet[i].name << "!!!"
                             << endl;
                }
            }
        }
    }
    else
    {
        //OUTPUT: Display to user that he or she has missed
        cout << "You Missed." << endl;

        //PROCESSING: Assign to both boards that user has missed
        pguess.board[row][col] = 'M';
        p.board[row][col] = 'M';
    }
}

/**************************************************************************
 *
 * FUNCTION machineTest
 *
 * ________________________________________________________________________
 * This function receives two PlayerBoards, row and col of a shot then
 * outputs whether the machine got a hit or miss - returns bool.
 * ________________________________________________________________________
 * PRE-CONDITIONS
 *   The following need previously defined functions:
 *      p          : the board of the enemy
 *      pguess     : the guessing board by user
 *      row        : row of the shot
 *      col        : col of the shot
 *
 * POST-CONDITIONS
 *      This function will output whether the machine fot a hit or miss.
 *
 * ***********************************************************************/
bool machineTest(PlayerBoard &p,      //OUT - the board of the enemy
                 PlayerBoard &pguess, //OUT - the guessing board by user
                 int row,             //IN - row of the shot
                 int col)             //IN - col of the shot
{
    //PROCESSING: Returns true if the shot has already been a hit
    if(p.board[row][col] == 'H')
        return true;

    //PROCESSING: Switches based on whehter the shot has hit a ship or not
    if(p.board[row][col] == 's')
    {
        //OUTPUT: Display to user that he or she has hit a ship
        cout << "Hit!!!" << endl;

        //PROCESSING: Assign to both boards that ship has been hit
        pguess.board[row][col] = 'H';
        p.board[row][col] = 'H';

        //PROCESSING: Will cycle through all the ships in the fleet
        for(int i = 0; i < FLEET_SIZE; i++)
        {
            //PROCESSING: Will calculate the size of the ship
            int len;
            len = p.fleet[i].size;

            //PROCESSING: Cycles through all elements of the ship on board
            for(unsigned long j = 0; j < static_cast<unsigned long>(len);
                j++)
            {
                //PROCESSING: If a ship vector element matches the hit
                //            target, then its hitcount will e increased
                if(p.fleet[i].cells.at(j).ROW == row
                        && p.fleet[i].cells.at(j).COL == col)
                {
                    p.fleet[i].hitcount++;

                    //PROCESSING: Checks if hitcount is equal to size to
                    //            see if it has been sunk
                    if(p.fleet[i].hitcount == p.fleet[i].size)
                        //OUTPUT: Display that the ship has been sunk
                        cout << "You sunk the " << p.fleet[i].name << "!!!"
                             << endl;
                }
            }
        }

        //PROCESSING: Returns that shot has hit a ship
        return true;
    }
    else
    {
        //OUTPUT: Display to user that he or she has missed
        cout << "You Missed." << endl;

        //PROCESSING: Assign to both boards that user has missed
        pguess.board[row][col] = 'M';
        p.board[row][col] = 'M';

        //PROCESSING: Returns to user that shot has missed
        return false;
    }
}

/**************************************************************************
 *
 * FUNCTION Hunt
 *
 * ________________________________________________________________________
 * This function receives a PlayerBoard then outputs a random valid row and
 * col of a shot onto the board - returns nothing.
 * ________________________________________________________________________
 * PRE-CONDITIONS
 *   The following need previously defined functions:
 *      p          : the board of the enemy
 *      row        : row of the random valid shot
 *      col        : col of the random valid shot
 *
 * POST-CONDITIONS
 *      This function will output a random row and col of a shot.
 *
 * ***********************************************************************/
void Hunt(const PlayerBoard &p, //IN - board of the enemy
          int &row,             //OUT - row of random valid shot
          int &col)             //OUT - col of random valid shot
{
    //constants
    bool val;
    val = true;

    //PROCESSING: Runs while val is true or valid
    while(val)
    {
        //PROCESSING: Generates random row and col values
        row = rand() % 10;
        col = rand() % 10;

        //PROCESSING: If cooridnates have already not been shot at, then
        //            loop does not have to run again
        if(p.board[row][col] != 'M' && p.board[row][col] != 'H')
            val = false;
    }
}

/**************************************************************************
 *
 * FUNCTION Target
 *
 * ________________________________________________________________________
 * This function receives a PlayerBoard, row and col of a shot along with a
 * vector of potential shots then outputs whether the machine got a hit or
 * miss - returns nothing.
 * ________________________________________________________________________
 * PRE-CONDITIONS
 *   The following need previously defined functions:
 *      potentials : list of potential shots
 *      p          : the board of the enemy
 *      row        : row of the shot
 *      col        : col of the shot
 *
 * POST-CONDITIONS
 *      This function will output a row and col of a potential shot
 *
 * ***********************************************************************/
void Target(vector<Point> &potentials, //IN - list of potential shots
            const PlayerBoard &p,      //IN - board of the enemy
            int &row,                  //OUT - Returns row of valid shot
            int &col)                  //OUT - Returns col of valid shot
{
    //constants
    bool val;
    val = false;

    //PROCESSING: Only runs if potentials size is greater than zero
    if(potentials.size() != 0)
    {
        do
        {
            //PROCESSING: Reinitialize back to false
            val = false;

            //PROCESSING: Gets the row and col values from the front of the
            //            potentials list
            row = potentials.front().ROW;
            col = potentials.front().COL;

            //PROCESSING: If coordinate has already been hit, then run loop
            //            again to fetch new value and erase the old one
            if(p.board[row][col] == 'H')
            {
                val = true;
                potentials.erase(potentials.begin());
            }
            else
                //PROCESSING: Erase the old value if it is valid
                potentials.erase(potentials.begin());
        }
        while(val);
    }
}

/**************************************************************************
 *
 * FUNCTION computerMode
 *
 * ________________________________________________________________________
 * This function receives two PlayerBoards, a vector of potential shots and
 * an integer for the machine state then outputs the updated boards by
 * reference - returns nothing.
 * ________________________________________________________________________
 * PRE-CONDITIONS
 *   The following need previously defined functions:
 *      p          : the board of the enemy
 *      pguess     : the guessing board
 *      potentials : list of potential shots
 *      mstate     : the machine state
 *
 * POST-CONDITIONS
 *      This function will output the updated boards with shots by the
 *      machine by reference.
 *
 * ***********************************************************************/
void computerMode(PlayerBoard &p,            //OUT - the board of the enemy
                  PlayerBoard &pguess,       //OUT - the guessing board
                  vector<Point> &potentials, //OUT - list of possible shots
                  int &mstate)               //OUT - the machine state
{
    //constants
    int row;
    int col;

    //PROCESSING: Switches between HUNT and TARGET mode
    if(mstate == HUNT)
    {
        //Hunt - Will return random row and col of a shot on board
        Hunt(p, row, col);

        //PROCESSING: If shot hits, then it will change machine state and
        //            push back new potential targets
        if(machineTest(p, pguess, row ,col))
        {
            //PROCESSING: State of machine changes to TARGET
            mstate = TARGET;

            //PROCESSING: As long as surrounding values are within bounds,
            //            theywill be added to the potentials list
            if(col + 1 != 10 && p.board[row][col + 1] != 'H')
                potentials.push_back({row, col + 1});

            if(col - 1 != -1 && p.board[row][col - 1] != 'H')
                potentials.push_back({row, col - 1});

            if(row + 1 != 10 && p.board[row + 1][col] != 'H')
                potentials.push_back({row + 1, col});

            if(row - 1 != -1 && p.board[row - 1][col] != 'H')
                potentials.push_back({row - 1, col});
        }
    }
    else if(mstate == TARGET)
    {
        //Target - Will return a row and col from the front of the list of
        //         potential shots
        Target(potentials, p, row, col);

        //PROCESSING: If shot hits, then it will change machine state and
        //            push back new potential targets
        if(machineTest(p, pguess, row, col))
        {
            //PROCESSING: State of machine stays on TARGET
            mstate = TARGET;

            //PROCESSING: As long as surrounding values are within bounds,
            //            theywill be added to the potentials list
            if(col + 1 != 10 && p.board[row][col + 1] != 'H')
                potentials.push_back({row, col + 1});

            if(col - 1 != -1 && p.board[row][col - 1] != 'H')
                potentials.push_back({row, col - 1});

            if(row + 1 != 10 && p.board[row + 1][col] != 'H')
                potentials.push_back({row + 1, col});

            if(row - 1 != -1 && p.board[row - 1][col] != 'H')
                potentials.push_back({row - 1, col});
        }

        //PROCESSING: Once all surrounding values have been exhausted, then
        //            state of machine will switch to HUNT
        if(potentials.size() == 0)
        {
            mstate = HUNT;
        }
    }
}

/**************************************************************************
 *
 * FUNCTION gameWon
 *
 * ________________________________________________________________________
 * This function receives a PlayerBoard then outputs whether the user has
 * won the game - returns bool.
 * ________________________________________________________________________
 * PRE-CONDITIONS
 *   The following need previously defined functions:
 *      p          : the board of the user
 *
 * POST-CONDITIONS
 *      This function will output whether the user has won the game.
 *
 * ***********************************************************************/
bool gameWon(const PlayerBoard &p) //IN - the board of the user
{
    //PROCESSING: Cycles through the size of the fleet to check if all the
    //            hitcounts of the ships are the same as their size which
    //            means they have been sunk
    for(int i = 0; i < FLEET_SIZE; i++)
        if(p.fleet[i].hitcount != p.fleet[i].size)
            return false;

    return true;
}
