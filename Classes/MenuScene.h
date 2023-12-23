#pragma once

#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

class MenuScene :public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();//继承创建场景

    virtual bool init();         //初始化函数声明

    CREATE_FUNC(MenuScene);      //创建Scene对象的宏定义

    void close_game(Ref* pSender); //关闭游戏

    void goto_options(Ref* pSender);   //去设置界面

    void goto_helper(Ref* pSender);  //去帮助界面

    void goto_adventure(Ref* psender);  //去冒险模式

    void goto_boss(Ref* psender);  //去boss模式

    void goto_nest(Ref* psender);    //去怪物窝

    
    void CloseCallback(cocos2d::Ref* pSender);
};

#endif //  __Menu_SCENE_H__
