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

    auto mouseListener = EventListenerMouse::create();

    mouseListener->onMouseDown = CC_CALLBACK_1(Scene1::onMouseDown, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

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

    //当前鼠标点击的格子位置
    Position p = transition(x, y);

    //通过标签来获取当前的格子 
    Node* n = this->getChildByTag(p.i * 100 + p.j);
    Sprite* Grid_Selcted= static_cast<Sprite*>(n);

    //当y没有超过地图范围，显示鼠标所在的格子
    if (y<560)
        Grid_Selcted->setVisible(true);

    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 12; j++) 
        if (i*100+j != p.i * 100 + p.j){

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

    if (money<120)
        Tower2->setTexture("Theme/Theme1/TShit0.png");
    else
        Tower2->setTexture("Theme/Theme1/TShit1.png");

    int x1= 40 + p.j * 80;
    int y1 = 40 + (6 - p.i) * 80;

    //显示瓶子炮塔的购买图标
    Tower1->setPosition(Vec2(x1 - Tower1->getContentSize().width / 2,y1 + Tower1->getContentSize().height));
    Buy_Layer->addChild(Tower1,2);

    //显示便便炮塔的购买图标
    Tower2->setPosition(Vec2(x1 + Tower2->getContentSize().width / 2, y1 + Tower2->getContentSize().height));
    Buy_Layer->addChild(Tower2, 2);

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

                log("build_tower(position, tower_available[0])");

                //花钱
                money =money - 100;
                //格子不可见
                Grid_Selcted->setVisible(false);  

                //去除购买炮塔的图标
                this->removeChild(Buy_Layer);

                //地图上该点为炮塔
                Map1[p.i][p.j] = TOWER;

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


}


void Scene1::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
