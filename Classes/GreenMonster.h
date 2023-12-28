
#ifndef __CarrotFantasy__GREENMONSTER_
#define __CarrotFantasy__GREENMONSTER__
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include"Scene1.h"
USING_NS_CC;

class GreenMonster : public cocos2d::Sprite
{
public:

	int speed = 70;
	int Hp;
	int ATK = 1;  //����Ĺ���ֵ
	int value = 14; //��ɱ�����õ�Ǯ

	ProgressTimer* BloodBar;

    static Sprite* createSprite();
	
	virtual bool init();

	CREATE_FUNC(GreenMonster);

	void Move(Position p[],int num);  //ͨ��·�������ƶ�

	void Init_Route(Position p[]);   //��ʼ��·��

	void updateHp(float dt);  //����Ѫ��
};
#endif /* defined(__CarrotFantasy__GreenMonster__) */