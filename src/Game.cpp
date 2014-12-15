#include "Game.h"
#include <iostream>
#include <vector>

using namespace std;

Game::Game()
{
    TCODConsole::initRoot(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, "", false, TCOD_renderer_t::TCOD_RENDERER_SDL);
    TCODConsole::root->setDefaultBackground(TCODColor::white);
    TCODConsole::root->setDefaultForeground(TCODColor::black);
    TCODConsole::root->setAlignment(TCOD_alignment_t::TCOD_LEFT);

    background = new TCODImage("Media/blank.png");


    Parser parser = Parser();

    parser.loadFile("Scripts/characters.txt");
    parser.parseCharacters(characters);

    parser.loadFile("Scripts/level.txt");
    parser.parseLevel(level, characters);
}

void Game::run()
{
    while (!TCODConsole::isWindowClosed())
    {
        render();
        break;
    }
}

void Game::render()
{
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,NULL,NULL);
    level.run(background, sound, characters);
}
