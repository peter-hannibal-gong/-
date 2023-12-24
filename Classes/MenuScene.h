#pragma once

#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"



class MenuScene :public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();//�̳д�������

    virtual bool init();         //��ʼ����������

    CREATE_FUNC(MenuScene);      //����Scene����ĺ궨��

    void close_game(Ref* pSender); //�ر���Ϸ

    void goto_helper(Ref* pSender);   //ȥ���ý���

    void goto_setting(Ref* pSender);  //ȥ��������

    void goto_adventure(Ref* psender);  //ȥð��ģʽ

    void goto_nest(Ref* psender);    //ȥ������

    void goto_boss(Ref* psender);  //ȥbossģʽ

    

    
    void CloseCallback(cocos2d::Ref* pSender);
};

#endif //  __Menu_SCENE_H__

