
#ifndef __CarrotFantasy__TowerFan__
#define __CarrotFantasy__TowerFan__

#include "cocos2d.h"

USING_NS_CC;
class TowerFan : public cocos2d::Sprite
{

	

public:

	int level = 0;  //塔的等级,分别为0、1、2级
	int value[3] = {128,304,512};  //塔的价值（卖出获得的钱）
	int upgradecost[3] = {160,220,260 }; //建造和升级塔的
	int ATK[3] = { 40,55,70 };

	//int AttackRange = 200; //攻击范围，一级塔的攻击范围为200
	//int AttackSpace = 2;//攻击间隔
	
	int range_is_visible = 0; //初始范围和升级、出售界面不可见
	

	//创建精灵
    static Sprite* createSprite();
	
	//初始化
	virtual bool init();

	//宏定义
	CREATE_FUNC(TowerFan);

	//被点击显示范围和等级界面
	void Show_RangeAndGrade(Node* node,int money);

	//隐藏显示范围和等级界面
	void Hide_RangeAndGrade(Node* node);

	//升级
	void Upgrade(Node* node);

	//一次攻击
    void attack(Node* node,cocos2d::Vec2 start , cocos2d::Vec2 end);

	//有目标的情况下攻击
    void AttackTarget(float dt);  

	//选择攻击对象
	void checkAtkTarget(float dt);

	//停止计时器
	void stopschedule();

};
#endif /* defined(__CarrotFantasy__TowerShit__) */