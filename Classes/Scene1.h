#pragma once
#ifndef __SCENE1_H__
#define __SCENE1_H__

#include "cocos2d.h"


class Scene1 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();  //������������

    virtual bool init();                //��ʼ����������

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);  //�ص���������

    // implement the "static create()" method manually
    CREATE_FUNC(Scene1);    //����Scene1����ĺ궨��
};

#endif // __HELLOWORLD_SCENE_H__
