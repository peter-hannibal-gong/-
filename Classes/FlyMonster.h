
#ifndef __CarrotFantasy__FLYMONSTER_
#define __CarrotFantasy__FLYMONSTER__
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include"Scene1.h"
USING_NS_CC;
class FlyMonster : public cocos2d::Sprite
{
public:

	int speed = 70;
	int Hp=100;
	int ATK = 1;  //����Ĺ���ֵ
	int value = 14; //��ɱ�����õ�Ǯ
	float delaytime;

	ProgressTimer* BloodBar;

    static Sprite* createSprite();
	
	virtual bool init();

	CREATE_FUNC(FlyMonster);

	void Move(Position p[],int num);  //ͨ��·�������ƶ�

	void Init_Route(Position p[]);   //��ʼ��·��

	void updateHp(float dt);  //����Ѫ��

	int getHp() ; //��ȡѪ��



};
#endif /* defined(__CarrotFantasy__FlyMonster__) */