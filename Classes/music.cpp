
#include "music.h"
#include "MenuScene.h"
USING_NS_CC;

class CocosDenshion::SimpleAudioEngine* bgm = CocosDenshion::SimpleAudioEngine::getInstance();
class CocosDenshion::SimpleAudioEngine* hit_sound = CocosDenshion::SimpleAudioEngine::getInstance();
bool bgm_open = 0;
bool hit_sound_open = 0;
/*
if (bgm_open&&!bgm->isBackgroundMusicPlaying())
        bgm->playBackgroundMusic("/music/bgm.mp3", true);
bgm->stopBackgroundMusic();
hit_sound->playEffect("/music/hit_sound.mp3", false, 1.0f, 1.0f, 1.0f);
    */