#pragma once
#ifndef __SCENE1_H__
#define __SCENE1_H__

#include "cocos2d.h"

const int Column_Size = 12;  //横向12个格子
const int Row_Size = 7;      //纵向7个格子
#define EMPTY 0             //该格子为空
#define TOWER 1             //该格子为塔
#define INCAPABLE 2         //该格子不能放东西

//表示第i列第j行的格子
struct Position  
{
    int i;
    int j;
};

class Scene1 : public cocos2d::Scene
{
private:
    //地图
    int Map1[Row_Size][Column_Size]=   
        { {0,0,0,1,1,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}};

    int money=450; //钱


public:

    //场景函数声明
    static cocos2d::Scene* createScene();  

    //初始化函数声明
    virtual bool init();                

    //回调函数声明
    void menuCloseCallback(cocos2d::Ref* pSender);  

    //创建Scene1对象的宏定义
    CREATE_FUNC(Scene1);    

    //将坐标转化为格点坐标
    Position transition(int x,int y);  

    //鼠标点击事件
    void onMouseDown(cocos2d::Event* event);
};


#endif // __SCENE1_H__
