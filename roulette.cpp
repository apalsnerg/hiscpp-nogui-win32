#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>
#include <string>
#include <tgmath.h>
#include <windows.h>
#include "player.h"
#include "roulette.h"
#include "util.h"
using namespace std;

/**
 * Constructor
 * 
 * @param name The name of the player that is co-generated
 */
Roulette::Roulette(string name)  {
    if (name != "" || name.size() > 0) {
        player = Player(name);
    } else {
        player = Player();
    }
}

/**
 * The Roulette board, including dozen divisions
 */
int Roulette::playingField[3][4][3] =
{
    {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12}
    },
    {
        {13, 14, 15},
        {16, 17, 18},
        {19, 20, 21},
        {22, 23, 24}
    },
    {
        {25, 26, 27},
        {28, 29, 30},
        {31, 32, 33},
        {34, 35, 36}
    }
};

/**
 * The Roulette board as just the rows
 */
int Roulette::playingFieldLines[12][3] = 
{
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9},
    {10, 11, 12},
    {13, 14, 15},
    {16, 17, 18},
    {19, 20, 21},
    {22, 23, 24},
    {25, 26, 27},
    {28, 29, 30},
    {31, 32, 33},
    {34, 35, 36}
};

/*
 * The numbers that are red and black, respectively
 */
vector<int> Roulette::redNums = {1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36};
vector<int> Roulette::blackNums = {2, 4, 6, 8, 10, 11, 13, 15, 17, 20, 22, 24, 26, 28, 29, 31, 33, 35};

void Roulette::setBet() {
    cout << "How much would you like to bet?" << "\n" << ">> ";
    try {
        cin >> bet;
    } catch (const invalid_argument& e) {
        cout << "You must enter a number." << "\n";
    }
}

int Roulette::getBet() {
    return bet;
}

/**
 * Allows the player to override the bet protocol, meaning they can make any bet
 */
void Roulette::betRelease() {
    bOverrideBetProtocol = true;
}

/**
 * Re-enables the bet restriction protocol, meaning they are restricted to the allowedBets.
 */
void Roulette::betShackle() {
    bOverrideBetProtocol = false;
}

/**
 * Spins the wheel (generates a random number between 0 and 36)
 */
int Roulette::spin() {
    srand(time(NULL));
    return rand() % 37; // 0 to 36
}

/**
 * Getter for the player
 */
Player Roulette::getPlayer() {
    return player;
}

/**
 * Setter for the minimum bet
 */
void Roulette::setMinBet(int newMinBet) {
    minBet = newMinBet;
}

/**
 * Setter for the maximum bet
 */
void Roulette::setMaxBet(int newMaxBet) {
    maxBet = newMaxBet;
}

/**
 * Prompts the user to give their name (necessary for use in main)
 */
void Roulette::configPlayerName() {
    player.promptName();
}

void Roulette::configuration() {
    cout << "Would you like to reset your name? (Y/n)" << endl << ">> ";
    string nameRes;
    getline(cin, nameRes);
    if (nameRes[0] == 'Y' || nameRes[0] == 'y') {
        player.promptName();
    }
    
    cout << "Would you like to update your balance? (Y/n)" << "\n" << ">> ";
    string balRes;
    getline(cin, balRes);
    if (balRes[0] == 'Y' || balRes[0] == 'y') {
        cout << "What would you like to set your balance to?" << "\n" << ">> ";
        string newBalance;
        getline(cin, newBalance);
        try {
            int i = stoi(newBalance);
            player.setBalance(i);
        } catch (const invalid_argument& e) {
            cout << "Not a valid number. Skipping." << "\n";
        } catch (const out_of_range& e) {
            cout << "Too large! Skipping." << "\n";
        }
    }
    string betResOvr;
    string betRes;
    if (bOverrideBetProtocol) {
        cout << "NOTE: Your bet settings have been reset." << "\n";
        betShackle();
    }
    cout << "The allowed bets are 100kr, 350kr, and 500kr." << "\n";
    cout << "Would you like to configure this? (Y/n)" << "\n" << ">> ";
    getline(cin, betRes);
    if (betRes[0] == 'Y' || betRes[0] == 'y') {
        betRelease();
        string configResMax;
        cout << "Would you like to configure a maximum bet? It cannot be lower than 1. (Y/n)" << "\n" << ">> ";
        getline(cin, configResMax);
        if (configResMax[0] == 'Y' || configResMax[0] == 'y') {
            cout << "Please enter a maximum bet." << "\n" << ">> ";
            string newMaxBetStr;
            try {
                getline(cin, newMaxBetStr);
                int newMaxBet = stoi(newMaxBetStr);
                if (newMaxBet < 1) {
                    newMaxBet = 1;
                }
                setMaxBet(newMaxBet);
            } catch (const invalid_argument& e) {
                cout << "Not a valid number. Defaulting to no maximum." << "\n";
            } catch (const out_of_range& e) {
                cout << "Not a valid number. Defaulting to no maximum." << "\n";
            }
        }
        string configResMin;
        cout << "Would you like to configure a minimum bet? "
            << "It cannot be lower than 1 or higher than the maximum. (Y/n)" << endl << ">> ";
        getline(cin, configResMin);
        if (configResMin[0] == 'Y' || configResMin[0] == 'y') {
            cout << "Please enter a minimum bet." << "\n" << ">> ";
            string newMinBetStr;
            try {
                getline(cin, newMinBetStr);
                int newMinBet = stoi(newMinBetStr);
                if (newMinBet < 1 || newMinBet > maxBet || maxBet == 1) {
                    newMinBet = 1;
                }
                setMinBet(newMinBet);
            } catch (const invalid_argument& e) {
                cout << "Not a valid number. Defaulting to 100." << "\n";
            } catch (const out_of_range& e) {
                cout << "Not a valid number. Defaulting to 100." << "\n";
            }
        }
    }
    cout << "Configuration complete." << "\n";
}

void Roulette::printRules() {
    cout << "This might be a lot to take in, so you might have to read it twice. Let's go!" << "\n";
    cout << "The Roulette table is divided into three dozens of four lines of three numbers, like this: " << "\n\n";
    showPlayingField();
    cout << "The numbers on the side designate the [dozen] and the lines,"
         << "while the numbers at the bottom signify the |columns|" << "\n";
    if (bOverrideBetProtocol) {
        cout << "You will be able to place a bet between " << minBet << " and " << maxBet << "." << "\n";
    } else {
        cout << "You will be able to bet 100kr, 350kr, and 500kr." << "\n";
    }
    cout << "On the Roulette table, odd numbers are black, and even numbers are red." << "\n";
    cout << "You will be able to enter a variety of commands depending on what you want to do. Here they are:" << "\n";
    
    printComs();
}

void Roulette::printComs() {
    cout << "Enter 'help' at any time to show this list" << "\n";
    cout << "Enter 'quit' at any time to end the game." << "\n";
    cout << "Enter 'bet' to see the possible bets, or followed by a number to set your bet. Default 1kr. " << "\n";
    cout << "Enter 'balance' to see your account balance." << "\n";
    cout << "Enter 'settings' to configure the game." << "\n";
    cout << "Enter 'field' to see the playing field." << "\n";
    cout << "-------------------------------" << "\n";
    cout << "The following are spinning commands. When you enter any of these, the wheel with spin." << "\n";
    cout << "Enter 'single' followed by a number to bet on that number. A win on single returns 35x your bet." << "\n";
    cout << "Enter 'split' followed by the lower of the two numbers you want to bet on. "
         << "A win on split returns 17x your bet." << "\n";
    cout << "Enter 'street' followed by the number of the row to bet on those numbers. "
         << "A win on street returns 11x your bet." << "\n";
    cout << "Enter 'corner' followed by the number at the top left of the square you want to bet on. "
         << "A win on corner returns 8x your bet." << "\n";
    cout << "Enter 'line' followed by the number of the first row you want to bet on. "
         << "A win on line returns 5x your bet." << "\n";
    cout << "Enter 'dozen' followed by the number of the dozen you want to bet on. "
         << "A win on dozen returns 2x your bet." << "\n";
    cout << "Enter 'column' followed by the number of the column you want to bet on. "
         << "A win on column returns 2x your bet." << "\n";
    cout << "Enter 'colour' followed by the colour you want to bet on. A win on colour returns 1x your bet." << "\n";
    cout << "Enter 'high' to bet the rolled number will be larger than 18. A win on high returns 1x your bet." << "\n";
    cout << "Enter 'low' to bet the rolled number will be less than 18. A win on low returns 1x your bet." << "\n";
    cout << "Enter 'even' to bet the rolled number will be even. A win on even returns 1x your bet." << "\n";
    cout << "Enter 'odd' to bet the rolled number will be odd. A win on odd returns 1x your bet." << "\n";
    cout << endl;
}

/**
 * Prints the playing field of the Roulette table, prettily
 * Also has the number of the rows, dozens, and columns on the right and below
 */
void Roulette::showPlayingField() {
    int lineCounter = 0;
    int dozenCounter = 1;
    cout << "+--------------+ [1]" << "\n";
    for (int i = 0; i < 3; i++) {
        dozenCounter += 1;
        for (int j = 0; j < 4; j++) {
            lineCounter += 1;
            for (int k = 0; k < 3; k++) {
                int curNum = playingField[i][j][k];
                cout << "| ";
                if (curNum < 10) {
                    cout << " ";
                }
                cout << curNum;
                cout << " ";
            }
            cout << "| " << lineCounter << endl;
        }
        if (dozenCounter < 4) {
            cout << "+--------------+ " << "[" << dozenCounter << "]" "\n";
        } else {
            cout << "+--------------+ " << "\n";
            cout << "|  1 |  2 |  3 |" << "\n\n";
        }
    }
}

/**
 * Prints some intro text with the rules
 */
void Roulette::intro() {
    cout << "Welcome to Roulette!" << "\n";
    cout << "You will be playing with custom rules based on the European standard." << "\n";
    cout << "There will be 37 numbers in total, ranging from 0-36." << "\n";
    cout << "0 can only be used as a direct bet." << "\n";
    cout << "Black numbers are even, and red numbers are odd." << "\n";
    cout << "Before we get started, what can I call you?" << endl;
}

/**
 * Evaluates the numbers the user bet on and the spin and returns how much they won or lost
 * 
 * @param userInput the string containing the user's command
 * @returns a vector with the result of the bet and how much the player won or lost.
 */
vector<string> Roulette::evalSpin(string userInput) {
    /* A vector of strings that are the constituent words of the line the user inputted */
    vector<string> usrInptVctr = strSplit(userInput);
    /* The user must place a bet at the start of the game */
    if (bet == 0) {
        cout << "You need to set a bet first!" << "\n";
        return {"none", "0"};
    }
    // If we expect a qualifier after the type selection and don't receive one, e.g. with single or colour
    if (usrInptVctr.size() < 2 && usrInptVctr[0] != "high" && usrInptVctr[0] != "low"
                               && usrInptVctr[0] != "even" && usrInptVctr[0] != "odd") {
        if ((usrInptVctr[0] == "colour" || usrInptVctr[0] == "color")) {
            cout << "You need to specify a colour!" << "\n";
            return {"none", "0"};
        } else {
            cout << "You need to specify a number!" << "\n";
            return {"none", "0"};
        }
    }

    /*
     * Below we evaluate the user's selected bet type.
     * Could be done with a switch, but switching on a string is complicated.
     * Methods for checking whether the bet was successful are used where necessary;
     * elsewhere just some basic logic is used.
     * 
     * On a win, "win" is return with the bet multiplied by the win factor.
     * On a loss, "lose" is returned with just the bet.
     * This way, we can evaluate whether the user's balance should be increased or decreased (using the first value),
     * and how much it should be done so by (the second value) where we return in our game loop.
     */
    int betNum;
    if (
        usrInptVctr[0] != "colour" && usrInptVctr[0] != "color" && usrInptVctr[0] != "high"
        && usrInptVctr[0] != "low" && usrInptVctr[0] != "even" && usrInptVctr[0] != "odd" ) {
        try {
            /* If we expect a number for the bet and don't receive one, throw */
            betNum = stoi(usrInptVctr[1]);
        } catch (invalid_argument &e) {
            cout << "You need to specify a number!" << "\n";
            return {"none", "0"};
        } catch (out_of_range &e) {
            cout << "That number is too vast!" << "\n";
            return {"none", "0"};
        }
        if (betNum > 36 || betNum < 1) {
            cout << "Not a valid number!" << "\n";
            return {"none", "0"};
        }
    }

    
    rolledNumber = spin();
    cout << "Spinning the wheel..." << "\n";
    /* Simulates physical spinning and makes sure the seed is not the same for each spin */
    Sleep(3000);

    /*
     * Before validating every spin, we make sure to validate the number the user entered
     * to make sure they don't e.g. try to bet on the 120th dozen or the -53rd column
     */
    if (usrInptVctr[0] == "single") {
        if (betNum > 36 || betNum < 1) {
            cout << "No such number!" << "\n";
            return {"none", "0"};
        }
        if (rolledNumber == betNum) {
            return {"win", to_string(bet * 35)};
        }
        return {"lose", to_string(bet)};

    } else if (usrInptVctr[0] == "split") {
        /* The user has to bet on at least 0 and a split bet on the last number doesn't make sense */
        if (betNum > 36 || betNum < 1) {
            cout << "This bet is not valid for that number!" << "\n";
            return {"none", "0"};
        }
        if (rolledNumber == betNum || rolledNumber == betNum + 1) {
            return {"win", to_string(bet * 17)};
        }
        return{"lose", to_string(bet)};

    } else if (usrInptVctr[0] == "street") {
        /* There are only 12 rows of numbers */
        if (betNum > 12 || betNum < 1) {
            cout << "No such street!" << "\n";
            return {"none", "0"};
        }
        if (isInStreet(betNum, rolledNumber)) {
            return {"win", to_string(bet * 11)};
        }
        return {"lose", to_string(bet)};

    } else if (usrInptVctr[0] == "corner") {
        /* The player must bet on at least 1 and 32 is the last number we can form a square from */
        if (betNum > 32 || betNum < 1 || betNum % 3 == 0) {
            cout << "No valid corner bets for this number!" << "\n";
            return {"none", "0"};
        }
        if (isInCorner(betNum, rolledNumber)) {
            return {"win", to_string(bet * 8)};
        }
        return {"lose", to_string(bet)};

    } else if (usrInptVctr[0] == "line") {
        /* The user must bet on at least the first line and can't line bet on the last row */
        if (betNum < 1 || betNum > 11) {
            cout << "No valid line bets for this number!" << "\n";
            return {"none", "0"};
        }
        if (isInLine(betNum, rolledNumber)) {
            return {"win", to_string(bet * 5)};
        }
        return {"lose", to_string(bet)};

    } else if (usrInptVctr[0] == "dozen") {
        /* The dozens are labeled 1, 2, and 3 and we can only process those */
        if (!trueFindInt(betNum, {1, 2, 3})) {
            cout << "You must choose between dozens 1, 2, and 3!" << "\n";
            return {"none", "0"};
        }
        if (isInDozen(betNum, rolledNumber)) { 
            return {"win", to_string(bet * 2)};
        }
        return {"lose", to_string(bet)};
            

    } else if (usrInptVctr[0] == "column") {
        /* There only exists a first, second, and third column */
        if (!trueFindInt(betNum, {1, 2, 3})) {
            cout << "You must pick between columns 1, 2, and 3!" << "\n";
            return {"none", "0"};
        }
        if (isInColumn(betNum, rolledNumber)) {
            return {"win", to_string(bet * 2)};
        }
        return {"lose", to_string(bet)};

    } else if (usrInptVctr[0] == "colour" || usrInptVctr[0] == "color") {
        string betClr = usrInptVctr[1];
        if (isRedOrBlack(betClr, rolledNumber)) {
            return {"win", to_string(bet)};
        }
        return {"lose", to_string(bet)};

    } else if (usrInptVctr[0] == "high" || usrInptVctr[0] == "low") {
        string highOrLow = usrInptVctr[0];
        if (isHighOrLow(highOrLow, rolledNumber)) {
            return {"win", to_string(bet)};
        }
        return {"lose", to_string(bet)};

    } else if (usrInptVctr[0] == "odd" || usrInptVctr[0] == "even") {
        string oddOrEven = usrInptVctr[0];
        if (isOddOrEven(oddOrEven, rolledNumber)) {
            return {"win", to_string(bet)};
        }
       return {"lose", to_string(bet)};
    }

    return {"none", 0};
}

/**
 * One of the core input validators.
 * This processes the user input and returns the appropriate response to the loop depending on the content.
 * 
 * @param userInput The user's input
 * 
 * @returns "none" if the string was rejected or the desired effect is to do nothing in the game,
 *          "quit" if the user wants to quit the game, and "ok" if the validation passes as a valid spin string
 */
string Roulette::evalInput(string userInput) {
    /* A vector of allowed bets to check the user's input against if they didn't issue a normal command */
    vector<string> validBets = {
        "single",
        "split",
        "street",
        "corner",
        "line",
        "dozen",
        "column",
        "colour",
        "color",
        "high",
        "low",
        "even",
        "odd"
    };

    /* Split the user's input into a vector containing the constituent words */
    vector<string> usrInptVctr = strSplit(userInput);

    /* 
     * In this section, we return "none" to ensure that nothing happens in the game if the user doesn't input a valid bet or quit
     * We return "quit" if the user issues the quit command to tell the loop to end itself
     * And if the user inputs a valid bet command, we return "ok", continuing the game
     */
    if (usrInptVctr[0] == "quit" || usrInptVctr[0] == "exit") {
        return "quit";
    } else if (usrInptVctr[0] == "balance") {
        cout << "Your balance is " << player.getBalance() << "kr." << "\n";
        return "none";
    } else if (usrInptVctr[0] == "help") {
        printComs();
        return "none";
    } else if (usrInptVctr[0] == "bet") {
        if (usrInptVctr.size() != 2) {
            if (bOverrideBetProtocol) {
                cout << "The minimum bet is " << minBet << "kr and the maximum bet is " << maxBet << "kr." << "\n";
            } else {
                cout << "The allowed bets are: " << allowedBets[0] << "kr, " << allowedBets[1] << "kr, and " << allowedBets[2] << "kr." << "\n";
            }
            return "none";
        }
        int usrBet;
        string usrBetStr = usrInptVctr[1];
        try {
            usrBet = stoi(usrBetStr);
        } catch (const invalid_argument &e) {
            cout << "Your bet must be a number." << "\n";
            return "none";
        } catch (const out_of_range &e) {
            cout << "Your bet must be a number." << "\n";
            return "none";
        }

        /* Check if the user has enough money to make the bet */
        if (usrBet > player.getBalance()) {
            cout << "You don't have enough money to make that bet." << "\n";
            return "none";
        }
        /* Validate that the user didn't bet under the minimum */
        else if (bOverrideBetProtocol && stoi(usrInptVctr[1]) < 1) {
            cout << "Your bet must be at least 1kr." << "\n";
            return "none";
        }
        /* Validate that the user didn't bet a non-allowed number if the bets are shackled*/
        else if (!trueFindInt(stoi(usrInptVctr[1]), allowedBets)) {
            cout << "Your bet must be either " << allowedBets[0] << "kr, " << allowedBets[1] << "kr, or " << allowedBets[2] << "kr." << "\n";
            return "none";
        }
        bet = stoi(usrInptVctr[1]);
        cout << "You have placed a bet of " << bet << "kr." << "\n";
        return "none";
    } else if (usrInptVctr[0] == "settings") {
        configuration();
        return "none";
    } else if (usrInptVctr[0] == "field") {
        showPlayingField();
        return "none";
    } else if (usrInptVctr[0] == "name") {
        player.printName();
        return "none";
    }  else if (!trueFindStr(usrInptVctr[0], validBets)) {
        cout << '"' << usrInptVctr[0] << '"' << " is not a valid command. Please try again." << endl;
        return "none";
    }
    return "ok";
}

/**
 * Checks if a number is in the given dozen
 * 
 * @param num The dozen to check
 * @param rolled The number to check for
 * @return Whether the number is in the dozen
 */
bool Roulette::isInDozen(int num, int rolled) {
    num = num - 1;
    for (int i = 0; i < 4; i++) { // For every row
        for (int j = 0; j < 3; j++) { // For every number
            if (playingField[num][i][j] == rolled) {
                return true;
            }
        }
    }
    return false;
}

/**
 * Checks if a number is in the given street, i.e. in the row
 * 
 * @param num The row to check (which we reduce by 1 since we count from 0)
 * @param rolled The number to check for
 * @return Whether the number is in the street
 */
bool Roulette::isInStreet(int num, int rolled) {
    for (int i = 0; i < 3; i++) {
        if (playingFieldLines[num - 1][i] == rolled) {
            return true;
        } 
    }
    return false;
}
/**
 * Checks if a number is in a line, i.e. in a row or the following row.
 * Theoretically, this could be done way more easily by implementing a second array that stores the numbers without the dozens.
 * However, this is cooler.
 * 
 * @param num The first row to check
 * @param rolled The number to check for
 * @return true if the number is in the given street or the next, else false
 */
bool Roulette::isInLine(int num, int rolled) {
    for (int i = 0; i < 3; i++) {
        if (playingFieldLines[num - 1][i] == rolled) {
            return true;
        }
        if (playingFieldLines[num][i] == rolled) {
            return true;
        }
    }
    return false;
}

/**
 * Checks if the given number is in the specified column of the playing field.
 *
 * @param num The number to check for.
 * @param rolled The number that was rolled.
 * @return true if the number is in the specified column, false otherwise.
 */
bool Roulette::isInColumn(int num, int rolled) {
    for (int i = 0; i < 3; i++) { // For every dozen
        for (int j = 0; j < 4; j++) { // For every row
            if (playingField[i][j][num - 1] == rolled) { // If the number is in the chosen column (user will enter 1, 2, or 3 so we need to subtract 1)
                return true;
            }
        }
    }
    return false;
}

bool Roulette::isHighOrLow(string highOrLow, int rolled) {
    string rolledLevel = "high";
    if (rolled < 19) {
        rolledLevel = "low";
    }
    return (rolledLevel == highOrLow);
}

/**
 * Since every corner can be simplified to n, n+1, n+3, n+4, we don't need to check against the playingField, just do some arithmetic.
 * Visually, using 2 as our number:
 * {1, [2, 3]}
 * {4, [5, 6]}
 * {7, 8, 9}
 * The corner includes 3 (2 + 1), 5 (2 + 3), and 6 (2 + 4), Q.E.D.
 *
 * @param num the number to the top left of the corner
 * @param rolled the number generated randomly
 * 
 * @returns bool whether the rolled number is in the chosen corner
 */
bool Roulette::isInCorner(int num, int rolled) {
    vector<int> checkNums = {num, num+1, num+3, num+4};
    if (trueFindInt(rolled, checkNums)) {
        return true;
    }
    return false;
}

/**
 * Checks if the user guessed right about the number being odd or even
 * 
 * @param choice The user's guess
 * @param rolled The number that was rolled
 * 
 * @returns true if the user guessed right, else false
 */
bool Roulette::isOddOrEven(string choice, int rolled) {
    if (choice == "odd") {
        return (rolled % 2 == 1);
    } else if (choice == "even") {
        return (rolled % 2 == 0);
    }
    return false;
}

/**
 * Checks if the user guessed right about the number being red or black
 * 
 * @param choice The user's guess
 * @param rolled The number that was rolled
 * 
 * @returns true if the user guessed right, else false
 */
bool Roulette::isRedOrBlack(string choice, int rolled) {
    if (choice == "red") {
        return trueFindInt(rolled, redNums);
    } else if (choice == "black") {
        return trueFindInt(rolled, blackNums);
    }
    return false;
}

/**
 * The main loop for the game.
 * Keeps going until the user enters the "quit" command.
 */
int Roulette::gameLoop() {
    bool playing = true;
    while (playing) {
        cout << ">> ";
        string action = "none";
        string userInput;
        getline(cin, userInput);
        /* If the user enters an empty line, do nothing */
        if (userInput != "") {
            action = evalInput(userInput);
        }
        /*  If the user quits, exit the loop */
        if (action == "quit") {
            playing = false;
        /* If the user inputs a nonsense command, do nothing */
        } else if (action == "none") {
            continue;
        /* 
         * If the input evaluation passes,
         * evaluate the spin the user desired
         */
        } else {
            /*
             * First value is "win", "lose", or "none" depending on whether
             * the bet was valid and succeded/failed, second value is the
             *  payout, loss, or 0 if "none"
             */
            vector<string> result = evalSpin(userInput);
            if (result[0] == "none") {
                continue;
            }
            cout << "The number rolled was: " << rolledNumber << "\n";
            if (result[0] == "win") {
                cout << "Hooray, " << player.getName() << "! You won! You earned " << result[1] << "kr!" << "\n";
                player.increaseBalance(stoi(result[1]));
                totalPayouts += stoi(result[1]);
            } else if (result[0] == "lose") {
                cout << "Sorry, " << player.getName() << ", you lose! You lost your bet of " << result[1] << "kr." << "\n";
                player.reduceBalance(stoi(result[1]));
                int tmp = stoi(result[1]);
                totalLosses += tmp;
            }
            cout << "Your new balance is: " << player.getBalance() << "kr." << "\n";
            cout << "Your total payout for this session is: "
                 << totalPayouts << "kr." << "\n";
            cout << "Your total losses for this session are: "
                 << totalLosses << "kr." << "\n\n";
            if (player.getBalance() == 0) {
                cout << "You're out of money! Game over!" << "\n";
                playing = false;
            }
        }
    }
    cout << "Bye bye!" << endl;
    return 1;
}
