
#include"MonsterFactory.h"
#include"FlyMonster.h"
#include"PinkMonster.h"
#include"GreenMonster.h"
USING_NS_CC;
Sprite* MonsterFactory::Produce_Monster(int type)
{
	Sprite* Monster;

	//测试先都生产flymonster
	switch (type) {
		case 0:
			Monster = FlyMonster::createSprite();
			break;
		case 1:
			Monster = FlyMonster::createSprite();
			break;
		case 2:
			Monster = FlyMonster::createSprite();
			break;
	}
		
	
	//返回当前产生的怪物
	return Monster;
}

