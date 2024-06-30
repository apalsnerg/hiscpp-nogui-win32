#include <iostream>
#include <string>
#include <algorithm>
#include "player.h"
#include "util.h"
using namespace std;

Player::Player(string playerName, int playerBalance) {
    name = playerName;
    balance = playerBalance;
}

void Player::promptName() {
    string newName;
    cout << "Enter your name: " << endl << ">> ";
    getline(cin, newName);
    /* If the user does not enter a name or enters only spaces, set the name to "John Doe" */
    if (newName == "" || isOnlySpaces(newName)) {
        newName = "John Doe";
    }
    name = newName;
}

void Player::setName(string newName) {
    name = newName;
}

string Player::getName() {
    return name;
}

void Player::setBalance(int newBalance) {
    balance = newBalance;
}

void Player::increaseBalance(int incAmnt) {
    balance += incAmnt;
}

void Player::reduceBalance(int rdcAmnt) {
    balance -= rdcAmnt;
}

void Player::printName() {
    cout << "Your name is " << name << "." << "\n";
}

int Player::getBalance() {
    return balance;
}
