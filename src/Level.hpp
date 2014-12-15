#ifndef LEVEL_H
#define LEVEL_H
#include <string>
#include <vector>
#include <map>
#include "Config.hpp"
#include "Dialogue.hpp"
#include "Sound.hpp"

using namespace std;

class Statement
{
public:
    Statement(string text, int nextLine, string type)
    {
        this->text = text;
        this->nextLine = nextLine;
        this->type = type;
    }
    string text;
    int nextLine;
    string type;
};


class Level
{
    public:
        Level();
        unsigned int currentLine;

        void run(TCODImage *bg, Sound& sound, vector<Character>& characters);

        void addStatement(string text, int nextLine, string type);

        void addDialogue(string fileName, Dialogue dialogueName);

        vector<Statement> statements;

        map<string, Dialogue> dialogues;
};

#endif // LEVEL_H
