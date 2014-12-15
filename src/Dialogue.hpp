#include <vector>
#include <string>
#include <iostream>
#include "libtcod.hpp"
#include <stdio.h>
#include <stdlib.h>
#include "Character.hpp"
#include "Config.hpp"

using namespace std;

class Expression
{
public:
    Expression()
    {
        character = "";
        variable = "";
        value = -1;
    }

    Expression(string character, string variable, int value);

    string character;
    string variable;
    int    value;
};

class PlayerReply
{
public:
    PlayerReply(string text, short nextLine, Expression condition, Expression action);

    PlayerReply(string text, short nextLine);

    string text;
    short nextLine;

    Expression condition;
    Expression action;
};

class Dialogue
{
public:
    Dialogue();

    unsigned int currentLine, replyNumber;

    void run(TCODConsole *osc, TCODImage *bg, vector<Character>& characters);

    void addReply(int pos, string text, int linkTo);
    void addReply(int pos, string text, int linkTo,
                  Expression condition, Expression action);

    void addNpcLine(string text);

    vector<string> lineText;
    vector< vector<PlayerReply> > lineReplies;
};
