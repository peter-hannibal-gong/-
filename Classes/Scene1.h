#pragma once
#ifndef __SCENE1_H__
#define __SCENE1_H__

#include "cocos2d.h"

const int Column_Size = 12;  //����12������
const int Row_Size = 7;      //����7������
const int Total_Wave_Number = 15;

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
    int wave = 1;
    int Acceleration_Switch = 0;  //���ٿ��أ���ʼΪ0������
    int Pause_Switch = 1; //��ͣ���س�ʼΪ1����ʼ����ʱʱ��ͣ

    int grid_is_visible = 0;  //��������Ƿ���ʾ��״̬����ʼΪ0

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
    void update();
};


#endif // __SCENE1_H__
