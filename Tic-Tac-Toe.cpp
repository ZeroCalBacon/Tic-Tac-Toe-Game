#include "Player.h"
#include "Game.h"
#include "Art.h"
#include <iostream>
#include <limits>
#include <chrono>
#include <cstdlib>
#include <thread>
using namespace std;

int main() {
    const int fps = 60;
    const chrono::milliseconds frameTime(1000 / fps);

    this_thread::sleep_for(chrono::milliseconds(150));
    cout << Art::redLetter() + "Game loading";
    for (int i = 0; i < 5; i++) {
        //wait for 200 milliseconds
        this_thread::sleep_for(chrono::milliseconds(150));
        cout << ".";
        // flush output buffer to display dots immediately
        cout.flush();
        //wait for 200 milliseconds
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    cout << "\n\n" << Art::greenLetter() + "Game loaded successfully!" + Art::resetLetter() << endl;
    this_thread::sleep_for(chrono::seconds(1));
    system("cls");

    //INTRO - ASCII Art (method called)
    for (char c : Art::asciiIntro()) {
        if (isspace(c)) {
            cout << flush << c;
        } else {
            cout << flush << c;
            this_thread::sleep_for(chrono::milliseconds(1));
        }
    }

    cout << "\n\nPRESS [ENTER] TO START\n>>>";
    cin.ignore();
    
    //INTRO - clears art
    system("cls");

    //initializing bool
    bool playAgain = true;
    while (playAgain) {
        //initializing mode selection 
        int ch = 0;

        //MENU - ASCII Art (method called)
        for (char c : Art::asciiMenu()) {
            if (isspace(c)) {
                cout << flush << c;
            }
            else {
                cout << flush << c;
                this_thread::sleep_for(chrono::microseconds(900));
            }
        }
        
        //mode selection (exception handling)
        do {
            //try, selection menu
            try {
                cout << ">>>";
                cin >> ch;
                //if selection fails
                if (cin.fail() || (ch < 1 || ch > 4)) {
                    throw invalid_argument("\033[1;31mERROR: Invalid Selection!\033[0m\n");
                }
                break;
            }   
            //catch, throws exception
            catch (const exception& e) {
                cerr << e.what() << endl;
                cin.clear();
                cin.ignore();
                ch = 0;
            }
        } while (true);
        
        //MENU - clears art
        system("cls");

        //obj Game class
        Game *game = new Game;
        //initializing 2D array for gameBoard
        game->CreateBoard();

        //obj for Player I
        Player player("Player I");
        Player player2("Player II");
        
        //CheckWin func result
        string fin = "";
        bool flag = true;
        //Switch case
        switch (ch) {
            //CASE 1 (SINGLEPLAYER)
            case 1: {
                bool rematchCPU = true;
                do {
                    while (flag){
                        //player turn
                        game->PlayerTurn(player);
                        //check if player 1 won or not
                        fin = game->CheckWin();
                        if (fin != "") {
                            goto point;
                        }

                        //machine turn
                        game->MachineTurn();
                        //check if any player won the game
                        fin = game->CheckWin();

                        //conditions to check who won
                        point:
                        //player 1 won
                        if (fin == "Player I") {
                            this_thread::sleep_for(chrono::seconds(2));
                            system("cls");
                            for (char c : Art::asciiUser()) {
                                if (isspace(c)) {
                                    cout << flush << c;
                                } 
                                else {
                                    cout << flush << c;
                                    this_thread::sleep_for(chrono::microseconds(1000));
                                }
                            }
                            this_thread::sleep_for(chrono::seconds(1));
                            flag = false;
                        }
                        
                        //player 2 won
                        else if (fin == "Player II") {
                            system("cls");
                            for (char c : Art::asciiCPU()) {
                                if (isspace(c)) {
                                    cout << flush << c;
                                } 
                                else {
                                    cout << flush << c;
                                    this_thread::sleep_for(chrono::microseconds(1000));
                                }
                            }
                            this_thread::sleep_for(chrono::seconds(1));
                            flag = false;
                        }
                        //draw
                        else if (fin == "Draw") {
                            system("cls");
                            for (char c : Art::asciiDraw()) {
                                if (isspace(c)) {
                                    cout << flush << c;
                                } 
                                else {
                                    cout << flush << c;
                                    this_thread::sleep_for(chrono::microseconds(1000));
                                }
                            }
                            this_thread::sleep_for(chrono::seconds(1));
                            flag = false;
                        }
                    }

                    //rematch
                    char choice = ' ';
                    this_thread::sleep_for(chrono::seconds(1));
                    system("cls");
                    cout << Art::orangeLetter();
                    for (char c : Art::asciiCPURematch()) {
                        if (isspace(c)) {
                            cout << flush << c;
                        } 
                        else {
                            cout << flush << c;
                            this_thread::sleep_for(chrono::microseconds(1000));
                        }
                    }
                    cout << Art::resetLetter();
                    cout << "Do you want to rematch (Y/N)?\n>>>";
                    cin >> choice;
                    while (choice!= 'Y' && choice!= 'y' && choice!= 'N' && choice!= 'n'){
                        cout << "\033[1;31mERROR: Invalid Selection!\033[0m\n";
                        cout << "Do you want to rematch (Y/N)?\n>>>";
                        cin >> choice;
                    }
                    if (choice == 'Y' || choice == 'y') {
                        system("cls");
                        game->Reset();
                        flag = true;
                    } 
                    else if (choice == 'N' || choice == 'n') {
                        rematchCPU = false;
                        char menuPrompt = ' ';
                        cout << "Do you want to go back to the main menu (Y/N)?\n>>>";
                        cin >> menuPrompt;
                        while (menuPrompt!= 'Y' && menuPrompt!= 'y' && menuPrompt!= 'N' && menuPrompt!= 'n'){
                            cout << "\033[1;31mERROR: Invalid Selection!\033[0m\n";
                            cout << "Do you want to go back to the main menu (Y/N)?\n>>>";
                            cin >> menuPrompt;
                        }
                        if (menuPrompt == 'Y' || menuPrompt == 'y') {
                            system("cls");
                            playAgain = true;
                            rematchCPU = false;
                        } 
                        else if (menuPrompt == 'N' || menuPrompt == 'n') {
                            rematchCPU = false;
                            system("cls");
                            for (char c : Art::asciiOutro()) {
                                if (isspace(c)) {
                                    cout << flush << c;
                                } 
                                else {
                                    cout << flush << c;
                                    this_thread::sleep_for(chrono::microseconds(1000));
                                }
                            }
                            this_thread::sleep_for(chrono::seconds(1));
                            exit(0);
                        }
                    }
                } while (rematchCPU);
                break;
            }
            
            //CASE 2 (MULTIPLAYER)
            case 2: {
                bool rematchPlayer = true;
                do {
                    while (flag) {
                        //player I turn
                        game->PlayerTurn(player);
                        //check if won
                        fin = game->CheckWin();
                        if (fin!= "") {
                            goto point2;
                        }

                        game->PlayerTurn(player2);
                        fin = game->CheckWin();

                        point2:
                        //player 1 wins condition
                        if (fin == "Player I") {
                            this_thread::sleep_for(chrono::seconds(2));
                            system("cls");
                            for (char c : Art::asciiPlayerI()) {
                                if (isspace(c)) {
                                    cout << flush << c;
                                } 
                                else {
                                    cout << flush << c;
                                    this_thread::sleep_for(chrono::microseconds(1000));
                                }
                            }
                            this_thread::sleep_for(chrono::seconds(1));
                            flag = false;
                        }

                        //player 2 wins
                        else if (fin == "Player II") {
                            this_thread::sleep_for(chrono::seconds(2));
                            system("cls");
                            for (char c : Art::asciiPlayerII()) {
                                if (isspace(c)) {
                                    cout << flush << c;
                                } 
                                else {
                                    cout << flush << c;
                                    this_thread::sleep_for(chrono::microseconds(1000));
                                }
                            }
                            this_thread::sleep_for(chrono::seconds(1));
                            flag = false;
                        }

                        //draw
                        else if (fin == "Draw") {
                            this_thread::sleep_for(chrono::seconds(2));
                            system("cls");
                            for (char c : Art::asciiDraw()) {
                                if (isspace(c)) {
                                    cout << flush << c;
                                } 
                                else {
                                    cout << flush << c;
                                    this_thread::sleep_for(chrono::microseconds(1000));
                                }
                            }
                            this_thread::sleep_for(chrono::seconds(1));
                            flag = false;
                        }
                    }
                    
                    //rematch
                    char choice = ' ';
                    this_thread::sleep_for(chrono::seconds(1));
                    system("cls");
                    cout << Art::orangeLetter();
                    for (char c : Art::asciiRematch()) {
                        if (isspace(c)) {
                            cout << flush << c;
                        } 
                        else {
                            cout << flush << c;
                            this_thread::sleep_for(chrono::microseconds(1000));
                        }
                    }
                    cout << Art::resetLetter();
                    cout << "Do you want to rematch (Y/N)?\n>>>";
                    cin >> choice;
                    while (choice!= 'Y' && choice!= 'y' && choice!= 'N' && choice!= 'n'){
                        cout << "\033[1;31mERROR: Invalid Selection!\033[0m\n";
                        cout << "Do you want to rematch (Y/N)?\n>>>";
                        cin >> choice;
                    }
                    if (choice == 'Y' || choice == 'y') {
                        system("cls");
                        game->Reset();
                        flag = true;
                    } 
                    else if (choice == 'N' || choice == 'n') {
                        rematchPlayer = false;
                        char menuPrompt = ' ';
                        cout << "Do you want to go back to the main menu (Y/N)?\n>>>";
                        cin >> menuPrompt;
                        while (menuPrompt!= 'Y' && menuPrompt!= 'y' && menuPrompt!= 'N' && menuPrompt!= 'n'){
                            cout << "\033[1;31mERROR: Invalid Selection!\033[0m\n";
                            cout << "Do you want to go back to the main menu (Y/N)?\n>>>";
                            cin >> menuPrompt;
                        }
                        if (menuPrompt == 'Y' || menuPrompt == 'y') {
                            system("cls");
                            playAgain = true;
                            rematchPlayer = false;
                        } 
                        else if (menuPrompt == 'N' || menuPrompt == 'n') {
                            rematchPlayer = false;
                            system("cls");
                            for (char c : Art::asciiOutro()) {
                                if (isspace(c)) {
                                    cout << flush << c;
                                } 
                                else {
                                    cout << flush << c;
                                    this_thread::sleep_for(chrono::microseconds(1000));
                                }
                            }
                            this_thread::sleep_for(chrono::seconds(1));
                            exit(0);
                        }
                    }
                } while (rematchPlayer);
                break;
            }

            //CASE 3 (GAME RULES)
            case 3: {
                game->PrintRules();
                cout << "PRESS [ENTER] TO GO BACK TO THE MENU\n>>>";
                cin.ignore();
                system("cls");
                break;
            }

            //CASE 4 (EXIT PROGRAM)
            case 4: {
                system("cls");
                for (char c : Art::asciiOutro()) {
                    if (isspace(c)) {
                        cout << flush << c;
                    }
                    else {
                        cout << flush << c;
                        this_thread::sleep_for(chrono::microseconds(1000));
                    }
                }
                this_thread::sleep_for(chrono::milliseconds(1000)); 
                exit(0);
            }
        }

    }
}