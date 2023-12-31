#pragma once
#ifndef __MAPCHOOSE_SCENE_H__
#define __MAPCHOOSE_SCENE_H__

#include "cocos2d.h"


class MapChooseScene : public cocos2d::Scene
{
private:
    int Chapter = 1; //���浱ǰ�ڵڼ��ŵ�ͼ
public:

    //������������
    static cocos2d::Scene* createScene();

    //��ʼ����������
    virtual bool init();
    
    void goto_helper(cocos2d::Ref* pSender);
    //�ص���������
    void CloseCallback(cocos2d::Ref* pSender);

    //����Scene1����ĺ궨��
    CREATE_FUNC(MapChooseScene);

    
};


#endif // __MAPCHOOSE_H__

