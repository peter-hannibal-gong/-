
#pragma once
#ifndef __LEVELSELECTION_SCENE_H__
#define __LEVELSELECTION_SCENE_H__

#include "cocos2d.h"


class LevelSelectionScene : public cocos2d::Scene
{
private:
    //��¼��ǰ�ڵڼ���
    int level_number = 1;  


public:

    //������������
    static cocos2d::Scene* createScene();

    //��ʼ����������
    virtual bool init();

    //�ص���������
    void CloseCallback(cocos2d::Ref* pSender);

    //����Scene1����ĺ궨��
    CREATE_FUNC(LevelSelectionScene);


    //����ÿ���ؿ��ĸſ�ͼ���ڵĲ�
    void Create_Layer1(); 


};


#endif // __LEVELSELECTION_SCENE_H__

