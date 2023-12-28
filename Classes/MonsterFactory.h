
#ifndef __MONSTER_FACTORY__
#define __MONSTER_FACTORY__
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "Scene1.h"
USING_NS_CC;

#define inverval 1 
//每个怪物产生的间隔为1s


class MonsterFactory:public cocos2d::Node
{
public:
	//通过数组和数量产生怪物
	Sprite* Produce_Monster(int type);
	

};
#endif /* defined(__MONSTER_FACTORY__) */