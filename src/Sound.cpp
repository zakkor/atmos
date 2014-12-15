#include "Sound.hpp"

Sound::Sound()
{
    //ctor
}

void Sound::playSound(string fileName)
{
    int formatPos = fileName.find_first_of('.') + 1;
    string formatText;
    for (int i = formatPos; i < fileName.length(); i++)
    {
        formatText += fileName[i];
    }

    if (formatText == "ogg")
    {
        music.openFromFile(fileName);
        music.play();
    }
    else
    {
        buffer.loadFromFile(fileName);
        sound.setBuffer(buffer);
        sound.play();
    }
}
