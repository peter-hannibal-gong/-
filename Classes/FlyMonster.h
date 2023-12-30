
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
	int ATK = 1;  //怪物的攻击值
	int value = 14; //击杀怪物获得的钱
	float delaytime;

	ProgressTimer* BloodBar;

    static Sprite* createSprite();
	
	virtual bool init();

	CREATE_FUNC(FlyMonster);

	void Move(Position p[],int num);  //通过路径进行移动

	void Init_Route(Position p[]);   //初始化路径

	void updateHp(float dt);  //更新血量

	int getHp() ; //获取血量



};
#endif /* defined(__CarrotFantasy__FlyMonster__) */