
#ifndef SOUNDPLAYER_State_h
#define SOUNDPLAYER_State_h
#include <Arduino.h>
#include "DFRobot_DF1201S.h"
#include "BuckeyContext.h"
#include "Timer.h"
#include "Language.h"

// https://forum.arduino.cc/t/how-to-write-an-arduino-library-with-a-singleton-object/666625/2

// Define a struct to hold sound data
struct SoundData
{
    const char *readableName;
    const char *soundFileEnglish;
    float durationEnglish;
    const char *soundFileSpanish;
    float durationSpanish;
};

class SoundPlayer_
{
private:
    // static SoundPlayer *instance;

    SoundData *sounds; // Array of sound data

    bool _isBusy = false;

    size_t soundsCount;

    SoundPlayer_() = default; // Make constructor private

    DFRobot_DF1201S *df1201s;

    Timer *delayTimer;
        //param vol 0-30
    int volumeStates[4] = {2, 10, 20, 29};

    int state = 2;


public:
    static SoundPlayer_ &getInstance();

    SoundPlayer_(const SoundPlayer_ &) = delete; // no copying

    SoundPlayer_ &operator=(const SoundPlayer_ &) = delete;

    void initialize(DFRobot_DF1201S &df1201sInstance, SoundData soundData[], size_t count);

    float playSoundByName(const String &name, Language locale = Language::ENGLISH);

    boolean playSound(const String &trackname);

    void playSoundByNumber(int16_t number);

    void setVolume(int volume);

    bool IsBusy();

    void changeVolume();
};

extern SoundPlayer_ &SoundPlayer;

#endif
