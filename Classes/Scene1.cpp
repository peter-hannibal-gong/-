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

<<<<<<< HEAD
=======
    // ��ӹ���ľ��
    auto Board = Sprite::create("Board.png");
    if (Board == nullptr)
    {
        problemLoading("'Board.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        Board->setPosition(Vec2(visibleSize.width / 12*2-40 + origin.x, visibleSize.height /7*5+20 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(Board, 0);
    }


    // ��Ӳ˵�ͼƬ
    auto Menu_Sprite = Sprite::create("/Theme/Theme1/menu.png");
    if (Menu_Sprite == nullptr)
    {
        problemLoading("'/Theme/Theme1/menu.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        Menu_Sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height  + origin.y - Menu_Sprite->getContentSize().height / 2));

        // add the sprite as a child to this layer
        this->addChild(Menu_Sprite, 0);
    }

    /*---------------money��ʾ---------------*/

    //��Ǯת��Ϊ�ַ�������32������ʾ
    auto Money_Label = Label::createWithTTF(std::to_string(money), "/fonts/Marker Felt.ttf", 28);
    Money_Label->setName("MoneyLabel");
    //����ê��
    Money_Label->setAnchorPoint(Vec2(0, 0.5));

    Money_Label->setPosition(Vec2(origin.x + visibleSize.width * 0.11,origin.y + visibleSize.height * 0.95));
    this->addChild(Money_Label);


    /*---------------������ʾ---------------*/

    //���������ʾ
    auto Wave_Board = Sprite::create("/Theme/Theme1/Wave_Board.png");
    Wave_Board->setPosition(Vec2(origin.x + visibleSize.width * 0.43,origin.y + visibleSize.height * 0.95));
    this->addChild(Wave_Board);

    //��ǰ������ʾ
    auto Wave_Label = Label::createWithTTF(std::to_string(wave / 10 % 10) + "    " + std::to_string(wave % 10), "/fonts/Marker Felt.ttf", 28);
    Wave_Label->setName("WavesLabel");
    Wave_Label->setColor(Color3B::YELLOW);
    Wave_Label->setPosition(Vec2(origin.x + visibleSize.width * 0.43,origin.y + visibleSize.height * 0.94));
    this->addChild(Wave_Label);

    //�ܲ�����ʾ
    auto TotalWave_Label = Label::createWithTTF("/ " + std::to_string(Total_Wave_Number) + "Waves", "/fonts/Marker Felt.ttf", 28);
    TotalWave_Label->setPosition(Vec2(origin.x + visibleSize.width * 0.55,origin.y + visibleSize.height * 0.94));
    this->addChild(TotalWave_Label);

    /*-------------���ٿ�����ʾ-------------*/
 
    //�������鼰��Ӧ�Ĳ˵���
    auto Normal_Speed_Item = Sprite::create("/Theme/Theme1/NormalSpeed.png");
    auto speed_up_off = MenuItemSprite::create(Normal_Speed_Item, Normal_Speed_Item);

    auto Double_Speed_Item = Sprite::create("/Theme/Theme1/DoubleSpeed.png");
    auto speed_up_on = MenuItemSprite::create(Double_Speed_Item, Double_Speed_Item);

    //�������ٿ��ص��л��˵���
    auto SpeedItemtoggle = MenuItemToggle::createWithCallback([&](Ref* psender) {
        //���˵��������л����ٵ�ģʽ
        if (Acceleration_Switch == 0) {
            Acceleration_Switch = 1;
        }
        else {
            Acceleration_Switch = 0;
        }
        }, speed_up_off, speed_up_on, nullptr);
    //���˵������˵��У��������ʺϵ�λ��
    auto menu = Menu::create(SpeedItemtoggle,nullptr);
    SpeedItemtoggle->setPosition(Vec2(origin.x + visibleSize.width * 0.72, origin.y + visibleSize.height * 0.94));

    //���ò˵������˵����볡����
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);  

    
    /*-------------��ͣ������ʾ-------------*/

    //��������ͣ�С�ͼ��
    auto Pause_Sprite = Sprite::create("/Theme/Theme1/paused.png");
    if (Pause_Sprite == nullptr)
    {
        problemLoading("'/Theme/Theme1/paused.png'");
    }
    else
    {
        Pause_Sprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.95));
        this->addChild(Pause_Sprite);  
        //��ʼΪ���ɼ�
        Pause_Sprite->setVisible(false);
        Pause_Sprite->setScale(1.2);
    }


    //�������鼰��Ӧ�Ĳ˵���
    auto Pause_off_Item = Sprite::create("/Theme/Theme1/PauseOff.png");
    auto Pause_off = MenuItemSprite::create(Pause_off_Item, Pause_off_Item);
    auto Pause_on_Item = Sprite::create("/Theme/Theme1/PauseOn.png");
    auto Pause_on = MenuItemSprite::create(Pause_on_Item, Pause_on_Item);

    //������ͣ���ص��л��˵���
    auto PauseItemtoggle = MenuItemToggle::createWithCallback([=](Ref* psender) {
        //������Ч
        if (Pause_Switch == 0) {
            Pause_Switch = 1;
            //����ͣ�С��ɼ�
            Pause_Sprite->setVisible(true);
            //������ʾ�ر�
            Wave_Board->setVisible(false);
            Wave_Label->setVisible(false);
            TotalWave_Label->setVisible(false);
        }
        else {
            Pause_Switch = 0;
            //����ͣ�С����ɼ�
            Pause_Sprite->setVisible(false);
            //������ʾ����
            Wave_Board->setVisible(true);
            Wave_Label->setVisible(true);
            TotalWave_Label->setVisible(true);
        }
        }, Pause_off, Pause_on, nullptr);

    //���˵�������ں���λ�ã�����˵���
    PauseItemtoggle->setPosition(Vec2(origin.x + visibleSize.width * 0.83,origin.y + visibleSize.height * 0.94));
    menu->addChild(PauseItemtoggle);

    /*-------------ѡ�����ʾ-------------*/
    auto MenuItem = MenuItemImage::create("/Theme/Theme1/MenuItem.png","CloseSelected.png",CC_CALLBACK_1(Scene1::menuCloseCallback, this));
    
    MenuItem->setPosition(Vec2(origin.x + visibleSize.width * 0.88,origin.y + visibleSize.height * 0.94));



    /*-------------����ʱ��-------------*/
>>>>>>> b64f658e5abf13c66906fbb1ba4b6c50bd903416
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

<<<<<<< HEAD
    auto mouseListener = EventListenerMouse::create();

    mouseListener->onMouseDown = CC_CALLBACK_1(Scene1::onMouseDown, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

=======
   
    auto mouseListener = EventListenerMouse::create();

    mouseListener->onMouseDown = CC_CALLBACK_1(Scene1::onMouseDown, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    
   
>>>>>>> b64f658e5abf13c66906fbb1ba4b6c50bd903416
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
    if (y < 560) {   //�����λ�ò��ڲ˵���
        //��ǰ������ĸ���λ��
        Position p = transition(x, y);

        //ͨ����ǩ����ȡ��ǰ�ĸ��� 
        Node* n = this->getChildByTag(p.i * 100 + p.j);
        Sprite* Grid_Selcted = static_cast<Sprite*>(n);

        //��yû�г�����ͼ��Χ����ʾ������ڵĸ���
        Grid_Selcted->setVisible(true);

        for (int i = 0; i < 7; i++)
            for (int j = 0; j < 12; j++)
                if (i * 100 + j != p.i * 100 + p.j) {

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

        if (money < 120)
            Tower2->setTexture("Theme/Theme1/TShit0.png");
        else
            Tower2->setTexture("Theme/Theme1/TShit1.png");

        int x1 = 40 + p.j * 80;
        int y1 = 40 + (6 - p.i) * 80;

        //��ʾƿ�������Ĺ���ͼ��
        Tower1->setPosition(Vec2(x1 - Tower1->getContentSize().width / 2, y1 + Tower1->getContentSize().height));
        Buy_Layer->addChild(Tower1, 2);

<<<<<<< HEAD
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
=======
        //��ʾ��������Ĺ���ͼ��
        Tower2->setPosition(Vec2(x1 + Tower2->getContentSize().width / 2, y1 + Tower2->getContentSize().height));
        Buy_Layer->addChild(Tower2, 2);

        //��layer���볡����
        this->addChild(Buy_Layer);
>>>>>>> b64f658e5abf13c66906fbb1ba4b6c50bd903416

        //���������Ƿ�������
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = [](Touch* touch, Event* event) {
            return true;
        };
        listener->onTouchEnded = [this, Grid_Selcted, Tower1, Tower2, p, Buy_Layer, x1, y1](Touch* touch, Event* event) {

            //������λ���ڵ�һ������ͼ����
            if (touch->getLocation().x >= Tower1->getPosition().x - Tower1->getContentSize().width / 2 &&
                touch->getLocation().x <= Tower1->getPosition().x + Tower1->getContentSize().width / 2 &&
                touch->getLocation().y >= Tower1->getPosition().y - Tower1->getContentSize().height / 2 &&
                touch->getLocation().y <= Tower1->getPosition().y + Tower1->getContentSize().height / 2) {
                if (money >= 100) {//��Ǯ��������

                    log("build_tower(position, tower_available[0])");

                    //��Ǯ
                    money = money - 100;
                    //���Ӳ��ɼ�
                    Grid_Selcted->setVisible(false);

<<<<<<< HEAD
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
=======
                    //ȥ������������ͼ��
                    this->removeChild(Buy_Layer);

                    //��ͼ�ϸõ�Ϊ����
                    Map1[p.i][p.j] = TOWER;

                    //����ƿ������
                    auto Bottle_Tower = Sprite::create("Theme/Bottle/SmallBottle.png");
                    Bottle_Tower->setPosition(Vec2(x1, y1));
                    Bottle_Tower->setTag(x1 * 1000 + y1 * 10);
                    this->addChild(Bottle_Tower);

                }
                else {  //Ǯ����
                    //ȥ������������ͼ��
                    this->removeChild(Buy_Layer);

                }

            }
            else if (//������λ���ڵڶ�������ͼ����
                touch->getLocation().x >= Tower2->getPosition().x - Tower2->getContentSize().width / 2 &&
                touch->getLocation().x <= Tower2->getPosition().x + Tower2->getContentSize().width / 2 &&
                touch->getLocation().y >= Tower2->getPosition().y - Tower2->getContentSize().height / 2 &&
                touch->getLocation().y <= Tower2->getPosition().y + Tower2->getContentSize().height / 2) {
                if (money >= 120) {//��Ǯ��������
                    // build_tower(position, tower_available[1]);
                    log("build_tower(position, tower_available[1])");

                    //��Ǯ
                    money = money - 120;

                    //���Ӳ��ɼ�
                    Grid_Selcted->setVisible(false);

                    //ȥ������������ͼ��
                    this->removeChild(Buy_Layer);

                    //��ͼ�ϸõ�Ϊ����
                    Map1[p.i][p.j] = TOWER;

                    //����������
                    auto Shit_Tower = Sprite::create("Theme/Shit/SmallShit.png");
                    Shit_Tower->setPosition(Vec2(x1, y1));
                    Shit_Tower->setTag(x1 * 10000 + y1 * 100);
                    this->addChild(Shit_Tower);
                }
                else {  //Ǯ����
                    //ȥ������������ͼ��
                    this->removeChild(Buy_Layer);

                }
            }
            else {//������λ�ò���ͼ����
                //���Ӳ��ɼ�
                Grid_Selcted->setVisible(false);
                //ȥ������������ͼ��
                this->removeChild(Buy_Layer);

            }
            return true;
        };
        //��������ͼ�����ڵĲ�
>>>>>>> b64f658e5abf13c66906fbb1ba4b6c50bd903416

        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, Buy_Layer);

    }
}


void Scene1::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
