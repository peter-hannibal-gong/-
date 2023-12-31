#include "TowerFan.h"
#include "FlyMonster.h"
#include "Scene1.h"
#include<vector>
extern std::vector <FlyMonster*> m;  //用于存放怪物
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

    target = nullptr;  //攻击的目标，初始为nullptr
    //Scene* scene = se;

   
    //scene->setName("Scene");

    //设置图片
    this->initWithFile("/Theme/Shit/SmallShit.png");
    

    //每0.2s更新一次攻击目标
    schedule(CC_SCHEDULE_SELECTOR(TowerFan::checkAtkTarget),0.2f);

    //如果目标存在，每0.4秒攻击一次
    schedule(CC_SCHEDULE_SELECTOR(TowerFan::AttackTarget), 1.0f);
   
    return true;
}

void TowerFan::stopschedule()
{
    unschedule(CC_SCHEDULE_SELECTOR(TowerFan::checkAtkTarget));
    unschedule(CC_SCHEDULE_SELECTOR(TowerFan::AttackTarget));
}

/*被点击显示范围和等级界面*/
void TowerFan::Show_RangeAndGrade(Node* node,int money)
{
    //获取炮塔所在的位置
    int x = this->getPosition().x;
    int y = this->getPosition().y;

    //转化为格点坐标
    int i = 6 - (y / 80);
    int j = (x / 80);

    //范围显示 
    auto Range = Sprite::create("/Theme/Tower/AttackRange.png");
    Range->setScale(level*0.5+1);
    Range->setOpacity(150);
    Range->setPosition(Vec2(j * 80 + 40, (6 - i) * 80 + 40));
    Range->setTag(6000 + 100 * i + j);
    node->addChild(Range, 2); 

    //升级显示
    if (level!=2) { //没有达到最高级
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

    //出售显示
    auto SellTower = Sprite::create("/Theme/Tower/SellTower.png");
    SellTower->setPosition(Vec2(j * 80 + 40, (6 - i) * 80 -40));
    node->addChild(SellTower, 2);
    SellTower->setTag(8000 + 100 * i + j);

    //显示升级所需money
    if (level != 2) { //没有达到最高级
        auto UpLevel_Money = Label::createWithTTF(std::to_string(upgradecost[level + 1]), "fonts/Marker Felt.ttf", 20);
        UpLevel_Money->setPosition(Vec2(j * 80 + 50, (6 - i) * 80 + 95));
        node->addChild(UpLevel_Money, 2);
        UpLevel_Money->setTag(9000 + 100 * i + j);
    }
    
    //显示出售money
    auto SellTower_Money = Label::createWithTTF(std::to_string(value[level]), "fonts/Marker Felt.ttf", 20);
    SellTower_Money->setPosition(Vec2(j * 80 + 50, (6 - i) * 80 - 65));
    node->addChild(SellTower_Money, 2);
    SellTower_Money->setTag(10000 + 100 * i + j);

}

/*隐藏范围和等级界面*/
void TowerFan::Hide_RangeAndGrade(Node* node)
{

    //获取炮塔所在的位置
    int x = this->getPosition().x;
    int y = this->getPosition().y;

    //转化为格点坐标
    int i = 6 - (y / 80);
    int j = (x / 80);              

    //移除范围显示
    Node* n1 = node->getChildByTag(6000 + 100 * i + j);
    Sprite* Range = static_cast<Sprite*>(n1);
    Range->setVisible(false);
    node->removeChild(Range);

    //升级显示取消
    Node* n2 = node->getChildByTag(7000 + 100 * i + j);
    Sprite* UpLevel = static_cast<Sprite*>(n2);
    node->removeChild(UpLevel);

    //出售显示取消
    Node* n3 = node->getChildByTag(8000 + 100 * i + j);
    Sprite* SellTower = static_cast<Sprite*>(n3);
    node->removeChild(SellTower);

    //显示升级所需money取消
  
        Node* n4 = node->getChildByTag(9000 + 100 * i + j);
        Label* UpLevel_Money = static_cast<Label*>(n4);
        node->removeChild(UpLevel_Money);
    
    //显示出售money
    Node* n5 = node->getChildByTag(10000 + 100 * i + j);
    Label* SellTower_Money = static_cast<Label*>(n5);
    node->removeChild(SellTower_Money);

}

/*给塔升级，更新塔的图片*/
void TowerFan::Upgrade(Node* node)
{
    level++;

    if (level == 1)
        this->setTexture("/Theme/Shit/MediumShit.png");
    else  if (level == 2)
        this->setTexture("/Theme/Shit/BigShit.png");
  
}

/*更新攻击目标*/
void TowerFan::checkAtkTarget(float dt)
{
   
    //获取范围
    auto Range = Sprite::create("/Theme/Tower/AttackRange.png");
    Range->setScale(level * 0.5 + 1);
    //Node* n1 = se->getChildByTag(6000 + 100 * i + j);
    //Sprite* Range = static_cast<Sprite*>(n1);


    //对于当前选择的目标，要判断他是否在范围内
    if (target!=nullptr)
        if (target->survival == 1) {
            float x = this->getPosition().x;
            float y = this->getPosition().y;

            float x1 = target->getPosition().x;
            float y1 = target->getPosition().y;

            float d = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));

            //如果当前目标出了范围
            if (d > Range->getContentSize().height / 2) {
                target = nullptr;
            }        
        }

    //如果当前没有目标，在怪兽序列中寻找目标
    if (target == nullptr) {
        for (int i = 0; i < m.size(); i++) 
            if (m[i]->survival==1) {  //如果这个怪物存活

                FlyMonster* monster = m[i];

                //获取位置信息
                float x = this->getPosition().x;
                float y = this->getPosition().y;

                float x1 = monster->getPosition().x;
                float y1 = monster->getPosition().y;

                //求怪物和塔之间的距离
                float d = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));

                //如果在范围内，则将其设置为目标
                if (d <= Range->getContentSize().height / 2) {
                    target = monster;
                    return;
                }
            }
    }


}

/*便便塔的攻击特效*/
void TowerFan::attack(Node* node, cocos2d::Vec2 start, cocos2d::Vec2 end)
{

    //获取炮塔所在的位置
    int x = this->getPosition().x;
    int y = this->getPosition().y;

    //转化为格点坐标
    int i = 6 - (y / 80);
    int j = (x / 80);

    //计算需要旋转的度数
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
   
    /*-------------------------------炮塔动作效果--------------------------------*/

    //根据不同的等级选择不同的帧动画
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
   


    /*-------------------------------子弹效果----------------------------------*/

    //飞史效果
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
    //设置角度旋转
    TowerShit_attack->setRotation(r);  

    //移除事件
    auto remove_bullet = CallFunc::create([=]() {
        node->removeChild(TowerShit_attack);
        });
 

    MoveTo* move1 = MoveTo::create(1, end); 
    auto sequence1 = Sequence::create(DelayTime::create(0.1f),FadeIn::create(0.05),move1, FadeOut::create(0.05), remove_bullet, nullptr);
    TowerShit_attack->runAction(sequence1);


    //击中炸史效果
    auto ShitHit = Sprite::create("/Theme/Shit/ShitHit.png");
    ShitHit->setPosition(end);
    node->addChild(ShitHit);

    auto sequence2 = Sequence::create(DelayTime::create(0.1f),FadeOut::create(0),DelayTime::create(1), FadeIn::create(0.1), DelayTime::create(0.3), FadeOut::create(0.1), nullptr);
    ShitHit->runAction(sequence2);

    
}

/*攻击目标*/
void TowerFan::AttackTarget(float dt)
{
    //auto node1 = this->getChildByName("Target");
    //FlyMonster* target = static_cast<FlyMonster*>(node1);

    auto node2 = this->getChildByName("Scene");

    //如果目标存在，则对其进行攻击
    if (target != nullptr) {
        if (target->getHp() > ATK[level])
            target->takedamage(ATK[level]);
        else
            target->takedamage(target->getHp());
        attack(se,this->getPosition(),target->getPosition());
    }
}
