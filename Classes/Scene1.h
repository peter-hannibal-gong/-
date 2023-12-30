#pragma once
#ifndef __SCENE1_H__
#define __SCENE1_H__

#include "cocos2d.h"
#include<vector>
const int Column_Size = 12;  //����12������
const int Row_Size = 7;      //����7������
const int Total_Wave_Number = 15;    //�ܹ��Ĳ���
const int Monster_Number = 3;      //ÿ���м�ֻ����

USING_NS_CC;

//��λ�����ȡ��ȡ��x/100==���ֵ
//��λ���ำ�裺x=��ֵ
//�ø���Ϊ��
#define EMPTY   000     //���ֵ//��ֵ
//�ø���Ϊ�ϰ���
#define BLOCK         9  //���ֵ
#define BLOCK_aggsign 999//��ֵ
//�ø���Ϊ·
#define LOAD          8  //���ֵ
#define LOAD_aggsign  888//��ֵ
//ƿ������
#define Bottle  1  //���ֵ
#define Bottle1 101//��ֵ
#define Bottle2 102//��ֵ
#define Bottle3 103//��ֵ
//�������
#define Shit    2  //���ֵ
#define Shit1   201//��ֵ
#define Shit2   202//��ֵ
#define Shit3   203//��ֵ

//��Խ����е�Tag
//�Բ�ͬ���͵�node�ٵ�ͼ�ϵı�ǩ�����ǲ��ü�1000�ķ�ʽ�����ֿ���
//i*100+j+5000Ϊһ�������  


//��ʾ��i�е�j�еĸ���
struct Position  
{
    int i;
    int j;
};

class Scene1 : public cocos2d::Scene
{
private:
    

    int money=450; //��ʼӵ�е�Ǯ
    int wave = 1;  //��ǰ�Ĳ���
    int Monster_Order = 0;  //��ǰ�����Ĺ������һ���еĴ���

    int Acceleration_Switch = 0;  //���ٿ��أ���ʼΪ0������
    int Pause_Switch = 1; //��ͣ���س�ʼΪ1����ʼ����ʱʱ��ͣ

    int grid_is_visible = 0;  //��������Ƿ���ʾ��״̬����ʼΪ0
    int range_is_visible = 0;  //���淶Χ�Ƿ���ʾ

    

public:

    Position Start_Place;
    Position End_Place;
    Position Route[18];


    //��һ�ص�ͼ,��ʾ��Щ�ط����Է�������
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


    //�����ĵ�ͼ
    int TowerMap1[Row_Size][Column_Size] = {
   {0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0,0,0,0,0}
    };

    //��15����ÿ��3ֻ����  0��ʾflyMonster��1��ʾpinkMonster��2��ʾgreenMonster
    int Monster_Wave[Total_Wave_Number][Monster_Number] = {
        {1,1,1},{0,0,0},{2,2,2},
        {1,1,1},{0,0,0},{2,2,2},
        {1,1,1},{0,0,0},{2,2,2},
        {1,1,1},{0,0,0},{2,2,2},
        {1,1,1},{0,0,0},{2,2,2}
    };
    
    //������������
    static cocos2d::Scene* createScene();  

    //��ʼ����������
    virtual bool init();                

    //�ص���������
    void CloseCallback(cocos2d::Ref* pSender);  

    //����Scene1����ĺ궨��
    CREATE_FUNC(Scene1);    

    //������ת��Ϊ�������
    Position transition(int x,int y);  

    //������¼�
    void onMouseDown(cocos2d::Event* event);
    void gch_onMouseDown(cocos2d::Event* event);

    //��Ϸ��ʼ����ʱ
    void Game_Start();

    //ʵʱ���½�Ǯ
    void updateMoney(float dt);

    //ʵʱ���²���
    void updateWave(float dt);

    //ʵʱ��������
    void updateMonster(float dt);

    //�����ŵĹ���
    void AliveMonster(float dt);

    //ÿ0.2����һ���Ƿ��й��ﵽ���յ㣬�Ե��ܲ�
    void If_Attack_Carrot(float dt);
};


#endif // __SCENE1_H__
