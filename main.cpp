#include <iostream>
#include <string>
#include "roulette.h"
#include "player.h"
using namespace std;

int main() {
    Roulette roulette;
    bool playing = true;
    roulette.intro();
    roulette.configPlayerName();
    Player player = roulette.getPlayer();
    cout << "Welcome, " << player.getName() << "!" << "\n";
    cout << "Your starting balance is " << player.getBalance() << "kr." << "\n" << "The allowed bets are 100kr, 350kr, and 500kr." << "\n";
    cout << "Would you like to configure these settings? (Y/n)" << "\n" << ">> ";
    string answer;
    getline(cin, answer);
    if (answer[0] == 'Y' || answer[0] == 'y') {
        roulette.configuration();
    }

    cout << "First, let me explain how this program works to you." << "\n\n";
    roulette.printRules();

    cout << "Great! Now we're ready to begin." << endl;
    cout << "Start by setting your first bet. Then, you can choose what you want to bet on." << endl;

    roulette.gameLoop();
    return 1;
}
