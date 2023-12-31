
#include "carrot.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using  namespace ui;


Sprite* Carrot::createSprite()
{

    return Carrot::create();
}

/*初始化*/
bool Carrot::init()
{
    if (!Sprite::init()) {
        return false;
    }

    this->initWithFile("Carrot/Carrot10.png");
    this->setScale(1);
    //创建生命值血条
    auto HpBarBG = Sprite::create("/Monster/BloodBarBg.png");
    HpBarBG->setPosition(Vec2(getContentSize().width / 2 +5, getContentSize().height / 2 + 35));
    HpBarBG->setScale(0.4);
    addChild(HpBarBG);

    BloodBar = ProgressTimer::create(Sprite::create("/Monster/BloodBar.png"));
    BloodBar->setType(ProgressTimer::Type::BAR);
    BloodBar->setMidpoint(Vec2(0, 0.5));
    BloodBar->setBarChangeRate(Vec2(1, 0));
    BloodBar->setScale(0.4);
    BloodBar->setPosition(Vec2(HpBarBG->getPosition()));

    addChild(BloodBar, 2);
    //设置血条初始值
    BloodBar->setPercentage(100.0f);

    //每0.2秒更新一次萝卜的血量
    schedule(CC_SCHEDULE_SELECTOR(Carrot::updateHp), 0.2f);

    return true;
}

/*通过计算到达终点的怪物个数设置血量*/
bool Carrot::SetHp(int damage)
{
    if (damage >= 10)
        Hp = 0;
    else
        Hp = Hp - damage;

    if (Hp == 0)
        return true;
    else
        return false;
}


/*实时更新血量值和萝卜形象*/
void Carrot::updateHp(float dt)
{

    //Hp = Hp - 1;
    if (Hp <= 0) {
        unschedule(CC_SCHEDULE_SELECTOR(Carrot::update));
        //this->setVisible(false);
        //removeFromParent();//让怪消失
    }
    BloodBar->setPercentage(float(Hp*10));

    switch (Hp) {
        case (10):
            this->setTexture("/Carrot/Carrot10.png");
            break;
        case (9):
            this->setTexture("/Carrot/Carrot9.png");
            break;
        case (8):
            this->setTexture("/Carrot/Carrot7-8.png");
            break;
        case (7):
            this->setTexture("/Carrot/Carrot7-8.png");
            break;
        case (6):
            this->setTexture("/Carrot/Carrot5-6.png");
            break;
        case (5):
            this->setTexture("/Carrot/Carrot5-6.png");
            break;
        case (4):
            this->setTexture("/Carrot/Carrot4.png");
            break;
        case (3):
            this->setTexture("/Carrot/Carrot3.png");
            break;
        case (2):
            this->setTexture("/Carrot/Carrot2.png");
            break;
        case (1):
            this->setTexture("/Carrot/Carrot1.png");
            break;

    }
   
}


