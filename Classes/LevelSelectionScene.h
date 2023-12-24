
#pragma once
#ifndef __LEVELSELECTION_SCENE_H__
#define __LEVELSELECTION_SCENE_H__

#include "cocos2d.h"


class LevelSelectionScene : public cocos2d::Scene
{
private:
    //记录当前在第几关
    int level_number = 1;  


public:

    //场景函数声明
    static cocos2d::Scene* createScene();

    //初始化函数声明
    virtual bool init();

    //回调函数声明
    void CloseCallback(cocos2d::Ref* pSender);

    //创建Scene1对象的宏定义
    CREATE_FUNC(LevelSelectionScene);


    //创建每个关卡的概况图所在的层
    void Create_Layer1(); 


};


#endif // __LEVELSELECTION_SCENE_H__

