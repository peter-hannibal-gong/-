#pragma once
#ifndef __SCENE1_H__
#define __SCENE1_H__

#include "cocos2d.h"


class Scene1 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();  //场景函数声明

    virtual bool init();                //初始化函数声明

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);  //回调函数声明

    // implement the "static create()" method manually
    CREATE_FUNC(Scene1);    //创建Scene1对象的宏定义
};

#endif // __HELLOWORLD_SCENE_H__
