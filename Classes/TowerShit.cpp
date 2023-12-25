
#include "TowerShit.h"
USING_NS_CC;


Sprite* TowerShit::createSprite()
{

    return TowerShit::create();
}


bool TowerShit::init()
{
    if (!Sprite::init()) {
        return false;
    }

    //设置图片
    this->initWithFile("/Theme/Shit/BigShit.png");
    
    //设置帧动画
    Vector<SpriteFrame*> frame;
    frame.pushBack(SpriteFrame::create("/Theme/Shit/BigShit.png", Rect(0, 0, 70, 70)));
    frame.pushBack(SpriteFrame::create("/Theme/Shit/BigShit2.png", Rect(0, 0, 70, 70)));
    frame.pushBack(SpriteFrame::create("/Theme/Shit/BigShit.png", Rect(0, 0, 70, 70)));

    float animationdelay = 0.3f;
    auto animation = Animation::createWithSpriteFrames(frame, animationdelay);

    //表示无限循环
    int repeatTime = -1;  
    auto animate = Animate::create(animation);
    auto repeatAnimation = RepeatForever::create(animate);

    //设置标签便于后续停止动作
    repeatAnimation->setTag(1); 
    this->runAction(repeatAnimation);

    
    //this->stopActionByTag(1);  //停止动作
   
 
    return true;
}