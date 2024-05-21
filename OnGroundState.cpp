#include "OnGroundState.h"
#include <Arduino.h>
#include "SoundPlayer.h"
#include "BuckeyContext.h"

OnGroundState::OnGroundState()
{
    delayTimer = new Timer();
    attentionTimer = new Timer();
    pinMode(PIR_PIN, INPUT);
}

void OnGroundState::enter(BuckeyContext &context)
{
    Serial.println("State On Ground");
    inCallAction = OnGrourdEnum::IN_DELAY;

    int time = 4;
    if (BuckeyContext::currentBucketState == BucketState::INSESSION)
    {

        // if more attempts then thank the player or ask to not be put down.

        String soundFileId = "ThankYouForPlayingWithMe";
        if (BuckeyContext::sessionProgressCount < 2)
        {
            soundFileId = dontputdown[random(2)];
        }

        float duration = SoundPlayer.playSoundByName(soundFileId, BuckeyContext::currentLanguage);
        time += duration;
    }

    BuckeyContext::currentBucketState = BucketState::ONGROUND;
    attentionTimer->setTimer(ATTENTION_CALL_INTERVAL);
    delayTimer->setTimer(time);
}

void OnGroundState::exit(BuckeyContext &context)
{
}

void OnGroundState::update(BuckeyContext &context)
{

    if (inCallAction == OnGrourdEnum::SEARCHING)
    {
        int val = digitalRead(PIR_PIN); // read input value
        if (val == HIGH && delayTimer->isExpired())
        {

            // sound choices strings
            String soundFileId = pickMeUpSounds[count];

            // random english or spanish
            Language locale = ((count + languageCount) % 2 == 0) ? Language::ENGLISH : Language::SPANISH;
            SoundPlayer.playSoundByName(soundFileId, locale);

            count++;
            if (count >= 4)
            {
                count = 0;
                languageCount += 1;
            }

            delayTimer->setTimer(8);
            inCallAction = OnGrourdEnum::IN_DELAY;
            attentionTimer->setTimer(ATTENTION_CALL_INTERVAL);
        }
        else if (attentionTimer->isExpired())
        {

            int soundIndex = random(0, 4); // Generate a random number between 0 and 3
            String soundToPlay = pickMeUpSounds[soundIndex];
            SoundPlayer.playSoundByName(soundToPlay);
            delayTimer->setTimer(8);
            attentionTimer->setTimer(ATTENTION_CALL_INTERVAL);
        }
    }
    else if (inCallAction == OnGrourdEnum::IN_DELAY)
    {
        if (delayTimer->isExpired())
        {
            inCallAction = OnGrourdEnum::SEARCHING;
        }
    }
}