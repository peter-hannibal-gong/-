#pragma once
#ifndef __SCENE1_H__
#define __SCENE1_H__

#include "cocos2d.h"
#include<vector>
const int Column_Size = 12;  //横向12个格子
const int Row_Size = 7;      //纵向7个格子
const int Total_Wave_Number = 15;    //总共的波数
const int Monster_Number = 3;      //每波有几只怪物

USING_NS_CC;

//点位种类读取读取：x/100==检测值
//点位种类赋予：x=赋值
//该格子为空
#define EMPTY   000     //检测值//赋值
//该格子为障碍物
#define BLOCK         9  //检测值
#define BLOCK_aggsign 999//赋值
//该格子为路
#define LOAD          8  //检测值
#define LOAD_aggsign  888//赋值
//瓶子炮塔
#define Bottle  1  //检测值
#define Bottle1 101//赋值
#define Bottle2 102//赋值
#define Bottle3 103//赋值
//便便炮塔
#define Shit    2  //检测值
#define Shit1   201//赋值
#define Shit2   202//赋值
#define Shit3   203//赋值

//针对界面中的Tag
//对不同类型的node再地图上的标签，我们采用加1000的方式来区分开来
//i*100+j+5000为一级便便塔  


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
    int wave = 1;  //当前的波数
    int Monster_Order = 0;  //当前产生的怪物的在一波中的次序

    int Acceleration_Switch = 0;  //加速开关，初始为0，不打开
    int Pause_Switch = 1; //暂停开关初始为1，初始倒计时时暂停

    int grid_is_visible = 0;  //保存格子是否显示的状态，初始为0
    int range_is_visible = 0;  //保存范围是否显示

    

public:

    Position Start_Place;
    Position End_Place;
    Position Route[18];


    //第一关地图,表示哪些地方可以放置炮塔
    int Map1[Row_Size][Column_Size] =
    { 
    {EMPTY,EMPTY,EMPTY,BLOCK_aggsign,BLOCK_aggsign,BLOCK_aggsign,BLOCK_aggsign,BLOCK_aggsign,BLOCK_aggsign,EMPTY,EMPTY,EMPTY},
    {EMPTY,LOAD_aggsign,EMPTY,BLOCK_aggsign,BLOCK_aggsign,BLOCK_aggsign,BLOCK_aggsign,BLOCK_aggsign,BLOCK_aggsign,EMPTY,LOAD_aggsign,EMPTY},
    {EMPTY,LOAD_aggsign,EMPTY,EMPTY,BLOCK_aggsign,EMPTY,EMPTY,BLOCK_aggsign,EMPTY,EMPTY,LOAD_aggsign,EMPTY},
    {EMPTY,LOAD_aggsign,BLOCK_aggsign,EMPTY,LOAD_aggsign,LOAD_aggsign,LOAD_aggsign,LOAD_aggsign,EMPTY,BLOCK_aggsign,LOAD_aggsign,EMPTY},
    {EMPTY,LOAD_aggsign,LOAD_aggsign,LOAD_aggsign,LOAD_aggsign,BLOCK_aggsign,BLOCK_aggsign,LOAD_aggsign,LOAD_aggsign,LOAD_aggsign,LOAD_aggsign,EMPTY},
    {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY},
    {EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY}


    };


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

    //共15波，每波3只怪物  0表示flyMonster，1表示pinkMonster，2表示greenMonster
    int Monster_Wave[Total_Wave_Number][Monster_Number] = {
        {1,1,1},{0,0,0},{2,2,2},
        {1,1,1},{0,0,0},{2,2,2},
        {1,1,1},{0,0,0},{2,2,2},
        {1,1,1},{0,0,0},{2,2,2},
        {1,1,1},{0,0,0},{2,2,2}
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
    void gch_onMouseDown(cocos2d::Event* event);

    //游戏开始倒计时
    void Game_Start();

    //实时更新金钱
    void updateMoney(float dt);

    //实时更新波数
    void updateWave(float dt);

    //实时产生怪物
    void updateMonster(float dt);

    //监测活着的怪物
    void AliveMonster(float dt);

    //每0.2秒监测一次是否有怪物到达终点，吃到萝卜
    void If_Attack_Carrot(float dt);
};


#endif // __SCENE1_H__
