#include <iostream>
#include <string>
#include <vector>
using namespace std;


string isInDozen(int playingField[3][4][3], int num, int rolled) {
    cout << playingField[1][1][2] << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (playingField[num][i][j] == rolled) {
                return "win";
            }
        }
    }
    return "lose";
}


int main () {
    int playingField[3][4][3] = {
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

    int rolled = 14;
    
    cout << isInDozen(playingField, 2, rolled) << endl;



    return 1;
}
