
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

    //设置图片
    this->initWithFile("/Theme/Shit/SmallShit.png");
    
    //设置帧动画
    Vector<SpriteFrame*> frame;
    frame.pushBack(SpriteFrame::create("/Theme/Shit/BigShit.png", Rect(0, 0, 70, 70)));
    frame.pushBack(SpriteFrame::create("/Theme/Shit/BigShit2.png", Rect(0, 0, 70, 70)));
    frame.pushBack(SpriteFrame::create("/Theme/Shit/BigShit.png", Rect(0, 0, 70, 70)));

    float animationdelay = 0.3f;
    auto animation = Animation::createWithSpriteFrames(frame, animationdelay);

    //表示无限循环
    int repeatTime = -1;  
    auto animate = Animate::create(animation);
    auto repeatAnimation = RepeatForever::create(animate);

    //设置标签便于后续停止动作
    repeatAnimation->setTag(1); 
    this->runAction(repeatAnimation);

    
    this->stopActionByTag(1);  //停止动作
   
    //计时器，每1秒进行一次update
    //schedule(CC_SCHEDULE_SELECTOR(TowerShit::update),1.0f);

   
    return true;
}

/*被点击显示范围和等级界面*/
void TowerShit::Show_RangeAndGrade(Node* node,int money)
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
void TowerShit::Hide_RangeAndGrade(Node* node)
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
    if (level != 2) { //没有达到最高级(达到最高级原本就没有显示升级所需money)
        Node* n4 = node->getChildByTag(9000 + 100 * i + j);
        Label* UpLevel_Money = static_cast<Label*>(n4);
        node->removeChild(UpLevel_Money);
    }
    //显示出售money
    Node* n5 = node->getChildByTag(10000 + 100 * i + j);
    Label* SellTower_Money = static_cast<Label*>(n5);
    node->removeChild(SellTower_Money);

}

/*给塔升级，更新塔的图片*/
void TowerShit::Upgrade(Node* node)
{
    level++;

    if (level == 1)
        this->setTexture("/Theme/Shit/MediumShit.png");
    else  if (level == 2)
        this->setTexture("/Theme/Shit/BigShit.png");
  
}

/*便便塔的攻击*/
void TowerShit::attack(Node* node)
{
  
    //获取炮塔所在的位置
    int x = this->getPosition().x;
    int y = this->getPosition().y;

    //转化为格点坐标
    int i = 6 - (y / 80);
    int j = (x / 80);

    //飞史效果
    auto TowerShit_attack = Sprite::create("/Theme/Shit/BigShitAttack.png");
    TowerShit_attack->setPosition(Vec2(j * 80 + 40, (6 - i) * 80 + 40));
    node->addChild(TowerShit_attack);

    MoveTo* move1 = MoveTo::create(0.4, Vec2(j * 80 + 200, (6 - i) * 80 + 40)); 
    auto sequence1 = Sequence::create(FadeIn::create(0.05),move1, FadeOut::create(0.05), nullptr);
    TowerShit_attack->runAction(sequence1);

    //击中炸史效果
    auto ShitHit = Sprite::create("/Theme/Shit/ShitHit.png");
    ShitHit->setPosition(Vec2(j * 80 + 200, (6 - i) * 80 + 40));
    node->addChild(ShitHit);

    auto sequence2 = Sequence::create(FadeOut::create(0),DelayTime::create(0.4), FadeIn::create(0.1), DelayTime::create(0.3), FadeOut::create(0.1), FadeOut::create(0.1), nullptr);
    ShitHit->runAction(sequence2);

    


}


void TowerShit::update(float dt)
{
    
}

