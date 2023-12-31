#pragma once
#ifndef __MAPCHOOSE_SCENE_H__
#define __MAPCHOOSE_SCENE_H__

#include "cocos2d.h"


class MapChooseScene : public cocos2d::Scene
{
private:
    int Chapter = 1; //保存当前在第几张地图
public:

    //场景函数声明
    static cocos2d::Scene* createScene();

    //初始化函数声明
    virtual bool init();
    
    void goto_helper(cocos2d::Ref* pSender);
    //回调函数声明
    void CloseCallback(cocos2d::Ref* pSender);

    //创建Scene1对象的宏定义
    CREATE_FUNC(MapChooseScene);

    
};


#endif // __MAPCHOOSE_H__

