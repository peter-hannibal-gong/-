#pragma once
#ifndef __SCENE1_H__
#define __SCENE1_H__

#include "cocos2d.h"

const int Column_Size = 12;  //����12������
const int Row_Size = 7;      //����7������
#define EMPTY 0             //�ø���Ϊ��
#define TOWER 1             //�ø���Ϊ��
#define INCAPABLE 2         //�ø��Ӳ��ܷŶ���

//��ʾ��i�е�j�еĸ���
struct Position  
{
    int i;
    int j;
};

class Scene1 : public cocos2d::Scene
{
private:
    //��ͼ
    int Map1[Row_Size][Column_Size]=   
        { {0,0,0,1,1,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0}};

    int money=450; //Ǯ


public:

    //������������
    static cocos2d::Scene* createScene();  

    //��ʼ����������
    virtual bool init();                

    //�ص���������
    void menuCloseCallback(cocos2d::Ref* pSender);  

    //����Scene1����ĺ궨��
    CREATE_FUNC(Scene1);    

    //������ת��Ϊ�������
    Position transition(int x,int y);  

    //������¼�
    void onMouseDown(cocos2d::Event* event);
};


#endif // __SCENE1_H__
