#ifndef SOUND_H
#define SOUND_H
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>

using namespace std;

class Sound
{
    public:
        Sound();

        void playSound(string fileName);

    private:
        sf::Music       music;
        sf::Sound       sound;
        sf::SoundBuffer buffer;
};

#endif // SOUND_H
