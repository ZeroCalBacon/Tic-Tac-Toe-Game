#ifndef GAME_H
#define GAME_H
#define BOARD_DIMENSION 3

#include "Player.h"
#include <iostream>
#include <string>
#include <cmath>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
using namespace std;

class Game {
    private:
    char gameBoard[BOARD_DIMENSION][BOARD_DIMENSION];
    int count;

    public:
    //CreateBoard function
    void CreateBoard() {
        //iterate over rows
        for (int i = 0; i < BOARD_DIMENSION; i++) {
            //iterate over columns of the row
            for (int j = 0; j < BOARD_DIMENSION; j++){
                //initialize empty value
                gameBoard[i][j] = ' ';
            }
        }
        //call the showBoard() function.
        showBoard();
    }
    
    //showBoard function
    void showBoard() {
        printf("\n\n");
        cout << "\t\t\t----------------" << endl;
        //iterate over the rows
        for (int i = 0; i < BOARD_DIMENSION; i++) {
            //space using the tab character
            cout << "\t\t\t";
            //iterate over the column of the row
            for (int j = 0; j < BOARD_DIMENSION; j++) {
                cout << " | ";
                if (gameBoard[i][j] == 'X') {
                    cout << "\033[31mX\033[0m";
                } else if (gameBoard[i][j] == 'O') {
                    cout << "\033[32mO\033[0m";
                } else {
                    cout << " ";
                }
            }
            cout << " |\n\t\t\t----------------" << endl;  
        }
    }

    //Reset funtion
    void Reset() {
        //iterate over rows
        for (int i = 0; i < BOARD_DIMENSION; i++) {
            //iterate over columns of the row
            for (int j = 0; j < BOARD_DIMENSION; j++){
                //initialize empty value
                gameBoard[i][j] = ' ';
            }
        }
        //call the showBoard() function.
        showBoard();
        count = 0;
    }
    
    //PrintRules function
    void PrintRules() {
        //tic-tac-toe rules
        system("cls");
        string rule1 = "Tic-tac-toe is a two-player game, played on a 3x3 grid.\n";
        for (int i = 0; i < rule1.length(); i++) {
            cout << rule1[i] << flush;
            this_thread::sleep_for(chrono::milliseconds(10));
        }
        cout << "\nPRESS [ENTER] TO CONTINUE...";
        cin.ignore();
        cin.get();

        //prints each character of the rule one by one with a short delay in between
        string rule2 = "\nThe players take turns placing their mark (X or O) on the grid.\n";
        for (int i = 0; i < rule2.length(); i++) {
            cout << rule2[i] << flush;
            this_thread::sleep_for(chrono::milliseconds(10));
        }
        cout << "\nPRESS [ENTER] TO CONTINUE...";
        cin.ignore();

        string rule3 = "\nThe first player to get three of their marks in a row (horizontally, vertically, or diagonally) wins.\n";
        for (int i = 0; i < rule3.length(); i++) {
            cout << rule3[i] << flush;
            this_thread::sleep_for(chrono::milliseconds(10));
        }
        cout << "\nPRESS [ENTER] TO CONTINUE...";
        cin.ignore();

        string rule4 = "\nIf all of the spaces on the grid are filled and no player has won, the game is a draw.\n";
        for (int i = 0; i < rule4.length(); i++) {
            cout << rule4[i] << flush;
            this_thread::sleep_for(chrono::milliseconds(10));
        }
        cout << "\nPRESS [ENTER] TO CONTINUE...";
        cin.ignore();

        string rule5 = "\nTo make a move, enter the number of the square you wish to place your symbol (as shown below): \n";
        for (int i = 0; i < rule5.length(); i++) {
            cout << rule5[i] << flush;
            this_thread::sleep_for(chrono::milliseconds(10));
        }

        // Display example board with square numbers
        string rule6 = R"(
         -------------
         | 1 | 2 | 3 |
         -------------
         | 4 | 5 | 6 |
         -------------
         | 7 | 8 | 9 |
         -------------
        )";
        for (int i = 0; i < rule6.length(); i++) {
            cout << rule6[i] << flush;
            this_thread::sleep_for(chrono::milliseconds(10));
        }
        cout << "\n";
    }


    //PlayTurn function w/ player object
    void PlayerTurn(Player &player) {
        //position of a cell given by the player
        int position;
        //row to which the position belongs
        int row;

        //name of player using PlayerName() function
        cout << player.PlayerName() << "'s" << " Turn" << endl;
        //get the position
        cout << "Enter your position:\n>>";

        if (!(cin >> position)) {
            cout << "\nInvalid Position! Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            PlayerTurn(player);
            return;
        }

        //check position correct
        if (position < 1 || position > 9) {
            cout << "\nPick a correct position! (1-9)" << endl;
            //restart funct
            PlayerTurn(player);
            return;
        }
        //compute the row w/ ceil() function
        row = ceil((float)position / BOARD_DIMENSION);
        //compute the column to which the position belongs
        int col = (position - 1) % BOARD_DIMENSION;
        //check to find if position empty
        if (gameBoard[row - 1][col] != ' ') {
            cout << "\nPosition already marked! Choose another." << endl;
            // restart the function
            PlayerTurn(player);
            return;
        }
         //mark position as X if it was player 1 
         //mark position as Y if it was player 2
         player.PlayerName().compare("Player I") == 0 ? gameBoard[row - 1][col] = 'X' : gameBoard[row - 1][col] = 'O';
         cout << player.PlayerName() << " Marked: " << position << endl;
         // increment count
         count++;
        
        showBoard();
        
    }

    //MachineTurn function
    void MachineTurn(bool firstAttempt = true) {
        //random position w/ rand() function
        int random_position;

        if (firstAttempt) {
            //computing position between 1-9 for 3X3 matrix
            cout << "CPU's Turn" << endl;
            cout << "CPU's thinking of";
            for (int i = 0; i < 3; i++) {
                //wait for 200 milliseconds
                this_thread::sleep_for(chrono::milliseconds(200));
                cout << ".";
                //flush output buffer to display dots immediately
                cout.flush();
                //wait for 200 milliseconds
                this_thread::sleep_for(chrono::milliseconds(200)); 
            }
        }
        random_position = rand() % (BOARD_DIMENSION * BOARD_DIMENSION + 1);

        //computing row where position is present
        int row = ceil((float)random_position / BOARD_DIMENSION);
        //computing column where position is present
        int col = (random_position - 1) % 3;

        //check if position is already marked
        if (gameBoard[row - 1][col] != ' ') {
            //call the function again to replay
            MachineTurn(false);
        }
        else {
            //delay (randomized 1-3 seconds)
            srand(time(NULL));
            int delay_time = rand() % 3 + 1;
            this_thread::sleep_for(chrono::seconds(delay_time));

            cout << "\nCPU Marked: " << random_position << endl;
            //marking the position with O
            gameBoard[row - 1][col] = 'O';
            //incrementing count
            count++;
        }
        if (firstAttempt) {
            showBoard();
        }
        
    }

    //CheckWin function
    string CheckWin() {
        //check in the horizontal direction
        int r1 = 0, r2 = 0;
        //check in the vertical direction
        int c1 = 0, c2 = 0;
        //check in the diagonal direction
        int d1 = 0, d2 = 0;

        //symbol X and O
        char x = 'X';
        char o = 'O';

        //iterate over the rows
        for (int i = 0; i < BOARD_DIMENSION; i++) {
            //initialize horizontal and vertical variables to zero
            r1 = 0, r2 = 0;
            c1 = 0, c2 = 0;

            //iterate the columns
            for (int j = 0; j < BOARD_DIMENSION; j++) {
                //increment for horizontal values
                if (gameBoard[i][j] == x) {
                    r1++;
                }
                else if (gameBoard[i][j] == o) {
                    r2++;
                }
                //increment for vertical values
                if (gameBoard[j][i] == x) {
                    c1++;
                }
                else if (gameBoard[j][i] == o) {
                    c2++;
                }
            }

            if (r1 == BOARD_DIMENSION || c1 == BOARD_DIMENSION) {
                return "Player I";
            }
            else if (r2 == BOARD_DIMENSION || c2 == BOARD_DIMENSION) {
                return "Player II";
            }

            //increment for diagonal values (top L to bottom R)
            if (gameBoard[i][i] == x) {
                d1++;
            }
            else if (gameBoard[i][i] == o) {
                d2++;
            }
        }

        //check for diagonal wins (top L to bottom R)
        if (d1 == BOARD_DIMENSION) {
            return "Player I";
        }
        else if (d2 == BOARD_DIMENSION) {
            return "Player II";
        }

        //reset diagonal counters
        d1 = 0, d2 = 0;

        //increment for diagonal values (top R to bottom L)
        for (int i = 0; i < BOARD_DIMENSION; i++) {
            if (gameBoard[i][BOARD_DIMENSION - 1 - i] == x) {
                d1++;
            }
            else if (gameBoard[i][BOARD_DIMENSION - 1 - i] == o) {
                d2++;
            }
        }

        //check for diagonal wins (top R to bottom L)
        if (d1 == BOARD_DIMENSION) {
            return "Player I";
        }
        else if (d2 == BOARD_DIMENSION) {
            return "Player II";
        }

        //check for a draw
        if (count == BOARD_DIMENSION * BOARD_DIMENSION) {
            return "Draw";
        }
        return "";
    }
};

#endif // PLAYER_H