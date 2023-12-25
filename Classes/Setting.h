

#ifndef __SETTING_SCENE_H__
#define __SETTING_SCENE_H__

#include "cocos2d.h"

class Setting : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    void CloseHitSound(Ref* pSender);

    void Closebgm(Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(Setting);
};

#endif // __SETTING_SCENE_H__
