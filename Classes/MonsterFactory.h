
#ifndef __MONSTER_FACTORY__
#define __MONSTER_FACTORY__
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "Scene1.h"
USING_NS_CC;

#define inverval 1 
//ÿ����������ļ��Ϊ1s


class MonsterFactory:public cocos2d::Node
{
public:
	//ͨ�������������������
	Sprite* Produce_Monster(int type);
	

};
#endif /* defined(__MONSTER_FACTORY__) */