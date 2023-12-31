
#ifndef __CarrotFantasy__TowerFan__
#define __CarrotFantasy__TowerFan__

#include "cocos2d.h"

USING_NS_CC;
class TowerFan : public cocos2d::Sprite
{

	

public:

	int level = 0;  //���ĵȼ�,�ֱ�Ϊ0��1��2��
	int value[3] = {128,304,512};  //���ļ�ֵ��������õ�Ǯ��
	int upgradecost[3] = {160,220,260 }; //�������������
	int ATK[3] = { 40,55,70 };

	//int AttackRange = 200; //������Χ��һ�����Ĺ�����ΧΪ200
	//int AttackSpace = 2;//�������
	
	int range_is_visible = 0; //��ʼ��Χ�����������۽��治�ɼ�
	

	//��������
    static Sprite* createSprite();
	
	//��ʼ��
	virtual bool init();

	//�궨��
	CREATE_FUNC(TowerFan);

	//�������ʾ��Χ�͵ȼ�����
	void Show_RangeAndGrade(Node* node,int money);

	//������ʾ��Χ�͵ȼ�����
	void Hide_RangeAndGrade(Node* node);

	//����
	void Upgrade(Node* node);

	//һ�ι���
    void attack(Node* node,cocos2d::Vec2 start , cocos2d::Vec2 end);

	//��Ŀ�������¹���
    void AttackTarget(float dt);  

	//ѡ�񹥻�����
	void checkAtkTarget(float dt);

	//ֹͣ��ʱ��
	void stopschedule();

};
#endif /* defined(__CarrotFantasy__TowerShit__) */