#include "Level.hpp"

Level::Level()
{
    currentLine = 0;
}

void Level::run(TCODImage *bg, Sound& sound, vector<Character>& characters)
{
    TCODConsole *osc = new TCODConsole(150, 100);
    osc->setDefaultBackground(TCODColor::black);
    osc->setDefaultForeground(TCODColor::white);
///    bool gottaFadeIn = false;
    while (currentLine != -1 && !TCODConsole::isWindowClosed())
    {
        string statementType = statements.at(currentLine).type;
        osc->clear();
        TCODConsole::root->clear();
        bg->blit(TCODConsole::root, Config::SCREEN_WIDTH/2, Config::SCREEN_HEIGHT/2, TCOD_BKGND_SET, 0.14f, 0.14f, 0.0f);
        TCODConsole::root->flush();

///        if (gottaFadeIn)
///        {
///           for (int fade = 0; fade <= 255; fade++)
///            {
///                TCODConsole::setFade(fade, TCODColor::black);
///                TCODConsole::flush();
///            }
///            gottaFadeIn = false;
///        }

        if (statementType == "text")
        {
            osc->printRectEx(80/2, 0, 80, 80, TCOD_BKGND_DEFAULT, TCOD_CENTER, statements.at(currentLine).text.c_str());

//            int expectedHeight = osc->getHeightRect(0, 0, 80, 80, statements.at(currentLine).text.c_str());
//                                           VV
            TCODConsole::blit(osc, 0, 0, 80, 10, TCODConsole::root, Config::SCREEN_WIDTH /2 - 80/2, 55, 1, 0.6);
            TCODConsole::root->flush();

            TCODConsole::waitForKeypress(true);
        }
        else if (statementType == "image")
        {
            delete bg;
            bg = new TCODImage(statements.at(currentLine).text.c_str());
            //Fade
///            for (int fade = 255; fade >= 0; fade--)
///            {
///                TCODConsole::setFade(fade, TCODColor::black);
///                TCODConsole::flush();
///            }
///            gottaFadeIn = true;
        }
        else if (statementType == "sound")
        {
            sound.playSound(statements.at(currentLine).text.c_str());
        }
        else if (statementType == "dialogue")
        {
            if (dialogues.find(statements.at(currentLine).text) != dialogues.end())
            {
                dialogues.at(statements.at(currentLine).text).run(osc, bg, characters);
            }

        }
        else if (statementType == "sleep")
        {
            TCODSystem::sleepMilli(atoi(statements.at(currentLine).text.c_str()));
        }

        currentLine = statements.at(currentLine).nextLine;
    }
}

void Level::addStatement(string text, int nextLine, string type)
{
    statements.push_back(Statement(text, nextLine, type));
}

void Level::addDialogue(string fileName, Dialogue dialogueName)
{
    dialogues.emplace(fileName, dialogueName);
}
