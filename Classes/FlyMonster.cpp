
#include "FlyMonster.h"
USING_NS_CC;


Sprite* FlyMonster::createSprite()
{

    return FlyMonster::create();
}


bool FlyMonster::init()
{
    if (!Sprite::init()) {
        return false;
    }

    
    //����֡����
    Vector<SpriteFrame*> frame;
    frame.pushBack(SpriteFrame::create("/Monster/FlyMonster/Monster03.png", Rect(0, 0, 100, 80)));
    frame.pushBack(SpriteFrame::create("/Monster/FlyMonster/Monster04.png", Rect(0, 0, 100, 80)));
   
    float animationdelay = 0.25f;
    auto animation = Animation::createWithSpriteFrames(frame, animationdelay);

    //��ʾ����ѭ��
    int repeatTime = -1;  
    auto animate = Animate::create(animation);
    auto repeatAnimation = RepeatForever::create(animate);

    //���ñ�ǩ���ں���ֹͣ����
    repeatAnimation->setTag(1); 
    this->runAction(repeatAnimation);

    
    //this->stopActionByTag(1);  //ֹͣ����
   
    Position Route[18];

    Init_Route(Route);  //��ʼ��·��
    

    Move(Route,18);
    return true;
}

/*��ʼ��·��*/
void FlyMonster::Init_Route(Position p[])
{

    int Map1[Row_Size][Column_Size] =
    {
    {0,0,0,1,1,1,1,1,1,0,0,0},
    {0,1,0,1,1,1,1,1,1,0,1,0},
    {0,1,0,0,1,0,0,1,0,0,1,0},
    {0,1,1,0,1,1,1,1,0,1,1,0},
    {0,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,0,0,0,0,0,0,0,0,1,1} };


    p[0].i = 1; p[0].j = 1;

    p[1].i = 2; p[1].j = 1;

    p[2].i = 3; p[2].j = 1;

    p[3].i = 4; p[3].j = 1;

    p[4].i = 4; p[4].j = 2;

    p[5].i = 4; p[5].j = 3;

    p[6].i = 4; p[6].j = 4;

    p[7].i = 3; p[7].j = 4;

    p[8].i = 3; p[8].j = 5;

    p[9].i = 3; p[9].j = 6;

    p[10].i = 3; p[10].j = 7;

    p[11].i = 4; p[11].j = 7;

    p[12].i = 4; p[12].j = 8;

    p[13].i = 4; p[13].j = 9;

    p[14].i = 4; p[14].j = 10;

    p[15].i = 3; p[15].j = 10;

    p[16].i = 2; p[16].j = 10;

    p[17].i = 1; p[17].j = 10;

}

/*�ƶ�*/
void FlyMonster::Move(Position p[],int num)
{

    //��ȡ�ֱ��ʣ����ڴ�С��
    auto visibleSize = Director::getInstance()->getVisibleSize();  
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //��ʼλ��
    int x = p[0].j * 80 + 40;
    int y = (6 - p[0].i) * 80 + 40;
    this->setPosition(Vec2(origin.x + x, origin.y + y));

    MoveBy* move[18];

    for (int i = 1; i < num; i++) {
        int x1 = p[i-1].j * 80 + 40;
        int y1 = (6 - p[i-1].i) * 80 + 40;

        int x2 = p[i].j * 80 + 40;
        int y2 = (6 - p[i].i) * 80 + 40;

        move[i] = MoveBy::create(40.0/speed, Vec2(x2 - x1, y2 - y1));
   
    }
    //DelayTime::create(3)
    auto move1 = MoveTo::create(3, Vec2(origin.x + x, origin.y + y));

    //�ƶ��������յ�󵭳�
    auto sequence = Sequence::create(move1,move[1],move[2],move[3],move[4],move[5],move[6],
        move[7],move[8],move[9],move[10],move[11],move[12],move[13],move[14],move[15],
        move[16],move[17], FadeOut::create(0.05), nullptr);

    this->runAction(RepeatForever::create(sequence));

   
    //int i = 6 - (this->getPosition().y / 80);
    //int j = (this->getPosition().x / 80);
    
    //auto move1=MoveTo::create(40.0 / speed, Vec2(p[num - 1].j*80+40, (6-p[num - 1].i)*80+40));
    //this->runAction(move1);

}

/*ʵʱ����Ѫ��ֵ*/
void FlyMonster::update(float dt)
{
    


}