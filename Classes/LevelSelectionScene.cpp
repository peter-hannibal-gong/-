#include "LevelSelectionScene.h"
#include"MapChooseScene.h"
#include"Scene1.h"
USING_NS_CC;

/*创建场景*/
Scene* LevelSelectionScene::createScene()
{
    return LevelSelectionScene::create();
}

/*错误处理*/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames inLevelSelectionScene.cpp\n");
}


/*初始化场景*/
bool LevelSelectionScene::init()
{

    if (!Scene::init())  //初始化场景
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();  //获取分辨率（窗口大小）
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //放置背景图
    auto background = Sprite::create("/LevelSelectionScene/background.png");
    if (background == nullptr)   //找不到该图片
    {
        problemLoading("'/LevelSelectionScene/background.png'");
    }
    else
    {
        //放置图片
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        //将mainbackground加入这个场景中
        this->addChild(background);
    }

    auto LeftCloud = Sprite::create("/LevelSelectionScene/LeftCloud.png");
    if (LeftCloud == nullptr)   //找不到该图片
    {
        problemLoading("'/LevelSelectionScene/LeftCloud.png'");
    }
    else
    {
        //放置图片
        LeftCloud->setPosition(Vec2(origin.x+ LeftCloud->getContentSize().width / 2, origin.y+ LeftCloud->getContentSize().height / 2));

        //将leftcloud加入这个场景中
        this->addChild(LeftCloud);
    }

    auto RightCloud = Sprite::create("/LevelSelectionScene/RightCloud.png");
    if (RightCloud == nullptr)   //找不到该图片
    {
        problemLoading("'/LevelSelectionScene/RightCloud.png'");
    }
    else
    {
        //放置图片
        RightCloud->setPosition(Vec2(visibleSize.width+origin.x- RightCloud->getContentSize().width / 2, origin.y+ RightCloud->getContentSize().height / 2));

        //将rightcloud加入这个场景中
        this->addChild(RightCloud);
    }

    //创建菜单
    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    //返回地图选择界面的按键
    auto Back_Item = MenuItemImage::create("/LevelSelectionScene/Back.png", "/LevelSelectionScene/BackSelected.png");
    Back_Item->setCallback([this](Ref* psender) {//回调函数

        auto map_scene = MapChooseScene::createScene();//创建主菜单对应Scene
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, map_scene));//切换到MenuScene
        });
    Back_Item->setPosition(Vec2(origin.x + visibleSize.width * 0.05, origin.y + visibleSize.height * 0.95));
    menu->addChild(Back_Item);

    //帮助按钮
    auto Helper_Item = MenuItemImage::create("/LevelSelectionScene/Helper.png", "/LevelSelectionScene/HelperSelected.png");
    Helper_Item->setCallback([this](Ref* psender) {//回调函数
        ;   //帮助界面
        //auto helper_scene = MapChooseScene::createScene();//创建主菜单对应Scene
        //Director::getInstance()->replaceScene(TransitionFade::create(1.0f, helper_scene));//切换到MenuScene
        });
    Helper_Item->setPosition(Vec2(origin.x + visibleSize.width * 0.95, origin.y + visibleSize.height * 0.95));
    menu->addChild(Helper_Item);

    //开始游戏按钮
    auto Start_Item = MenuItemImage::create("/LevelSelectionScene/Start.png", "/LevelSelectionScene/StartSelected.png");
    Start_Item->setCallback([this](Ref* psender) {//回调函数
        if (level_number == 1) {
            auto Level1 = Scene1::createScene();//创建第一关对应Scene
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Level1));//切换到Scene1
        }
        //如果为第二关...
        //如果为第三关...
        });
    Start_Item->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height * 0.1));
    menu->addChild(Start_Item);


    //创建每个关卡的概况图所在的层
    Create_Layer1();

    return true;

}

void LevelSelectionScene::Create_Layer1()
{
    //获取分辨率（窗口大小）
    auto visibleSize = Director::getInstance()->getVisibleSize();  
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //创建层，将层加入场景中
    auto layer1 = Layer::create();
    layer1->setPosition(Vec2::ZERO);
    this->addChild(layer1);

    //创建菜单，将菜单加入层中
    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    layer1->addChild(menu);

    //第一关
    auto Level1_Item = MenuItemImage::create("/LevelSelectionScene/Level1.png", "/LevelSelectionScene/Level1.png");
    Level1_Item->setCallback([this](Ref* psender) {//回调函数

        auto Level1 = Scene1::createScene();//创建第一关对应Scene
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Level1));//切换到Scene1
        });
    Level1_Item->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height * 0.53));
    menu->addChild(Level1_Item);


    //第二关
    auto Level2_Item = MenuItemImage::create("/LevelSelectionScene/Level2.png", "/LevelSelectionScene/Level2.png");
    Level2_Item->setCallback([this](Ref* psender) {//回调函数
        
        //auto Level2 = Scene2::createScene();//创建第二关对应Scene
        //Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Level2));//切换到Scene2
        });
    Level2_Item->setPosition(Vec2(origin.x + visibleSize.width * 1.05, origin.y + visibleSize.height * 0.53));
    menu->addChild(Level2_Item);


    //第三关
    auto Level3_Item = MenuItemImage::create("/LevelSelectionScene/Level3.png", "/LevelSelectionScene/Level3.png");
    Level3_Item->setCallback([this](Ref* psender) {//回调函数
        auto visibleSize = Director::getInstance()->getVisibleSize();  //获取分辨率（窗口大小）
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto CountDown_layer = Layer::create();
    CountDown_layer->setPosition(Vec2::ZERO);

    auto word = Label::createWithTTF("UNFINISHED", "fonts/Marker Felt.ttf", 50);
    word->setColor(Color3B::WHITE);
    word->enableOutline(Color4B::BLACK, 1);
    word->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    CountDown_layer->addChild(word);
    CountDown_layer->runAction(Sequence::create(DelayTime::create(1), MoveBy::create(1, Vec2(0, 500)), nullptr));
    this->addChild(CountDown_layer);
        //auto Level3 = Scene3::createScene();//创建第三关对应Scene
        //Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Level3));//切换到Scene3
        });
    Level3_Item->setPosition(Vec2(origin.x + visibleSize.width * 1.6, origin.y + visibleSize.height * 0.53));
    menu->addChild(Level3_Item);


    //滑动事件的监听器
    auto listener4 = EventListenerTouchOneByOne::create();
    listener4->onTouchBegan = [layer1](Touch* touch, Event* event) {
        return true;
    };


    //实现滑动
    listener4->onTouchMoved = [layer1](Touch* touch, Event* event) {
        float distance = touch->getLocation().x - touch->getPreviousLocation().x;
        layer1->setPositionX(layer1->getPositionX() + distance);
    };
    listener4->onTouchEnded = [=](Touch* touch, Event* event) {
        //获取触摸移动横向距离，向左滑动距离为正，向右滑动距离为负
        float distance = touch->getLocation().x - touch->getStartLocation().x;
      
        //若滑动大于四分之一屏幕，则视为滑动翻页
        if (distance > visibleSize.width / 4) {  //向左划页
            if (level_number>=2) {   //在第二页之后才能向左翻页
                level_number--;
                //通过移动层的位置来实现地图的变化
                layer1->runAction(MoveTo::create(0.2, Vec2(origin.x-visibleSize.width*(0.55* level_number-0.55), 0)));
            }
            else  {//当前在第一页，无论怎么向左滑动都回到第一页
                layer1->runAction(MoveTo::create(0.2, Vec2(0 , 0)));
                //音效
            }
        }
        else if (distance < -visibleSize.width / 4) { //向右滑页
            if (level_number <=2) { //在第二页之前才能向右翻页
                level_number++;
                layer1->runAction(MoveTo::create(0.2, Vec2(origin.x -visibleSize.width * (0.55 * level_number - 0.55), 0)));
            }
            else {//当前在第三页，无论怎么向右滑动都回到第三页
                layer1->runAction(MoveTo::create(0.2, Vec2(origin.x -visibleSize.width * 1.1, 0)));
                //音效
            }
        }
        else {//若小于四分之一屏幕，则视为取消翻页
            layer1->runAction(MoveTo::create(0.2, Vec2(origin.x - visibleSize.width * (0.55 * level_number - 0.55), 0)));
                    
        }
    };
    //将事件监听器加入事件分发器
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener4, layer1);
    
}


void LevelSelectionScene::CloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}