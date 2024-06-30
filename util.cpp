#include <iostream>
#include <vector>
#include <string>
#include "util.h"

using namespace std;

/**
 * Splits a string into a vector of individual words
 * TODO: Add custom delimiter(s)
 * 
 * @param strToSplit The string to split up
 * 
 * @returns The vector of individual words
 */
vector<string> strSplit(string strToSplit) {
    vector<string> strToSplitArray; // Vector to contain the individual words
    string substr; // Temp string to contain the individual words during processing
    strToSplit += ' '; // Since we split on space, make sure there always is one at the end of the word
    for (int i = 0; i < strToSplit.length(); i++) {
        if (strToSplit[i] == ' ') {
            strToSplitArray.push_back(substr);
            substr = "";
        } else {
            substr += strToSplit[i];
        }
    }
    return strToSplitArray;
}

/** 
 * Checks if an integer exists is in an integer vector
 * 
 * @param needle The integer to search for
 * @param haystack The vector to search through
 * 
 * @return true if the integer exists in the vector, else false
 */
bool trueFindInt(int needle, vector<int> haystack) {
    for (int i = 0; i < haystack.size(); i++) {
        if (haystack[i] == needle) {
            return true;
        }
    }
    return false;
}

/** 
 * Checks if a string exists is in a string vector
 * 
 * @param needle The integer to search for
 * @param haystack The vector to search through
 * 
 * @return true if the integer exists in the vector, else false
 */
bool trueFindStr(string needle, vector<string> haystack) {
    for (int i = 0; i < haystack.size(); i++) {
        if (haystack[i] == needle) {
            return true;
        }
    }
    return false;
}


/**
 * Checks if a string only contains space characters
 * TODO: expand to all whitespaces
 * 
 * @param str The string to check
 * 
 * @return true if the string only contains spaces, else false
 */
bool isOnlySpaces(string str) {
    for (int i = 0; i < str.size(); i++) {
        if (str[i] != ' ') {
            return false;
        }
    }
    return true;
}
