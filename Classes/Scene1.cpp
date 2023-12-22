#include "Scene1.h"
USING_NS_CC;

/*������̨*/
Scene* Scene1::createScene()
{
    return Scene1::create();
}

/*�����ж�*/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in Scene1.cpp\n");
}

/*��ʼ��*/
bool Scene1::init()
{

    if (!Scene::init())
    {
        return false;
    }

    //��ȡ�ֱ��ʣ����ڴ�С��
    auto visibleSize = Director::getInstance()->getVisibleSize(); 
    //ԭ��λ��
    Vec2 origin = Director::getInstance()->getVisibleOrigin();



    //��ӱ���
    auto background = Sprite::create("/Theme/Theme1/background.png"); 
    if (background == nullptr)
    {
        problemLoading("'/Theme/Theme1/background.png'");
    }
    else {
        this->addChild(background, 0);
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    }

    // ��ӵ�ͼ
    auto map01 = Sprite::create("/Theme/Theme1/map01.png");
    if (map01 == nullptr)
    {
        problemLoading("'/Theme/Theme1/map01.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        map01->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 80));

        // add the sprite as a child to this layer
        this->addChild(map01, 0);
    }

    //���������ʾ����
    Sprite* grid[7][12];
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 12; j++) {
            //�����Ӽ��볡����
            grid[i][j] = Sprite::create("Grid.png");
            grid[i][j]->setPosition(Vec2(40 + 80 * j, 40 + (6 - i)*80));
            this->addChild(grid[i][j], 2);

            //���ñ�ǩֵ
            grid[i][j]->setTag(i * 100 + j);  

            //����ʾ
            grid[i][j]->setVisible(false); 
          
        }
    }

    auto mouseListener = EventListenerMouse::create();

    mouseListener->onMouseDown = CC_CALLBACK_1(Scene1::onMouseDown, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    return true;
}

/*������ת��Ϊ�������*/
Position Scene1::transition(int x, int y)
{
    Position p;
    p.j = (x / 80) ;
    p.i = 6 - (y / 80);
    return p;
}

/*�������ʾ����*/
void Scene1::onMouseDown(Event* event)
{
   
    //��ȡ�¼�
    EventMouse* e = (EventMouse*)event;
    
    //��ȡ���λ��
    int x = e->getCursorX();
    int y = e->getCursorY();

    //��ǰ������ĸ���λ��
    Position p = transition(x, y);

    //ͨ����ǩ����ȡ��ǰ�ĸ��� 
    Node* n = this->getChildByTag(p.i * 100 + p.j);
    Sprite* Grid_Selcted= static_cast<Sprite*>(n);

    //��yû�г�����ͼ��Χ����ʾ������ڵĸ���
    if (y<560)
        Grid_Selcted->setVisible(true);

    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 12; j++) 
        if (i*100+j != p.i * 100 + p.j){

            //ͨ����ǩ����ȡ��λ�õĸ���
            Node* n = this->getChildByTag(i * 100 + j);
            Sprite* Grid_Selcted = static_cast<Sprite*>(n);

            //����ʾ
            Grid_Selcted->setVisible(false);
        }
    


    //��ʾ�������

    //����һ��layer�����ڴ�������Ĺ���ͼ�꣬���Һ�����������Ƿ���
    auto Buy_Layer = Layer::create();

    auto Tower1 = Sprite::create();
    auto Tower2 = Sprite::create();

    if (money < 100)
        Tower1->setTexture("Theme/Theme1/TBottle0.png");
    else
        Tower1->setTexture("Theme/Theme1/TBottle1.png");

    if (money<120)
        Tower2->setTexture("Theme/Theme1/TShit0.png");
    else
        Tower2->setTexture("Theme/Theme1/TShit1.png");

    int x1= 40 + p.j * 80;
    int y1 = 40 + (6 - p.i) * 80;

    //��ʾƿ�������Ĺ���ͼ��
    Tower1->setPosition(Vec2(x1 - Tower1->getContentSize().width / 2,y1 + Tower1->getContentSize().height));
    Buy_Layer->addChild(Tower1,2);

    //��ʾ��������Ĺ���ͼ��
    Tower2->setPosition(Vec2(x1 + Tower2->getContentSize().width / 2, y1 + Tower2->getContentSize().height));
    Buy_Layer->addChild(Tower2, 2);

    this->addChild(Buy_Layer);

    //���������Ƿ�������
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch* touch, Event* event) {
        return true;
    };
    listener->onTouchEnded = [this, Grid_Selcted, Tower1, Tower2,p,Buy_Layer,x1,y1](Touch* touch, Event* event) {
        //������λ���ڵ�һ������ͼ����
        if (touch->getLocation().x >= Tower1->getPosition().x - Tower1->getContentSize().width / 2 &&
            touch->getLocation().x <= Tower1->getPosition().x + Tower1->getContentSize().width / 2 &&
            touch->getLocation().y >= Tower1->getPosition().y - Tower1->getContentSize().height / 2 &&
            touch->getLocation().y <= Tower1->getPosition().y + Tower1->getContentSize().height / 2) {
            if (money >=100) {//��Ǯ��������

                log("build_tower(position, tower_available[0])");

                //��Ǯ
                money =money - 100;
                //���Ӳ��ɼ�
                Grid_Selcted->setVisible(false);  

                //ȥ������������ͼ��
                this->removeChild(Buy_Layer);

                //��ͼ�ϸõ�Ϊ����
                Map1[p.i][p.j] = TOWER;

                auto Bottle_Tower = Sprite::create("Theme/Bottle/BigBottle.png");
                Bottle_Tower->setPosition(Vec2(x1, y1));
                this->addChild(Bottle_Tower);

            }
        }
        else if (//������λ���ڵڶ�������ͼ����
            touch->getLocation().x >= Tower2->getPosition().x - Tower2->getContentSize().width / 2 &&
            touch->getLocation().x <= Tower2->getPosition().x + Tower2->getContentSize().width / 2 &&
            touch->getLocation().y >= Tower2->getPosition().y - Tower2->getContentSize().height / 2 &&
            touch->getLocation().y <= Tower2->getPosition().y + Tower2->getContentSize().height / 2) {
            if (money >=120) {//��Ǯ��������
                // build_tower(position, tower_available[1]);
                log("build_tower(position, tower_available[1])");

                //��Ǯ
                money =money-120;

                //���Ӳ��ɼ�
                Grid_Selcted->setVisible(false);

                //ȥ������������ͼ��
                this->removeChild(Buy_Layer);

                //��ͼ�ϸõ�Ϊ����
                Map1[p.i][p.j] = TOWER;
            }
        }     
        else {//������λ�ò���ͼ����
            //���Ӳ��ɼ�
            Grid_Selcted->setVisible(false);
            //ȥ������������ͼ��
            this->removeChild(Buy_Layer);

        }
    };
    //�ڹ�����м���
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, Buy_Layer);


}


void Scene1::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
