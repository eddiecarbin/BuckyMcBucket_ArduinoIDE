#include <Arduino.h>
#include "SoundPlayer.h"
#include "DFRobot_DF1201S.h"

void SoundPlayer_::initialize(DFRobot_DF1201S &df1201sInstance, SoundData soundData[], size_t count)
{

    this->df1201s = &df1201sInstance;

    this->sounds = soundData;
    this->soundsCount = count;

    df1201s->setLED(true);

    delayTimer = new Timer();
}

float SoundPlayer_::playSoundByName(const String &name, Language language)
{
    for (size_t i = 0; i < soundsCount; ++i)
    {
        if (strcmp(sounds[i].readableName, name.c_str()) == 0)
        {
            // Serial.println(sounds[i].SOUNDFILEENGLISH);

            if (language == Language::SPANISH && sounds[i].soundFileSpanish && strlen(sounds[i].soundFileSpanish) > 0)
            {
                _isBusy = true;
                String filePath = String("/") + sounds[i].soundFileSpanish;
                df1201s->playSpecFile(filePath.c_str());
                return delayTimer->setTimer(sounds[i].durationSpanish);
            }
            else
            {
                _isBusy = true;
                // Either language is ENGLISH or no Spanish sound file exists, play English version
                String filePath = String("/") + sounds[i].soundFileEnglish;
                df1201s->playSpecFile(filePath.c_str());
                return delayTimer->setTimer(sounds[i].durationEnglish);
            }
            break;
        }
    }

    Serial.println("Sound not found: " + name);
    _isBusy = false;
    return -1; // Sound not found
}

boolean SoundPlayer_::playSound(const String &trackname)
{

    if (trackname == "")
    {
        return false;
    }

    delayTimer->setTimer(3);

    // Serial.println(trackname);
    df1201s->playSpecFile(trackname);

    return true;
}

void SoundPlayer_::changeVolume()
{
    state += 1;

    if (state >= 4)
    {
        state = 0;
    }

    int volume = volumeStates[state];

    setVolume(volume);
}

void SoundPlayer_::playSoundByNumber(int16_t number)
{
    // Serial.println(number);
    df1201s->playFileNum(number);
}

void SoundPlayer_::setVolume(int volume)
{
    // Set volume for left, right channels. lower numbers == louder volume!
    df1201s->setVol(volume);
}

bool SoundPlayer_::IsBusy()
{
    if (delayTimer->isExpired())
    {
        _isBusy = false;
    }

    return _isBusy;
}

SoundPlayer_ &SoundPlayer_::getInstance()
{
    static SoundPlayer_ instance;
    return instance;
}

SoundPlayer_ &SoundPlayer = SoundPlayer.getInstance();