#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include "Character.hpp"
#include "Level.hpp"

using namespace std;

class Parser
{
public:
    vector<string> lines;

    bool    loadFile(string fileName);

    string  copyFromCharToEnd(char character, string str);

    string  copyFromPosToEnd(int pos, string str);

    string  copyFromStartToChar(char character, string str);

    string  copyFromCharToChar(char char1, char char2, string str);

    void    parseDialogue(Dialogue &dialogue, vector<Character> &characters);

    void    parseCharacters(vector<Character> &characters);

    void    parseLevel(Level &level, vector<Character> &characters);
};
