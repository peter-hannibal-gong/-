
#ifndef __CarrotFantasy__FLYMONSTER_
#define __CarrotFantasy__FLYMONSTER__

#include "cocos2d.h"
#include"Scene1.h"
class FlyMonster : public cocos2d::Sprite
{
public:

	int speed = 110;
	int Hp = 60;
	int ATK = 1;  //����Ĺ���ֵ
	int value = 14; //��ɱ�����õ�Ǯ


    static Sprite* createSprite();
	
	virtual bool init();

	CREATE_FUNC(FlyMonster);

	void Move(Position p[],int num);  //ͨ��·�������ƶ�

	void Init_Route(Position p[]);   //��ʼ��·��

	void update(float dt);
};
#endif /* defined(__CarrotFantasy__FlyMonster__) */