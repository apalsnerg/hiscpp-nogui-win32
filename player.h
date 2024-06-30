#include <iostream>
#include <string>
using namespace std;

#pragma once
/**
 * Represents a player in the Roulette game
 */
class Player {
    public:
        /* Constructor */
        Player(string name = "John Doe", int balance = 1000);

        void promptName();

        void setName(string);


        void setBalance(int);

        void increaseBalance(int);

        void reduceBalance(int);

        void printName();

        string getName();

        int getBalance();
    private:
        int balance;
        string name;
};
