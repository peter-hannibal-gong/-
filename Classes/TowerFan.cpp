#include "TowerFan.h"
#include "FlyMonster.h"
#include "Scene1.h"
#include<vector>
extern std::vector <FlyMonster*> m;  //���ڴ�Ź���
extern Scene* se;
static FlyMonster* target=nullptr;

using namespace std;
Sprite* TowerFan::createSprite()
{

    return TowerFan::create();
}


bool TowerFan::init()
{
    if (!Sprite::init()) {
        return false;
    }

    target = nullptr;  //������Ŀ�꣬��ʼΪnullptr
    //Scene* scene = se;

   
    //scene->setName("Scene");

    //����ͼƬ
    this->initWithFile("/Theme/Shit/SmallShit.png");
    

    //ÿ0.2s����һ�ι���Ŀ��
    schedule(CC_SCHEDULE_SELECTOR(TowerFan::checkAtkTarget),0.2f);

    //���Ŀ����ڣ�ÿ0.4�빥��һ��
    schedule(CC_SCHEDULE_SELECTOR(TowerFan::AttackTarget), 1.0f);
   
    return true;
}

void TowerFan::stopschedule()
{
    unschedule(CC_SCHEDULE_SELECTOR(TowerFan::checkAtkTarget));
    unschedule(CC_SCHEDULE_SELECTOR(TowerFan::AttackTarget));
}

/*�������ʾ��Χ�͵ȼ�����*/
void TowerFan::Show_RangeAndGrade(Node* node,int money)
{
    //��ȡ�������ڵ�λ��
    int x = this->getPosition().x;
    int y = this->getPosition().y;

    //ת��Ϊ�������
    int i = 6 - (y / 80);
    int j = (x / 80);

    //��Χ��ʾ 
    auto Range = Sprite::create("/Theme/Tower/AttackRange.png");
    Range->setScale(level*0.5+1);
    Range->setOpacity(150);
    Range->setPosition(Vec2(j * 80 + 40, (6 - i) * 80 + 40));
    Range->setTag(6000 + 100 * i + j);
    node->addChild(Range, 2); 

    //������ʾ
    if (level!=2) { //û�дﵽ��߼�
        Sprite* UpLevel;
        if (money>=this->upgradecost[level+1])
            UpLevel = Sprite::create("/Theme/Tower/CanUpLevel.png");
        else
            UpLevel = Sprite::create("/Theme/Tower/CantUpLevel.png");
        UpLevel->setPosition(Vec2(j * 80 + 40, (6 - i) * 80 + 120));
        node->addChild(UpLevel, 2);
        UpLevel->setTag(7000 + 100 * i + j);
    }
    else {
        auto UpLevel = Sprite::create("/Theme/Tower/ReachHighestLevel.png");
        UpLevel->setPosition(Vec2(j * 80 + 40, (6 - i) * 80 + 120));
        node->addChild(UpLevel, 2);
        UpLevel->setTag(7000 + 100 * i + j);
    }

    //������ʾ
    auto SellTower = Sprite::create("/Theme/Tower/SellTower.png");
    SellTower->setPosition(Vec2(j * 80 + 40, (6 - i) * 80 -40));
    node->addChild(SellTower, 2);
    SellTower->setTag(8000 + 100 * i + j);

    //��ʾ��������money
    if (level != 2) { //û�дﵽ��߼�
        auto UpLevel_Money = Label::createWithTTF(std::to_string(upgradecost[level + 1]), "fonts/Marker Felt.ttf", 20);
        UpLevel_Money->setPosition(Vec2(j * 80 + 50, (6 - i) * 80 + 95));
        node->addChild(UpLevel_Money, 2);
        UpLevel_Money->setTag(9000 + 100 * i + j);
    }
    
    //��ʾ����money
    auto SellTower_Money = Label::createWithTTF(std::to_string(value[level]), "fonts/Marker Felt.ttf", 20);
    SellTower_Money->setPosition(Vec2(j * 80 + 50, (6 - i) * 80 - 65));
    node->addChild(SellTower_Money, 2);
    SellTower_Money->setTag(10000 + 100 * i + j);

}

/*���ط�Χ�͵ȼ�����*/
void TowerFan::Hide_RangeAndGrade(Node* node)
{

    //��ȡ�������ڵ�λ��
    int x = this->getPosition().x;
    int y = this->getPosition().y;

    //ת��Ϊ�������
    int i = 6 - (y / 80);
    int j = (x / 80);              

    //�Ƴ���Χ��ʾ
    Node* n1 = node->getChildByTag(6000 + 100 * i + j);
    Sprite* Range = static_cast<Sprite*>(n1);
    Range->setVisible(false);
    node->removeChild(Range);

    //������ʾȡ��
    Node* n2 = node->getChildByTag(7000 + 100 * i + j);
    Sprite* UpLevel = static_cast<Sprite*>(n2);
    node->removeChild(UpLevel);

    //������ʾȡ��
    Node* n3 = node->getChildByTag(8000 + 100 * i + j);
    Sprite* SellTower = static_cast<Sprite*>(n3);
    node->removeChild(SellTower);

    //��ʾ��������moneyȡ��
  
        Node* n4 = node->getChildByTag(9000 + 100 * i + j);
        Label* UpLevel_Money = static_cast<Label*>(n4);
        node->removeChild(UpLevel_Money);
    
    //��ʾ����money
    Node* n5 = node->getChildByTag(10000 + 100 * i + j);
    Label* SellTower_Money = static_cast<Label*>(n5);
    node->removeChild(SellTower_Money);

}

/*������������������ͼƬ*/
void TowerFan::Upgrade(Node* node)
{
    level++;

    if (level == 1)
        this->setTexture("/Theme/Shit/MediumShit.png");
    else  if (level == 2)
        this->setTexture("/Theme/Shit/BigShit.png");
  
}

/*���¹���Ŀ��*/
void TowerFan::checkAtkTarget(float dt)
{
   
    //��ȡ��Χ
    auto Range = Sprite::create("/Theme/Tower/AttackRange.png");
    Range->setScale(level * 0.5 + 1);
    //Node* n1 = se->getChildByTag(6000 + 100 * i + j);
    //Sprite* Range = static_cast<Sprite*>(n1);


    //���ڵ�ǰѡ���Ŀ�꣬Ҫ�ж����Ƿ��ڷ�Χ��
    if (target!=nullptr)
        if (target->survival == 1) {
            float x = this->getPosition().x;
            float y = this->getPosition().y;

            float x1 = target->getPosition().x;
            float y1 = target->getPosition().y;

            float d = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));

            //�����ǰĿ����˷�Χ
            if (d > Range->getContentSize().height / 2) {
                target = nullptr;
            }        
        }

    //�����ǰû��Ŀ�꣬�ڹ���������Ѱ��Ŀ��
    if (target == nullptr) {
        for (int i = 0; i < m.size(); i++) 
            if (m[i]->survival==1) {  //������������

                FlyMonster* monster = m[i];

                //��ȡλ����Ϣ
                float x = this->getPosition().x;
                float y = this->getPosition().y;

                float x1 = monster->getPosition().x;
                float y1 = monster->getPosition().y;

                //��������֮��ľ���
                float d = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));

                //����ڷ�Χ�ڣ���������ΪĿ��
                if (d <= Range->getContentSize().height / 2) {
                    target = monster;
                    return;
                }
            }
    }


}

/*������Ĺ�����Ч*/
void TowerFan::attack(Node* node, cocos2d::Vec2 start, cocos2d::Vec2 end)
{

    //��ȡ�������ڵ�λ��
    int x = this->getPosition().x;
    int y = this->getPosition().y;

    //ת��Ϊ�������
    int i = 6 - (y / 80);
    int j = (x / 80);

    //������Ҫ��ת�Ķ���
    float dx, dy, r;
    dx = end.x - start.x;
    dy = end.y - start.y;
    r = -atan2f(dy, dx) / 3.14159 * 180;


    auto atk_Effect = Sprite::create();
    atk_Effect->setPosition(Vec2(j*80+40,(6-i)*80+40));
    node->addChild(atk_Effect);

    auto hide = CallFunc::create([=]() {
        this->setVisible(0);
        });
    auto unhide = CallFunc::create([=]() {
        this->setVisible(1);
        });
    auto remove_atk_Effect = CallFunc::create([=]() {
        atk_Effect->removeFromParent();
        });
   
    /*-------------------------------��������Ч��--------------------------------*/

    //���ݲ�ͬ�ĵȼ�ѡ��ͬ��֡����
    Vector<SpriteFrame*> frame;
    switch (level) {
        case 0:
            frame.pushBack(SpriteFrame::create("/Theme/Shit/SmallShit.png", Rect(0, 0, 70, 70)));
            frame.pushBack(SpriteFrame::create("/Theme/Shit/SmallShit3.png", Rect(0, 0, 70, 70)));
            frame.pushBack(SpriteFrame::create("/Theme/Shit/SmallShit2.png", Rect(0, 0, 70, 70)));
            break;
        case 1:
            frame.pushBack(SpriteFrame::create("/Theme/Shit/MediumShit.png", Rect(0, 0, 70, 70)));
            frame.pushBack(SpriteFrame::create("/Theme/Shit/MediumShit3.png", Rect(0, 0, 70, 70)));
            frame.pushBack(SpriteFrame::create("/Theme/Shit/MediumShit2.png", Rect(0, 0, 70, 70)));
            break;
        case 2:
            frame.pushBack(SpriteFrame::create("/Theme/Shit/BigShit.png", Rect(0, 0, 70, 70)));
            frame.pushBack(SpriteFrame::create("/Theme/Shit/BigShit3.png", Rect(0, 0, 70, 70)));
            frame.pushBack(SpriteFrame::create("/Theme/Shit/BigShit2.png", Rect(0, 0, 70, 70)));
            break;

    }
    atk_Effect->runAction(Sequence::create(DelayTime::create(0.1f),hide,Animate::create(Animation::createWithSpriteFrames(frame, 0.25)),unhide, remove_atk_Effect, nullptr));
   


    /*-------------------------------�ӵ�Ч��----------------------------------*/

    //��ʷЧ��
    Sprite* TowerShit_attack;
    switch (level) {
        case 0:
            TowerShit_attack = Sprite::create("/Theme/Shit/SmallShitAttack.png");
            break;
        case 1:
            TowerShit_attack = Sprite::create("/Theme/Shit/MediumShitAttack.png");
            break;
        case 2:
            TowerShit_attack = Sprite::create("/Theme/Shit/BigShitAttack.png");
            break;


    }
      
    TowerShit_attack->setPosition(Vec2(j * 80 + 40, (6 - i) * 80 + 40));
    node->addChild(TowerShit_attack);
    //���ýǶ���ת
    TowerShit_attack->setRotation(r);  

    //�Ƴ��¼�
    auto remove_bullet = CallFunc::create([=]() {
        node->removeChild(TowerShit_attack);
        });
 

    MoveTo* move1 = MoveTo::create(1, end); 
    auto sequence1 = Sequence::create(DelayTime::create(0.1f),FadeIn::create(0.05),move1, FadeOut::create(0.05), remove_bullet, nullptr);
    TowerShit_attack->runAction(sequence1);


    //����ըʷЧ��
    auto ShitHit = Sprite::create("/Theme/Shit/ShitHit.png");
    ShitHit->setPosition(end);
    node->addChild(ShitHit);

    auto sequence2 = Sequence::create(DelayTime::create(0.1f),FadeOut::create(0),DelayTime::create(1), FadeIn::create(0.1), DelayTime::create(0.3), FadeOut::create(0.1), nullptr);
    ShitHit->runAction(sequence2);

    
}

/*����Ŀ��*/
void TowerFan::AttackTarget(float dt)
{
    //auto node1 = this->getChildByName("Target");
    //FlyMonster* target = static_cast<FlyMonster*>(node1);

    auto node2 = this->getChildByName("Scene");

    //���Ŀ����ڣ��������й���
    if (target != nullptr) {
        if (target->getHp() > ATK[level])
            target->takedamage(ATK[level]);
        else
            target->takedamage(target->getHp());
        attack(se,this->getPosition(),target->getPosition());
    }
}
