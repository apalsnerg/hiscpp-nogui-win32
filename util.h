#include <vector>
#include <string>

using namespace std;

/** Splits a string into a vector of its whitespace-separated words */
vector<string> strSplit(string inputStr);

/** Checks if an integer exists in a vector */
bool trueFindInt(int needle, vector<int> haystack);

/** Searches a string vector for a string */
bool trueFindStr(string needle, vector<string> haystack);

/** Checks if a string only contains spaces */
bool isOnlySpaces(string str);
