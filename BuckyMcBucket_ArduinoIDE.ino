#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "BuckeyContext.h"
#include "SoundPlayer.h"
#include "DFRobot_DF1201S.h"
// #include <SoftwareSerial.h>
#include <Arduino_BMI270_BMM150.h>
#include "StateMachine.h"
#include "Singleton.h"
#include "MotionController.h"
#include "HugRequestState.h"

BuckeyContext *buckeyContext;
MotionController *motionController;

#define DF1201SSerial Serial1

DFRobot_DF1201S DF1201S;

SoundData soundData[] = {
    // Paste the output here{"AhhThatsSoNice", "SND101.wav", 3.30, "SND100.wav", 3.70},
    {"AhhThatsSoNice", "SND100.wav", 3.70, "SND101.wav", 3.30},
    {"BeatBox", "SND102.wav", 14.10},
    {"HelloImBuckyCanSomeonePickMeUp", "SND103.wav", 4.80, "SND104.wav", 4.80},
    {"HelloMellamoBuckyMcBucket", "SND105.wav", 5.60, "SND106.wav", 5.70},
    {"HelloWillSomebodyPickMeUp", "SND107.wav", 3.50, "SND108.wav", 3.70},
    {"HeyDanceWithMe", "SND109.wav", 3.00, "SND110.wav", 3.50},
    {"HeyDontLeaveMe", "SND111.wav", 2.50, "SND112.wav", 2.90},
    {"HeyletsDance", "SND113.wav", 2.90, "SND114.wav", 2.70},
    {"HeyLevantame", "SND115.wav", 2.60, "SND116.wav", 2.10},
    {"HeyPickMeUp", "SND117.wav", 2.00, "SND118.wav", 2.60},
    {"HiImBuckyLetsGo", "SND119.wav", 3.80, "SND120.wav", 4.20},
    {"HiWillYouGiveMeAHug", "SND121.wav", 3.00, "SND122.wav", 4.40},
    {"HolaWillSomebobyPickMeUp", "SND123.wav", 3.20, "SND124.wav", 3.70},
    {"IDoLoveToJumpYoureGood", "SND125.wav", 3.60, "SND126.wav", 4.50},
    {"ImBucky", "SND127.wav", 1.40},
    {"ImJustABucketAllBuyMyself", "SND128.wav", 5.90, "SND129.wav", 5.60},
    {"JumpJumpJump", "SND130.wav", 3.80, "SND131.wav", 5.00},
    {"OhAreYouLeaving", "SND132.wav", 2.50, "SND133.wav", 3.00},
    {"OhYeahThatWasAGoodShake", "SND134.wav", 3.80, "SND135.wav", 4.30},
    {"OkILikeToSwingSwingMe", "SND136.wav", 4.00, "SND137.wav", 4.80},
    {"OkLetsGoSeeSomething", "SND138.wav", 3.10, "SND139.wav", 2.90},
    {"OkLetsJumpAround", "SND140.wav", 2.20, "SND141.wav", 2.70},
    {"OkLetsSpeak", "SND142.wav", 2.50, "SND143.wav", 2.70},
    {"OkWillYouJumpAroundWithMe", "SND144.wav", 2.80, "SND145.wav", 1.70},
    {"OkWillYouSwingMe", "SND146.wav", 2.20, "SND147.wav", 3.10},
    {"QuickWillYouShakeMe", "SND148.wav", 2.40, "SND149.wav", 2.70},
    {"ThanksForPlayingWithMe", "SND150.wav", 1.30, "SND151.wav", 2.30},
    {"ThankYouForPlayingWithMe", "SND152.wav", 3.90, "SND153.wav", 4.50},
    {"ThankYouForThatDance", "SND154.wav", 1.80, "SND155.wav", 2.30},
    {"ThankYouWillYouCarryMe", "SND156.wav", 3.30, "SND157.wav", 3.30},
    {"ThatWasAGreatSwing", "SND158.wav", 2.20, "SND159.wav", 3.10},
    {"WeeThatsSoFun", "SND160.wav", 3.00, "SND161.wav", 3.50},
    {"Whistle", "SND162.wav", 4.00},
    {"WillYouIntroduceMe", "SND163.wav", 3.20, "SND164.wav", 2.70},
    {"YoureAGoodDancer", "SND165.wav", 2.10, "SND166.wav", 1.80},
    {"YoureNiceWillYouShowMeAround", "SND167.wav", 3.00, "SND168.wav", 5.50}

};

void setup()
{

  Serial.begin(9600);
  delay(2000);

  Serial.println("BuckyMcBucket");
  if (!IMU.begin())
  {
    Serial.println("Failed to initialize IMU!");
    while (1)
      ;
  }
  delay(200);
  
  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  // Serial.println();
  // Serial.println("Acceleration in G's");
  // Serial.println("X\tY\tZ");
  delay(500);

  DF1201SSerial.begin(115200);
  while (!DF1201S.begin(DF1201SSerial))
  {
    Serial.println("Init failed, please check the wire connection!");
    delay(1000);
  }

  DF1201S.setLED(true);

  /*Set volume to 20
  param vol 0-30*/
  DF1201S.setVol(/*VOL = */ 20);
  DF1201S.switchFunction(DFRobot_DF1201S::MUSIC);
  // DF1201S.setPlayMode(DFRobot_DF1201S::SINGLE);
  DF1201S.enableAMP();
  // DF1201S.disableAMP();
  delay(400);
  randomSeed(analogRead(0));

  // DF1201S.setPlayMode(DFRobot_DF1201S::SINGLE);
  Serial.println("Test init soundplaye 2 r");

  SoundPlayer_ &soundPlayer = SoundPlayer_::getInstance();
  soundPlayer.initialize(DF1201S, soundData, sizeof(soundData) / sizeof(soundData[0]));

  buckeyContext = new BuckeyContext();
  buckeyContext->initialize();
  delay(100);

  boolean result = SoundPlayer.playSoundByName("HiImBuckyLetsGo");
  // Serial.println(SoundPlayer.IsBusy() ? "Busy" : "NOT Busy");
  // Serial.println(SoundPlayer.IsBusy() ? "Busy" : "NOT Busy");

  delay(3000);
  Serial.println("Finished Setup");
}

void loop()
{
  buckeyContext->update();
  delay(100);
}
