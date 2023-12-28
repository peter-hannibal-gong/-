
#ifndef __CarrotFantasy__PINKMONSTER_
#define __CarrotFantasy__PINKMONSTER__
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include"Scene1.h"
USING_NS_CC;
class PinkMonster : public cocos2d::Sprite
{
public:

	int speed = 70;
	int Hp;
	int ATK = 1;  //怪物的攻击值
	int value = 14; //击杀怪物获得的钱

	ProgressTimer* BloodBar;

    static Sprite* createSprite();
	
	virtual bool init();

	CREATE_FUNC(PinkMonster);

	void Move(Position p[],int num);  //通过路径进行移动

	void Init_Route(Position p[]);   //初始化路径

	void updateHp(float dt);  //更新血量
};
#endif /* defined(__CarrotFantasy__PinkMonster__) */