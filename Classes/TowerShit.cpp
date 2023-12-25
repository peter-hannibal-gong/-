
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

    //����ͼƬ
    this->initWithFile("/Theme/Shit/BigShit.png");
    
    //����֡����
    Vector<SpriteFrame*> frame;
    frame.pushBack(SpriteFrame::create("/Theme/Shit/BigShit.png", Rect(0, 0, 70, 70)));
    frame.pushBack(SpriteFrame::create("/Theme/Shit/BigShit2.png", Rect(0, 0, 70, 70)));
    frame.pushBack(SpriteFrame::create("/Theme/Shit/BigShit.png", Rect(0, 0, 70, 70)));

    float animationdelay = 0.3f;
    auto animation = Animation::createWithSpriteFrames(frame, animationdelay);

    //��ʾ����ѭ��
    int repeatTime = -1;  
    auto animate = Animate::create(animation);
    auto repeatAnimation = RepeatForever::create(animate);

    //���ñ�ǩ���ں���ֹͣ����
    repeatAnimation->setTag(1); 
    this->runAction(repeatAnimation);

    
    //this->stopActionByTag(1);  //ֹͣ����
   
 
    return true;
}