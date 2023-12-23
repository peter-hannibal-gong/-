#include "Scene1.h"
USING_NS_CC;

/*创建舞台*/
Scene* Scene1::createScene()
{
    return Scene1::create();
}

/*错误判断*/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in Scene1.cpp\n");
}

/*初始化*/
bool Scene1::init()
{

    if (!Scene::init())
    {
        return false;
    }

    //获取分辨率（窗口大小）
    auto visibleSize = Director::getInstance()->getVisibleSize(); 
    //原点位置
    Vec2 origin = Director::getInstance()->getVisibleOrigin();



    //添加背景
    auto background = Sprite::create("/Theme/Theme1/background.png"); 
    if (background == nullptr)
    {
        problemLoading("'/Theme/Theme1/background.png'");
    }
    else {
        this->addChild(background, 0);
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    }

    // 添加地图
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
    // 添加怪物木牌
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


    // 添加菜单图片
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

    /*---------------money显示---------------*/

    //将钱转化为字符串，用32号字显示
    auto Money_Label = Label::createWithTTF(std::to_string(money), "/fonts/Marker Felt.ttf", 28);
    Money_Label->setName("MoneyLabel");
    //设置锚点
    Money_Label->setAnchorPoint(Vec2(0, 0.5));

    Money_Label->setPosition(Vec2(origin.x + visibleSize.width * 0.11,origin.y + visibleSize.height * 0.95));
    this->addChild(Money_Label);


    /*---------------波数显示---------------*/

    //波数面板显示
    auto Wave_Board = Sprite::create("/Theme/Theme1/Wave_Board.png");
    Wave_Board->setPosition(Vec2(origin.x + visibleSize.width * 0.43,origin.y + visibleSize.height * 0.95));
    this->addChild(Wave_Board);

    //当前波数显示
    auto Wave_Label = Label::createWithTTF(std::to_string(wave / 10 % 10) + "    " + std::to_string(wave % 10), "/fonts/Marker Felt.ttf", 28);
    Wave_Label->setName("WavesLabel");
    Wave_Label->setColor(Color3B::YELLOW);
    Wave_Label->setPosition(Vec2(origin.x + visibleSize.width * 0.43,origin.y + visibleSize.height * 0.94));
    this->addChild(Wave_Label);

    //总波数显示
    auto TotalWave_Label = Label::createWithTTF("/ " + std::to_string(Total_Wave_Number) + "Waves", "/fonts/Marker Felt.ttf", 28);
    TotalWave_Label->setPosition(Vec2(origin.x + visibleSize.width * 0.55,origin.y + visibleSize.height * 0.94));
    this->addChild(TotalWave_Label);

    /*-------------倍速开关显示-------------*/
 
    //创建精灵及对应的菜单项
    auto Normal_Speed_Item = Sprite::create("/Theme/Theme1/NormalSpeed.png");
    auto speed_up_off = MenuItemSprite::create(Normal_Speed_Item, Normal_Speed_Item);

    auto Double_Speed_Item = Sprite::create("/Theme/Theme1/DoubleSpeed.png");
    auto speed_up_on = MenuItemSprite::create(Double_Speed_Item, Double_Speed_Item);

    //创建倍速开关的切换菜单项
    auto SpeedItemtoggle = MenuItemToggle::createWithCallback([&](Ref* psender) {
        //若菜单项被点击，切换倍速的模式
        if (Acceleration_Switch == 0) {
            Acceleration_Switch = 1;
        }
        else {
            Acceleration_Switch = 0;
        }
        }, speed_up_off, speed_up_on, nullptr);
    //将菜单项加入菜单中，放置在适合的位置
    auto menu = Menu::create(SpeedItemtoggle,nullptr);
    SpeedItemtoggle->setPosition(Vec2(origin.x + visibleSize.width * 0.72, origin.y + visibleSize.height * 0.94));

    //放置菜单，将菜单加入场景中
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);  

    
    /*-------------暂停按键显示-------------*/

    //创建“暂停中”图标
    auto Pause_Sprite = Sprite::create("/Theme/Theme1/paused.png");
    if (Pause_Sprite == nullptr)
    {
        problemLoading("'/Theme/Theme1/paused.png'");
    }
    else
    {
        Pause_Sprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.95));
        this->addChild(Pause_Sprite);  
        //初始为不可见
        Pause_Sprite->setVisible(false);
        Pause_Sprite->setScale(1.2);
    }


    //创建精灵及对应的菜单项
    auto Pause_off_Item = Sprite::create("/Theme/Theme1/PauseOff.png");
    auto Pause_off = MenuItemSprite::create(Pause_off_Item, Pause_off_Item);
    auto Pause_on_Item = Sprite::create("/Theme/Theme1/PauseOn.png");
    auto Pause_on = MenuItemSprite::create(Pause_on_Item, Pause_on_Item);

    //创建暂停开关的切换菜单项
    auto PauseItemtoggle = MenuItemToggle::createWithCallback([=](Ref* psender) {
        //播放音效
        if (Pause_Switch == 0) {
            Pause_Switch = 1;
            //“暂停中”可见
            Pause_Sprite->setVisible(true);
            //波数显示关闭
            Wave_Board->setVisible(false);
            Wave_Label->setVisible(false);
            TotalWave_Label->setVisible(false);
        }
        else {
            Pause_Switch = 0;
            //“暂停中”不可见
            Pause_Sprite->setVisible(false);
            //波数显示开启
            Wave_Board->setVisible(true);
            Wave_Label->setVisible(true);
            TotalWave_Label->setVisible(true);
        }
        }, Pause_off, Pause_on, nullptr);

    //将菜单项放置在合适位置，加入菜单中
    PauseItemtoggle->setPosition(Vec2(origin.x + visibleSize.width * 0.83,origin.y + visibleSize.height * 0.94));
    menu->addChild(PauseItemtoggle);

    /*-------------选项按键显示-------------*/
    auto MenuItem = MenuItemImage::create("/Theme/Theme1/MenuItem.png","CloseSelected.png",CC_CALLBACK_1(Scene1::menuCloseCallback, this));
    
    MenuItem->setPosition(Vec2(origin.x + visibleSize.width * 0.88,origin.y + visibleSize.height * 0.94));



    /*-------------触摸时间-------------*/
>>>>>>> b64f658e5abf13c66906fbb1ba4b6c50bd903416
    //触摸格点显示格子
    Sprite* grid[7][12];
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 12; j++) {
            //将格子加入场景中
            grid[i][j] = Sprite::create("Grid.png");
            grid[i][j]->setPosition(Vec2(40 + 80 * j, 40 + (6 - i)*80));
            this->addChild(grid[i][j], 2);

            //设置标签值
            grid[i][j]->setTag(i * 100 + j);  

            //不显示
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

/*将坐标转化为格点坐标*/
Position Scene1::transition(int x, int y)
{
    Position p;
    p.j = (x / 80) ;
    p.i = 6 - (y / 80);
    return p;
}

/*鼠标点击显示格子*/
void Scene1::onMouseDown(Event* event)
{

    //获取事件
    EventMouse* e = (EventMouse*)event;
    
    //获取鼠标位置
    int x = e->getCursorX();
    int y = e->getCursorY();
    if (y < 560) {   //点击的位置不在菜单栏
        //当前鼠标点击的格子位置
        Position p = transition(x, y);

        //通过标签来获取当前的格子 
        Node* n = this->getChildByTag(p.i * 100 + p.j);
        Sprite* Grid_Selcted = static_cast<Sprite*>(n);

        //当y没有超过地图范围，显示鼠标所在的格子
        Grid_Selcted->setVisible(true);

        for (int i = 0; i < 7; i++)
            for (int j = 0; j < 12; j++)
                if (i * 100 + j != p.i * 100 + p.j) {

                    //通过标签来获取该位置的格子
                    Node* n = this->getChildByTag(i * 100 + j);
                    Sprite* Grid_Selcted = static_cast<Sprite*>(n);

                    //不显示
                    Grid_Selcted->setVisible(false);
                }



        //显示购买界面

        //创建一个layer，用于存放炮塔的购买图标，并且后续方便监听是否点击
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

        //显示瓶子炮塔的购买图标
        Tower1->setPosition(Vec2(x1 - Tower1->getContentSize().width / 2, y1 + Tower1->getContentSize().height));
        Buy_Layer->addChild(Tower1, 2);

<<<<<<< HEAD
    this->addChild(Buy_Layer);

    //监听器，是否购买炮塔
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch* touch, Event* event) {
        return true;
    };
    listener->onTouchEnded = [this, Grid_Selcted, Tower1, Tower2,p,Buy_Layer,x1,y1](Touch* touch, Event* event) {
        //若按下位置在第一个炮塔图标内
        if (touch->getLocation().x >= Tower1->getPosition().x - Tower1->getContentSize().width / 2 &&
            touch->getLocation().x <= Tower1->getPosition().x + Tower1->getContentSize().width / 2 &&
            touch->getLocation().y >= Tower1->getPosition().y - Tower1->getContentSize().height / 2 &&
            touch->getLocation().y <= Tower1->getPosition().y + Tower1->getContentSize().height / 2) {
            if (money >=100) {//若钱够，则建造
=======
        //显示便便炮塔的购买图标
        Tower2->setPosition(Vec2(x1 + Tower2->getContentSize().width / 2, y1 + Tower2->getContentSize().height));
        Buy_Layer->addChild(Tower2, 2);

        //将layer加入场景中
        this->addChild(Buy_Layer);
>>>>>>> b64f658e5abf13c66906fbb1ba4b6c50bd903416

        //监听器，是否购买炮塔
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = [](Touch* touch, Event* event) {
            return true;
        };
        listener->onTouchEnded = [this, Grid_Selcted, Tower1, Tower2, p, Buy_Layer, x1, y1](Touch* touch, Event* event) {

            //若按下位置在第一个炮塔图标内
            if (touch->getLocation().x >= Tower1->getPosition().x - Tower1->getContentSize().width / 2 &&
                touch->getLocation().x <= Tower1->getPosition().x + Tower1->getContentSize().width / 2 &&
                touch->getLocation().y >= Tower1->getPosition().y - Tower1->getContentSize().height / 2 &&
                touch->getLocation().y <= Tower1->getPosition().y + Tower1->getContentSize().height / 2) {
                if (money >= 100) {//若钱够，则建造

                    log("build_tower(position, tower_available[0])");

                    //花钱
                    money = money - 100;
                    //格子不可见
                    Grid_Selcted->setVisible(false);

<<<<<<< HEAD
                auto Bottle_Tower = Sprite::create("Theme/Bottle/BigBottle.png");
                Bottle_Tower->setPosition(Vec2(x1, y1));
                this->addChild(Bottle_Tower);

            }
        }
        else if (//若按下位置在第二个炮塔图标内
            touch->getLocation().x >= Tower2->getPosition().x - Tower2->getContentSize().width / 2 &&
            touch->getLocation().x <= Tower2->getPosition().x + Tower2->getContentSize().width / 2 &&
            touch->getLocation().y >= Tower2->getPosition().y - Tower2->getContentSize().height / 2 &&
            touch->getLocation().y <= Tower2->getPosition().y + Tower2->getContentSize().height / 2) {
            if (money >=120) {//若钱够，则建造
                // build_tower(position, tower_available[1]);
                log("build_tower(position, tower_available[1])");

                //花钱
                money =money-120;

                //格子不可见
                Grid_Selcted->setVisible(false);

                //去除购买炮塔的图标
                this->removeChild(Buy_Layer);

                //地图上该点为炮塔
                Map1[p.i][p.j] = TOWER;
            }
        }     
        else {//若按下位置不在图标内
            //格子不可见
            Grid_Selcted->setVisible(false);
            //去除购买炮塔的图标
            this->removeChild(Buy_Layer);

        }
    };
    //在购买层中监听
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, Buy_Layer);
=======
                    //去除购买炮塔的图标
                    this->removeChild(Buy_Layer);

                    //地图上该点为炮塔
                    Map1[p.i][p.j] = TOWER;

                    //建造瓶子炮塔
                    auto Bottle_Tower = Sprite::create("Theme/Bottle/SmallBottle.png");
                    Bottle_Tower->setPosition(Vec2(x1, y1));
                    Bottle_Tower->setTag(x1 * 1000 + y1 * 10);
                    this->addChild(Bottle_Tower);

                }
                else {  //钱不够
                    //去除购买炮塔的图标
                    this->removeChild(Buy_Layer);

                }

            }
            else if (//若按下位置在第二个炮塔图标内
                touch->getLocation().x >= Tower2->getPosition().x - Tower2->getContentSize().width / 2 &&
                touch->getLocation().x <= Tower2->getPosition().x + Tower2->getContentSize().width / 2 &&
                touch->getLocation().y >= Tower2->getPosition().y - Tower2->getContentSize().height / 2 &&
                touch->getLocation().y <= Tower2->getPosition().y + Tower2->getContentSize().height / 2) {
                if (money >= 120) {//若钱够，则建造
                    // build_tower(position, tower_available[1]);
                    log("build_tower(position, tower_available[1])");

                    //花钱
                    money = money - 120;

                    //格子不可见
                    Grid_Selcted->setVisible(false);

                    //去除购买炮塔的图标
                    this->removeChild(Buy_Layer);

                    //地图上该点为炮塔
                    Map1[p.i][p.j] = TOWER;

                    //建造便便炮塔
                    auto Shit_Tower = Sprite::create("Theme/Shit/SmallShit.png");
                    Shit_Tower->setPosition(Vec2(x1, y1));
                    Shit_Tower->setTag(x1 * 10000 + y1 * 100);
                    this->addChild(Shit_Tower);
                }
                else {  //钱不够
                    //去除购买炮塔的图标
                    this->removeChild(Buy_Layer);

                }
            }
            else {//若按下位置不在图标内
                //格子不可见
                Grid_Selcted->setVisible(false);
                //去除购买炮塔的图标
                this->removeChild(Buy_Layer);

            }
            return true;
        };
        //监听购买图标所在的层
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
