#ifndef CHARACTER_H
#define CHARACTER_H
#include <map>
#include <string>

using namespace std;

class Character
{
    public:
        Character(string name) : name(name)
        {
            this->name = name;
        }

        string name;

        map<string, int> variables;
};

#endif // CHARACTER_H
