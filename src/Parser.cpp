#include "Parser.hpp"

bool Parser::loadFile(string fileName)
{
    lines.clear();
    string buffer;
    unsigned int nmbrLines = 0;
    std::ifstream scrStream(fileName);
    while (std::getline(scrStream, buffer))
    {
        lines.push_back(buffer);
        nmbrLines++;
    }

    lines.resize(nmbrLines);

    if (lines.empty())
    {
        std::cout << "Script empty! Either missing file or other issue!\n";
        return 0;
    }
    else
    {
        std::cout << fileName << " loaded successfully. (" << nmbrLines << " lines)\n";
        return 1;
    }
}

string Parser::copyFromCharToEnd(char character, string str)
{
    unsigned int position = str.find_first_of(character) + 2;
    string newStr = "";
    for (unsigned int i = position; i < str.size(); i++)
    {
        newStr += str.at(i);
    }
    return newStr;
}

string Parser::copyFromPosToEnd(int pos, string str)
{
    string newStr = "";

    for (unsigned int i = pos; i < str.size(); i++)
    {
        newStr += str.at(i);
    }

    return newStr;
}

string Parser::copyFromStartToChar(char character, string str)
{
    string newStr = "";
    int end;
    if (character == '.')
    {
        end = str.find_first_of(character);
    }
    else
    {
        end = str.find_first_of(character) - 1;
    }

    for (unsigned int i = 0; i < end; ++i)
    {
        newStr += str.at(i);
    }

    return newStr;
}

string Parser::copyFromCharToChar(char char1, char char2, string str)
{
    string newStr = "";

    int start = str.find_first_of(char1) + 1;
    int end = str.find_first_of(char2);

    for (unsigned int i = start; i < end; ++i)
    {
        newStr += str.at(i);
    }
    return newStr;
}


void Parser::parseDialogue(Dialogue &dialogue, vector<Character> &characters)
{
    int lineText = -1;
    for (unsigned int i = 0; i < lines.size();)
    {
        string buffer = lines.at(i);
        dialogue.addNpcLine(buffer);
        lineText++;

        bool noMoreReplies = false;
        int counter = 1;

        while (!noMoreReplies)
        {
            if ((i + counter) < lines.size())
            {
                buffer = lines.at(i + counter);

                //This must be the worst indentation check ive seen in my life
                if (buffer[0] == ' ' && buffer[1] == ' '
                        && buffer[2] == ' ' && buffer[3] == ' ')
                {
                    //First we take care of the actual text, then the link
                    buffer = copyFromPosToEnd(4, buffer);

                    string replyText = copyFromStartToChar('{', buffer);

                    int replyLinkTo = atoi(copyFromCharToChar('{', '}', buffer).c_str());

                    //Now we start looking for the condition
                    buffer = copyFromPosToEnd(buffer.find_first_of('}') + 1, buffer);

                    string replyCond = copyFromCharToChar('{', '}', buffer);
                    Expression condition;
                    if (replyCond != "")
                    {
                        condition.character = copyFromStartToChar('.', replyCond);
                        condition.variable = copyFromCharToChar('.', ' ', replyCond);
                        condition.value = atoi(copyFromCharToEnd('=', replyCond).c_str());
                    }

                    buffer = copyFromPosToEnd(buffer.find_first_of('}') + 1, buffer);

                    string replyAction = copyFromCharToChar('{', '}', buffer);
                    Expression action;

                    if (replyAction != "")
                    {
                        action.character = copyFromStartToChar('.', replyAction);
                        action.variable = copyFromCharToChar('.', ' ', replyAction);
                        action.value = atoi(copyFromCharToEnd('=', replyAction).c_str());
                    }
                    dialogue.addReply(lineText, replyText, replyLinkTo, condition, action);
                    counter++;
                }
                else
                {
                    i += counter;
                    noMoreReplies = true;
                }
            }
            else
            {
                i += counter;
                noMoreReplies = true;
            }
        }
    }
    cout << "Parsed dialog file successfully.\n";
}

void Parser::parseCharacters(vector<Character>& characters)
{
//    int lineText = -1;
    for (unsigned int i = 0; i < lines.size();)
    {
        string buffer = lines.at(i);
        Character newChar = Character(buffer);

        bool noMoreAttributes = false;
        int counter = 1;

        while (!noMoreAttributes)
        {
            if ((i + counter) < lines.size())
            {
                buffer = lines.at(i + counter);

                //This must be the worst indentation check ive seen in my life
                if (buffer[0] == ' ' && buffer[1] == ' '
                        && buffer[2] == ' ' && buffer[3] == ' ')
                {
                    buffer = copyFromPosToEnd(4, buffer);
                    newChar.variables.emplace(buffer, 0);
                    counter++;
                }
                else
                {
                    i += counter;
                    noMoreAttributes = true;
                    characters.push_back(newChar);
                }
            }
            else
            {
                i += counter;
                noMoreAttributes = true;
                characters.push_back(newChar);
            }
        }
    }
    cout << "Parsed characters successfully.\n";
}


void Parser::parseLevel(Level& level, vector<Character>& characters)
{
    for (unsigned int i = 0; i < lines.size(); ++i)
    {
        string buffer = lines.at(i);
        string statementType = copyFromCharToChar('{', '}', buffer);
        buffer = copyFromPosToEnd(buffer.find_first_of(' ') + 1, buffer);
        string statementText = copyFromStartToChar('{', buffer);
        buffer = copyFromPosToEnd(buffer.find_first_of('{'), buffer);
        int statementLinkTo = atoi(copyFromCharToChar('{', '}', buffer).c_str());

        level.addStatement(statementText, statementLinkTo, statementType);

        if (statementType == "dialogue")
        {
            Parser newParser = Parser();
            cout << "    ";
            newParser.loadFile("Scripts/" + statementText);
            Dialogue newDialogue = Dialogue();
            newParser.parseDialogue(newDialogue, characters);
            level.addDialogue(statementText, newDialogue);
        }
    }
    cout << "Parsed level successfully.\n";
}
