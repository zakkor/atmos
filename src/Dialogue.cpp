#include "Dialogue.hpp"

Expression::Expression(string character, string variable, int value)
{
    this->character = character;
    this->variable = variable;
    this->value = value;
}

PlayerReply::PlayerReply(string text, short nextLine)
{
    this->text = text;
    this->nextLine = nextLine;
}

PlayerReply::PlayerReply(string text, short nextLine, Expression condition, Expression action)
{
    this->text = text;
    this->nextLine = nextLine;

    this->condition = condition;
    this->action = action;
}


Dialogue::Dialogue()
{
    currentLine = 0;
    replyNumber = 0;
}

void Dialogue::run(TCODConsole *osc, TCODImage *bg, vector<Character> &characters)
{
    osc->setDefaultBackground(TCODColor::black);
    osc->setDefaultForeground(TCODColor::white);

    while (currentLine != -1 && !TCODConsole::isWindowClosed())
    {
        osc->clear();
        TCODConsole::root->clear();
        bg->blit(TCODConsole::root, Config::SCREEN_WIDTH/2, Config::SCREEN_HEIGHT/2, TCOD_BKGND_SET, 0.14f, 0.14f, 0.0f);
        TCODConsole::root->flush();


        osc->setDefaultForeground(TCODColor::yellow);
        //Npc line
//        string delayedPrinter;
//        for (int i = 0; i < lineText.at(currentLine).size(); i++)
//        {
//            osc->clear();
//            delayedPrinter += lineText.at(currentLine).at(i);
            osc->printRectEx(80/2, 0, 80, 80, TCOD_BKGND_DEFAULT, TCOD_CENTER, lineText.at(currentLine).c_str());
//            TCODConsole::blit(osc, 0, 0, 80, 10, TCODConsole::root, Config::SCREEN_WIDTH /2 - 80/2, 55, 1, 0.6);
//            TCODConsole::root->flush();
//            TCODSystem::sleepMilli(5);
//        }
        osc->setDefaultForeground(TCODColor::white);


        int expectedHeight = osc->getHeightRect(0, 0, 80, 80, lineText.at(currentLine).c_str());

        //Lists lineReplies available
        for (unsigned int i = 0; i < lineReplies.at(currentLine).size(); ++i)
        {
            Expression aux_cond;

            aux_cond.character = lineReplies.at(currentLine).at(i).condition.character;
            aux_cond.variable  = lineReplies.at(currentLine).at(i).condition.variable;
            aux_cond.value     = lineReplies.at(currentLine).at(i).condition.value;

            if (aux_cond.character != "")
            {
                for (auto c : characters)
                {
                    if (c.name == aux_cond.character)
                    {
//                        if (c.variables.find(aux_cond.variable) != c.variables.end())
                        {
                            if (c.variables.at(aux_cond.variable) == aux_cond.value)
                            {
                                osc->printRectEx(80/2, i + 2 + expectedHeight, 80, 80, TCOD_BKGND_DEFAULT, TCOD_CENTER,
                                                 lineReplies.at(currentLine).at(i).text.c_str());
                            }
                        }
                    }
                }
            }
            else
            {
                osc->printRectEx(80/2, i + 2 + expectedHeight, 80, 80, TCOD_BKGND_DEFAULT, TCOD_CENTER,
                                 lineReplies.at(currentLine).at(i).text.c_str());
            }
        }
        ///
        TCODConsole::blit(osc, 0, 0, 80, 10, TCODConsole::root, Config::SCREEN_WIDTH /2 - 80/2, 55, 1, 0.6);
        TCODConsole::root->flush();


        TCOD_key_t key;
        key = TCODConsole::waitForKeypress(true);

        while (key.c != '1' && key.c != '2' && key.c != '3' && key.c != '4')
        {
            key = TCODConsole::waitForKeypress(true);
        }

        replyNumber = key.c - '0' - 1;

        Expression aux_act;

        aux_act.character = lineReplies.at(currentLine).at(replyNumber).action.character;
        aux_act.variable  = lineReplies.at(currentLine).at(replyNumber).action.variable;
        aux_act.value     = lineReplies.at(currentLine).at(replyNumber).action.value;

        if (aux_act.character != "")
        {
            for (auto &i : characters)
            {
                if (i.name == aux_act.character)
                {
                    i.variables.at(aux_act.variable) = aux_act.value;
                }
            }
        }
        currentLine = lineReplies.at(currentLine).at(replyNumber).nextLine;
    }
}

void Dialogue::addReply(int pos, string text, int linkTo)
{
    if (pos >= lineReplies.size())
    {
        lineReplies.resize(lineReplies.size() + 1);
    }
    lineReplies.at(pos).push_back(PlayerReply(text, linkTo));
}

void Dialogue::addReply(int pos, string text, int linkTo,
                        Expression condition, Expression action)
{
    if (pos >= lineReplies.size())
    {
        lineReplies.resize(lineReplies.size() + 1);
    }
    lineReplies.at(pos).push_back(PlayerReply(text, linkTo, condition, action));
}


void Dialogue::addNpcLine(string text)
{
    lineText.push_back(text);
}
