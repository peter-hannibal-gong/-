
#include "TowerShit.h"
USING_NS_CC;


Sprite* TowerShit::createSprite()
{

    return TowerShit::create();
}


bool TowerShit::init()
{
    if (!Sprite::init()) {
        return false;
    }

    //����ͼƬ
    this->initWithFile("/Theme/Shit/SmallShit.png");
    
    //����֡����
    Vector<SpriteFrame*> frame;
    frame.pushBack(SpriteFrame::create("/Theme/Shit/BigShit.png", Rect(0, 0, 70, 70)));
    frame.pushBack(SpriteFrame::create("/Theme/Shit/BigShit2.png", Rect(0, 0, 70, 70)));
    frame.pushBack(SpriteFrame::create("/Theme/Shit/BigShit.png", Rect(0, 0, 70, 70)));

    float animationdelay = 0.3f;
    auto animation = Animation::createWithSpriteFrames(frame, animationdelay);

    //��ʾ����ѭ��
    int repeatTime = -1;  
    auto animate = Animate::create(animation);
    auto repeatAnimation = RepeatForever::create(animate);

    //���ñ�ǩ���ں���ֹͣ����
    repeatAnimation->setTag(1); 
    this->runAction(repeatAnimation);

    
    this->stopActionByTag(1);  //ֹͣ����
   
    //��ʱ����ÿ1�����һ��update
    //schedule(CC_SCHEDULE_SELECTOR(TowerShit::update),1.0f);

   
    return true;
}

/*�������ʾ��Χ�͵ȼ�����*/
void TowerShit::Show_RangeAndGrade(Node* node,int money)
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
void TowerShit::Hide_RangeAndGrade(Node* node)
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
    if (level != 2) { //û�дﵽ��߼�(�ﵽ��߼�ԭ����û����ʾ��������money)
        Node* n4 = node->getChildByTag(9000 + 100 * i + j);
        Label* UpLevel_Money = static_cast<Label*>(n4);
        node->removeChild(UpLevel_Money);
    }
    //��ʾ����money
    Node* n5 = node->getChildByTag(10000 + 100 * i + j);
    Label* SellTower_Money = static_cast<Label*>(n5);
    node->removeChild(SellTower_Money);

}

/*������������������ͼƬ*/
void TowerShit::Upgrade(Node* node)
{
    level++;

    if (level == 1)
        this->setTexture("/Theme/Shit/MediumShit.png");
    else  if (level == 2)
        this->setTexture("/Theme/Shit/BigShit.png");
  
}

/*������Ĺ���*/
void TowerShit::attack(Node* node)
{
  
    //��ȡ�������ڵ�λ��
    int x = this->getPosition().x;
    int y = this->getPosition().y;

    //ת��Ϊ�������
    int i = 6 - (y / 80);
    int j = (x / 80);

    //��ʷЧ��
    auto TowerShit_attack = Sprite::create("/Theme/Shit/BigShitAttack.png");
    TowerShit_attack->setPosition(Vec2(j * 80 + 40, (6 - i) * 80 + 40));
    node->addChild(TowerShit_attack);

    MoveTo* move1 = MoveTo::create(0.4, Vec2(j * 80 + 200, (6 - i) * 80 + 40)); 
    auto sequence1 = Sequence::create(FadeIn::create(0.05),move1, FadeOut::create(0.05), nullptr);
    TowerShit_attack->runAction(sequence1);

    //����ըʷЧ��
    auto ShitHit = Sprite::create("/Theme/Shit/ShitHit.png");
    ShitHit->setPosition(Vec2(j * 80 + 200, (6 - i) * 80 + 40));
    node->addChild(ShitHit);

    auto sequence2 = Sequence::create(FadeOut::create(0),DelayTime::create(0.4), FadeIn::create(0.1), DelayTime::create(0.3), FadeOut::create(0.1), FadeOut::create(0.1), nullptr);
    ShitHit->runAction(sequence2);

    


}


void TowerShit::update(float dt)
{
    
}

