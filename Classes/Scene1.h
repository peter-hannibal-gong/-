#pragma once
#ifndef __SCENE1_H__
#define __SCENE1_H__

#include "cocos2d.h"

const int Column_Size = 12;  //横向12个格子
const int Row_Size = 7;      //纵向7个格子
const int Total_Wave_Number = 15;
#define EMPTY 0             //该格子为空
#define TOWER 1             //该格子为塔
#define INCAPABLE 2         //该格子不能放东西

#define Tower_Bottle 3   //瓶子炮塔
#define Tower_Shit 4     //便便炮塔

//表示第i列第j行的格子
struct Position  
{
    int i;
    int j;
};

class Scene1 : public cocos2d::Scene
{
private:
    

    int money=450; //初始拥有的钱
    int wave = 1;
    int Acceleration_Switch = 0;  //加速开关，初始为0，不打开
    int Pause_Switch = 1; //暂停开关初始为1，初始倒计时时暂停

    int grid_is_visible = 0;  //保存格子是否显示的状态，初始为0

public:

    Position Start_Place;
    Position End_Place;
    Position Route[18];

    //第一关地图,表示哪些地方可以放置炮塔
    int Map1[Row_Size][Column_Size] =
    { 
    {0,0,0,1,1,1,1,1,1,0,0,0},
    {0,1,0,1,1,1,1,1,1,0,1,0},
    {0,1,0,0,1,0,0,1,0,0,1,0},
    {0,1,1,0,1,1,1,1,0,1,1,0},
    {0,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,0,0,0,0,0,0,0,0,1,1}};

    //炮塔的地图
    int TowerMap1[Row_Size][Column_Size] = {
   {0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0}
    };

    //场景函数声明
    static cocos2d::Scene* createScene();  

    //初始化函数声明
    virtual bool init();                

    //回调函数声明
    void CloseCallback(cocos2d::Ref* pSender);  

    //创建Scene1对象的宏定义
    CREATE_FUNC(Scene1);    

    //将坐标转化为格点坐标
    Position transition(int x,int y);  

    //鼠标点击事件
    void onMouseDown(cocos2d::Event* event);

    //游戏开始倒计时
    void Game_Start();

    //实时更新金钱
    void update();
};


#endif // __SCENE1_H__
