
#ifndef __CarrotFantasy__TowerShit__
#define __CarrotFantasy__TowerShit__

#include "cocos2d.h"

USING_NS_CC;
class TowerShit : public cocos2d::Sprite
{

	

public:

	int level = 0;  //���ĵȼ�,�ֱ�Ϊ0��1��2��
	int value[3] = {96,272,480};  //���ļ�ֵ��������õ�Ǯ��
	int upgradecost[3] = {120,220,260 }; //�������������

	int AttackRange = 200; //������Χ��һ�����Ĺ�����ΧΪ200
	int AttackSpace = 2;//�������
	
	int range_is_visible = 0; //��ʼ��Χ�����������۽��治�ɼ�
	

	//��������
    static Sprite* createSprite();
	
	//��ʼ��
	virtual bool init();

	//�궨��
	CREATE_FUNC(TowerShit);

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

};
#endif /* defined(__CarrotFantasy__TowerShit__) */