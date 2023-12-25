#pragma once
#ifndef __SCENE1_H__
#define __SCENE1_H__

#include "cocos2d.h"

const int Column_Size = 12;  //����12������
const int Row_Size = 7;      //����7������
const int Total_Wave_Number = 15;
#define EMPTY 0             //�ø���Ϊ��
#define TOWER 1             //�ø���Ϊ��
#define INCAPABLE 2         //�ø��Ӳ��ܷŶ���

#define Tower_Bottle 3   //ƿ������
#define Tower_Shit 4     //�������

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
    {0,0,0,1,1,1,1,1,1,0,0,0},
    {0,1,0,1,1,1,1,1,1,0,1,0},
    {0,1,0,0,1,0,0,1,0,0,1,0},
    {0,1,1,0,1,1,1,1,0,1,1,0},
    {0,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,0,0,0,0,0,0,0,0,1,1}};

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

    //��Ϸ��ʼ����ʱ
    void Game_Start();

    //ʵʱ���½�Ǯ
    void update();
};


#endif // __SCENE1_H__
