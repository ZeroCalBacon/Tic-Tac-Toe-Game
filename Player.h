#ifndef PLAYER_H
#define PLAYER_H

#include<string>
#include <thread>
using namespace std;

class Player {
    private:
    string name;

    public:
    //constructor
    Player(string n) : name(n) {}

    //PlayerName function gets name
    string PlayerName() const {
        return name;
    }
};

#endif // PLAYER_H