#include "MapChooseScene.h"
#include "MenuScene.h"
#include"LevelSelectionScene.h"
USING_NS_CC;

/*创建场景*/
Scene* MapChooseScene::createScene()
{
    return MapChooseScene::create();
}

/*错误处理*/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MapChooseScene.cpp\n");
}


/*初始化场景*/
bool MapChooseScene::init()
{

    if (!Scene::init())  //初始化场景
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();  //获取分辨率（窗口大小）
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //放置背景图
    auto background = Sprite::create("/MapChooseScene/background.png");
    if (background == nullptr)   //找不到该图片
    {
        problemLoading("'background.png'");
    }
    else
    {
        //放置图片
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        //将mainbackground加入这个场景中
        this->addChild(background);
    }

    //创建菜单
    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);


    //返回主菜单按键
    auto BackHome_Item = MenuItemImage::create("/MapChooseScene/BackHome.png", "/MapChooseScene/BackHomeSelected.png");
    BackHome_Item->setCallback([this](Ref* psender) {//回调函数
       
        auto menu_scene = MenuScene::createScene();//创建主菜单对应Scene
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, menu_scene));//切换到MenuScene
        });
    BackHome_Item->setPosition(Vec2(origin.x + visibleSize.width * 0.05,origin.y + visibleSize.height * 0.95));
    menu->addChild(BackHome_Item);

    //帮助按钮
    auto Helper_Item = MenuItemImage::create("/MapChooseScene/Helper.png", "/MapChooseScene/HelperSelected.png");
    Helper_Item->setCallback([this](Ref* psender) {//回调函数

        auto menu_scene = MenuScene::createScene();//创建主菜单对应Scene
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, menu_scene));//切换到MenuScene
        });
    Helper_Item->setPosition(Vec2(origin.x + visibleSize.width * 0.95, origin.y + visibleSize.height * 0.95));
    menu->addChild(Helper_Item);


    //创建地图所在的层
    auto Map_Layer = Layer::create();
    Map_Layer->setPosition(Vec2::ZERO);
    this->addChild(Map_Layer);


    auto CarrotMap = Sprite::create("/MapChooseScene/carrotmap.png");
    CarrotMap->setPosition(Vec2(origin.x - visibleSize.width / 2 + 10, origin.y + visibleSize.height / 2 - 30));
    Map_Layer->addChild(CarrotMap);

    //创建一个新menu，用于存放地图按键，加入Map_Layer中
    auto menu1 = Menu::create();
    menu1->setPosition(Vec2::ZERO);
    Map_Layer->addChild(menu1);


     /*-----------第一张map---------*/
    auto Map1_Item = MenuItemImage::create("/MapChooseScene/map1.png", "/MapChooseScene/map1.png");
    Map1_Item->setCallback([this](Ref* psender) {//回调函数

        auto LevelSelection = LevelSelectionScene::createScene();//创建主菜单对应Scene
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, LevelSelection));//切换到MenuScene
        });

    if (Map1_Item == nullptr || Map1_Item->getContentSize().width <= 0 || Map1_Item->getContentSize().height <= 0) {
        problemLoading("'Map1.png'");
    }
    else {

        //放置图片
        Map1_Item->setPosition(Vec2(origin.x + visibleSize.width / 2 + 10, origin.y + visibleSize.height / 2 - 30));

        //将第一张地图加入层中
        menu1->addChild(Map1_Item);
    }

    /*-----------第二张map---------*/
    auto Map2_Item = MenuItemImage::create("/MapChooseScene/map2.png", "/MapChooseScene/map2.png");
    Map2_Item->setCallback([this](Ref* psender) {//回调函数
        ;
        //auto menu_scene = MenuScene::createScene();//创建主菜单对应Scene
        //Director::getInstance()->replaceScene(TransitionFade::create(1.0f, menu_scene));//切换到MenuScene
        });

    if (Map2_Item == nullptr || Map2_Item->getContentSize().width <= 0 || Map2_Item->getContentSize().height <= 0) {
        problemLoading("'Map.png'");
    }
    else {
                
        //放置图片
        Map2_Item->setPosition(Vec2(origin.x + visibleSize.width / 2 *3+ 10, origin.y + visibleSize.height / 2 - 30));

        //将第二张地图加入层中
        menu1->addChild(Map2_Item);
    }

    /*-----------第三张map---------*/
    auto Map3_Item = MenuItemImage::create("/MapChooseScene/map3.png", "/MapChooseScene/map3.png");
    Map3_Item->setCallback([this](Ref* psender) {//回调函数
        ;
        // auto menu_scene = MenuScene::createScene();//创建主菜单对应Scene
        //Director::getInstance()->replaceScene(TransitionFade::create(1.0f, menu_scene));//切换到MenuScene
        });

    if (Map3_Item == nullptr || Map3_Item->getContentSize().width <= 0 || Map3_Item->getContentSize().height <= 0) {
        problemLoading("'Map3.png'");
    }
    else {

        //放置图片
        Map3_Item->setPosition(Vec2(origin.x + visibleSize.width / 2 * 5 + 10, origin.y + visibleSize.height / 2 - 30));

        //将第三张地图加入层中
        menu1->addChild(Map3_Item);
    }

    //向左翻页按钮
    auto LeftArrow = MenuItemImage::create("/MapChooseScene/LeftArrow.png", "/MapChooseScene/LeftArrowSelected.png");
    LeftArrow->setCallback([visibleSize, Map_Layer,this](Ref* psender) {//回调函数
        if (Chapter >= 1 ) {
            Chapter--;
            Map_Layer->runAction(MoveBy::create(0.4, Vec2(visibleSize.width, 0)));
        }
    });
    LeftArrow->setPosition(Vec2(origin.x + visibleSize.width * 0.08,origin.y + visibleSize.height / 2));
    menu->addChild(LeftArrow);

    //向右翻页按钮
    auto RightArrow = MenuItemImage::create("/MapChooseScene/RightArrow.png", "/MapChooseScene/RightArrowSelected.png");
    RightArrow->setCallback([visibleSize, Map_Layer, this](Ref* psender) {//回调函数
        if (Chapter <= 2) {
            Map_Layer->runAction(MoveBy::create(0.4, Vec2(-visibleSize.width, 0)));
            Chapter++;
        }
    });
    RightArrow->setPosition(Vec2(origin.x + visibleSize.width * 0.92, origin.y + visibleSize.height / 2));
    menu->addChild(RightArrow);

     
   
    return true;

}

void MapChooseScene::CloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}