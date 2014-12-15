#ifndef GAME_H
#define GAME_H
#include "Parser.hpp"
#include "Config.hpp"
//#include "Sound.hpp"

class Game
{
    public:
        Game();

        void run();

    private:
        void render();


    ///Variables:
    private:
        TCODImage *background;
        Sound sound;

        vector<Character> characters;
        Level level;
};

#endif // GAME_H
