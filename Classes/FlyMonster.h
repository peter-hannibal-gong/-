
#ifndef __CarrotFantasy__FLYMONSTER_
#define __CarrotFantasy__FLYMONSTER__

#include "cocos2d.h"
#include"Scene1.h"
class FlyMonster : public cocos2d::Sprite
{
public:

	int speed = 110;
	int Hp = 60;
	int ATK = 1;  //怪物的攻击值
	int value = 14; //击杀怪物获得的钱


    static Sprite* createSprite();
	
	virtual bool init();

	CREATE_FUNC(FlyMonster);

	void Move(Position p[],int num);  //通过路径进行移动

	void Init_Route(Position p[]);   //初始化路径

	void update(float dt);
};
#endif /* defined(__CarrotFantasy__FlyMonster__) */