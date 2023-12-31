#include "MenuScene.h"
#include "Helperb.h"
#include "Helpera.h"
#include "Helper.h"
#include"LevelSelectionScene.h"
#include "music.h"
USING_NS_CC;

/*创建场景*/
Scene* Helper::createScene()
{
    return Helper::create();
}

/*错误处理*/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in Helper.cpp\n");
}


/*初始化场景*/
bool Helper::init()
{
    if (!Scene::init())  //初始化场景
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();  //获取分辨率（窗口大小）
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //放置背景图
    auto mainbackground = Sprite::create("/HelperScene/help_3-hd_bg.png");
    if (mainbackground == nullptr)   //找不到该图片
    {
        problemLoading("'mainbackground.png'");
    }
    else
    { 
        //放置图片
        mainbackground->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y )); 

        //将mainbackground加入这个场景中
        this->addChild(mainbackground, 0);   
    }
    //返回按钮
    auto backItem = MenuItemImage::create(  //按钮
        "/HelperScene/help_1-hd_67.PNG",
        "/HelperScene/help_1-hd_38.PNG",
        CC_CALLBACK_1(Helper::CloseCallback, this));

    if (backItem == nullptr ||
        backItem->getContentSize().width <= 0 ||
        backItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");  //出现错误
    }
    else
    {
        backItem->setAnchorPoint(Vec2(0, 1));
        backItem->setScale(1.2);
        backItem->setPosition(Vec2(0, visibleSize.height));
        // create menu, it's an autorelease object
        auto menu = Menu::create(backItem, NULL);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu, 1);
    }
    //顶部装饰
    auto xuanxiang = Sprite::create("/HelperScene/help_1-hd_33.PNG");
    if (xuanxiang == nullptr)
    {
        problemLoading("'setting02-hd_45.png'");
    }
    else
    {
       
        xuanxiang->setAnchorPoint(Vec2(0.5, 1));
        xuanxiang->setPosition(Vec2(visibleSize.width / 2-xuanxiang->getContentSize().width + origin.x, -28 + visibleSize.height + origin.y));
        this->addChild(xuanxiang, 0);
    }
    auto xuanxiang1 = MenuItemImage::create(  //按钮
        "/HelperScene/help_1-hd_71_normal.PNG",
        "/HelperScene/help_1-hd_71.PNG",
        CC_CALLBACK_1(Helper::goto_helper1, this));

    if (xuanxiang1 == nullptr ||
        xuanxiang1->getContentSize().width <= 0 ||
        xuanxiang1->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");  //出现错误
    }
    else
    {
        xuanxiang1->setScale(1.5);
        xuanxiang1->setAnchorPoint(Vec2(0.5, 1));
        xuanxiang1->setPosition(Vec2(visibleSize.width / 2 + origin.x, -20 + visibleSize.height + origin.y));
        // create menu, it's an autorelease object
        auto menu = Menu::create(xuanxiang1, NULL);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu, 1);
    }
    auto xuanxiang2 = MenuItemImage::create(  //按钮
        "/HelperScene/help_1-hd_66_normal.PNG",
        "/HelperScene/help_1-hd_66.PNG",
        CC_CALLBACK_1(Helper::goto_helper2, this));
    if (xuanxiang2 == nullptr ||
        xuanxiang2->getContentSize().width <= 0 ||
        xuanxiang2->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");  //出现错误
    }
    else
    {
        xuanxiang2->setScale(1.5);
        xuanxiang2->setAnchorPoint(Vec2(0.5, 1));
        xuanxiang2->setPosition(Vec2(visibleSize.width / 2 + xuanxiang2->getContentSize().width + origin.x, -17 + visibleSize.height + origin.y));
        // create menu, it's an autorelease object
        auto menu = Menu::create(xuanxiang2, NULL);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu, 1);
    }

    //底部装饰
    auto bottom = Sprite::create("/HelperScene/help_1-hd_0.PNG");
    if (bottom == nullptr)   //找不到该图片
    {
        problemLoading("'bottom.png'");
    }
    else
    {
        //放置图片
        bottom->setPosition(Vec2(origin.x + visibleSize.width / 2 + 13, origin.y + 35));

        //将怪物加入场景中
        this->addChild(bottom);
    }
    auto num_max = Sprite::create("/HelperScene/num_4.png");
    if (num_max == nullptr)   //找不到该图片
    {
        problemLoading("'num_4.png'");
    }
    else
    {
        //放置图片
        num_max->setPosition(Vec2(origin.x + visibleSize.width / 2 + 10, origin.y + 35));
        this->addChild(num_max);
    }
    auto xiegang = Sprite::create("/HelperScene/num_-1.png");
    if (xiegang == nullptr)   //找不到该图片
    {
        problemLoading("'num_-1.png'");
    }
    else
    {
        //放置图片
        xiegang->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 35));
        this->addChild(xiegang);
    }
    auto num1 = Sprite::create("/HelperScene/num_1.png");
    if (num1 == nullptr)   //找不到该图片
    {
        problemLoading("'num1.png'");
    }
    else
    {
        //放置图片
        num1->setPosition(Vec2(origin.x + visibleSize.width / 2-10, origin.y + 35));
        this->addChild(num1);
    }
    auto num2 = Sprite::create("/HelperScene/num_2.png");
    if (num2 == nullptr)   //找不到该图片
    {
        problemLoading("'num2.png'");
    }
    else
    {
        //放置图片
        //num2->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 35));
        this->addChild(num2);
    }
    auto num3 = Sprite::create("/HelperScene/num_3.png");
    if (num3 == nullptr)   //找不到该图片
    {
        problemLoading("'num3.png'");
    }
    else
    {
        //放置图片
        //num3->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 35));
        this->addChild(num3);
    }
    auto num4 = Sprite::create("/HelperScene/num_4.png");
    if (num4 == nullptr)   //找不到该图片
    {
        problemLoading("'num4.png'");
    }
    else
    {
        //放置图片
        //num4->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 35));
        this->addChild(num4);
    }
    

    //创建地图所在的层
    auto Map_Layer = Layer::create();
    Map_Layer->setPosition(Vec2::ZERO);
    this->addChild(Map_Layer);


    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    //创建一个新menu，用于存放地图按键，加入Map_Layer中
    auto menu1 = Menu::create();
    menu1->setPosition(Vec2::ZERO);
    Map_Layer->addChild(menu1);

    //图鉴的位置
    

    /*-----------第一张map---------*/
    auto Map0_Item = MenuItemImage::create("/HelperScene/help_3-hd_1.png", "/HelperScene/help_3-hd_1.png");
    Map0_Item->setCallback([this](Ref* psender) {; });
    if (Map0_Item == nullptr || Map0_Item->getContentSize().width <= 0 || Map0_Item->getContentSize().height <= 0) {
        problemLoading("'help_3-hd_1.png'");
    }
    else {

        //放置图片
        Map0_Item->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 +30));

        //将第一张地图加入层中
        menu1->addChild(Map0_Item);
    }

    auto Word0_Item = MenuItemImage::create("/HelperScene/help_1-hd_73.PNG", "/HelperScene/help_1-hd_73.PNG");
    Word0_Item->setCallback([this](Ref* psender) {; });
    if (Word0_Item == nullptr || Word0_Item->getContentSize().width <= 0 || Word0_Item->getContentSize().height <= 0) {
        problemLoading("'help_1-hd_73.PNG'");
    }
    else {

        //放置图片
        Word0_Item->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 -160));

        //将第一张地图加入层中
        menu1->addChild(Word0_Item);
    }

    /*-----------第二张map---------*/
    auto Map1_Item = MenuItemImage::create("/HelperScene/help_3-hd_2.png", "/HelperScene/help_3-hd_2.png");
    Map1_Item->setCallback([this](Ref* psender) {; });

    if (Map1_Item == nullptr || Map1_Item->getContentSize().width <= 0 || Map1_Item->getContentSize().height <= 0) {
        problemLoading("'help_3-hd_1.png'");
    }
    else {

        //放置图片
        Map1_Item->setPosition(Vec2(origin.x + visibleSize.width / 2*3, origin.y + visibleSize.height / 2 +30));

        //将第一张地图加入层中
        menu1->addChild(Map1_Item);
    }
    auto Word1_Item = MenuItemImage::create("/HelperScene/help_1-hd_4.PNG", "/HelperScene/help_1-hd_4.PNG");
    Word1_Item->setCallback([this](Ref* psender) {; });
    if (Word1_Item == nullptr || Word1_Item->getContentSize().width <= 0 || Word1_Item->getContentSize().height <= 0) {
        problemLoading("'help_1-hd_73.PNG'");
    }
    else {

        //放置图片
        Word1_Item->setPosition(Vec2(origin.x + visibleSize.width / 2*3, origin.y + visibleSize.height / 2 - 160));

        //将第一张地图加入层中
        menu1->addChild(Word1_Item);
    }

    /*-----------第三张map---------*/
    auto Map2_Item = MenuItemImage::create("/HelperScene/help_3-hd_3.png", "/HelperScene/help_3-hd_3.png");
    Map2_Item->setCallback([this](Ref* psender) {; });
    if (Map2_Item == nullptr || Map2_Item->getContentSize().width <= 0 || Map2_Item->getContentSize().height <= 0) {
        problemLoading("'Map.png'");
    }
    else {

        //放置图片
        Map2_Item->setPosition(Vec2(origin.x + visibleSize.width / 2 *5, origin.y + visibleSize.height / 2 + 30));

        //将第二张地图加入层中
        menu1->addChild(Map2_Item);
    }
    auto Word2_Item = MenuItemImage::create("/HelperScene/help_1-hd_50.PNG", "/HelperScene/help_1-hd_50.PNG");
    Word2_Item->setCallback([this](Ref* psender) {; });
    if (Word2_Item == nullptr || Word2_Item->getContentSize().width <= 0 || Word2_Item->getContentSize().height <= 0) {
        problemLoading("'help_1-hd_73.PNG'");
    }
    else {

        //放置图片
        Word2_Item->setPosition(Vec2(origin.x + visibleSize.width / 2*5, origin.y + visibleSize.height / 2 - 160));

        //将第一张地图加入层中
        menu1->addChild(Word2_Item);
    }

    /*-----------第四张map---------*/
    
    auto Map3_Item = MenuItemImage::create("/HelperScene/help_3-hd_4.png", "/HelperScene/help_3-hd_4.png");
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
        Map3_Item->setPosition(Vec2(origin.x + visibleSize.width / 2*7, origin.y + visibleSize.height / 2 + 30));

        //将第三张地图加入层中
        menu1->addChild(Map3_Item);
    }
    auto Word3_Item = MenuItemImage::create("/HelperScene/help_1-hd_65.PNG", "/HelperScene/help_1-hd_65.PNG");
    Word3_Item->setCallback([this](Ref* psender) {; });
    if (Word3_Item == nullptr || Word3_Item->getContentSize().width <= 0 || Word3_Item->getContentSize().height <= 0) {
        problemLoading("'help_1-hd_73.PNG'");
    }
    else {

        //放置图片
        Word3_Item->setPosition(Vec2(origin.x + visibleSize.width / 2*7, origin.y + visibleSize.height / 2 -160));

        //将第一张地图加入层中
        menu1->addChild(Word3_Item);
    }

    //向左翻页按钮
    auto LeftArrow = MenuItemImage::create("/MapChooseScene/LeftArrow.png", "/MapChooseScene/LeftArrowSelected.png");
    //设置比例
    LeftArrow->setScale(0.8);
    LeftArrow->setCallback([visibleSize, Map_Layer,num1,num2,num3,num4, this](Ref* psender) {//回调函数
        if (Chapter >= 1) {
            Chapter--;
            Map_Layer->runAction(MoveBy::create(0.4, Vec2(visibleSize.width, 0)));
            switch (Chapter) {
            case 0:
                
                num1->setPosition(Vec2(visibleSize.width / 2 - 10, 35));
                num2->setPosition(Vec2(visibleSize.width / 2 - 10, visibleSize.height+50));
                
                break;
            case 1:
                
                num2->setPosition(Vec2(visibleSize.width / 2 - 10, 35));
                num1->setPosition(Vec2(visibleSize.width / 2 - 10, visibleSize.height + 50));
                num3->setPosition(Vec2(visibleSize.width / 2 - 10, visibleSize.height + 50));
                
                break;
            case 2:
                num3->setPosition(Vec2(visibleSize.width / 2 - 10, 35));
                num2->setPosition(Vec2(visibleSize.width / 2 - 10, visibleSize.height + 50));
                num4->setPosition(Vec2(visibleSize.width / 2 - 10, visibleSize.height + 50));
                
                break;
            case 3:
                
                num4->setPosition(Vec2(visibleSize.width / 2 - 10, 35));
                num3->setPosition(Vec2(visibleSize.width / 2 - 10, visibleSize.height + 50));
                
                break;
            }        
        }
        });
    LeftArrow->setPosition(Vec2(origin.x + visibleSize.width * 0.04+5, origin.y + visibleSize.height / 2));
    menu->addChild(LeftArrow);

    //向右翻页按钮
    auto RightArrow = MenuItemImage::create("/MapChooseScene/RightArrow.png", "/MapChooseScene/RightArrowSelected.png");
    RightArrow->setScale(0.8);
    RightArrow->setCallback([visibleSize, Map_Layer,num1, num2, num3, num4, this](Ref* psender) {//回调函数
        if (Chapter <= 2) {
            Map_Layer->runAction(MoveBy::create(0.4, Vec2(-visibleSize.width, 0)));
            Chapter++;
            switch (Chapter) {
            case 0:

                num1->setPosition(Vec2(visibleSize.width / 2 - 10, 35));
                num2->setPosition(Vec2(visibleSize.width / 2 - 10, visibleSize.height + 50));

                break;
            case 1:

                num2->setPosition(Vec2(visibleSize.width / 2 - 10, 35));
                num1->setPosition(Vec2(visibleSize.width / 2 - 10, visibleSize.height + 50));
                num3->setPosition(Vec2(visibleSize.width / 2 - 10, visibleSize.height + 50));

                break;
            case 2:
                num3->setPosition(Vec2(visibleSize.width / 2 - 10, 35));
                num2->setPosition(Vec2(visibleSize.width / 2 - 10, visibleSize.height + 50));
                num4->setPosition(Vec2(visibleSize.width / 2 - 10, visibleSize.height + 50));

                break;
            case 3:

                num4->setPosition(Vec2(visibleSize.width / 2 - 10, 35));
                num3->setPosition(Vec2(visibleSize.width / 2 - 10, visibleSize.height + 50));

                break;
            }
        }
        });
    RightArrow->setPosition(Vec2(origin.x + visibleSize.width * 0.96-5, origin.y + visibleSize.height / 2));
    menu->addChild(RightArrow);

    
    return true;

}
void Helper::goto_helper1(Ref* pSender)
{
    //创建冒险模式选关场景
    auto helper1 = Helpera::createScene();
    if (hit_sound_open)
        hit_sound->playEffect("/music/hit_sound.mp3", false, 1.0f, 1.0f, 1.0f);
    //淡出，切换场景
    Director::getInstance()->replaceScene(helper1);
}
void Helper::goto_helper2(Ref* pSender)
{
    //创建冒险模式选关场景
    auto helper = Helperb::createScene();
    if (hit_sound_open)
        hit_sound->playEffect("/music/hit_sound.mp3", false, 1.0f, 1.0f, 1.0f);
    //淡出，切换场景
    Director::getInstance()->replaceScene(helper);
}

void Helper::CloseCallback(cocos2d::Ref* pSender) 
{
    //Close the cocos2d-x game scene and quit the application
    auto MenuScene = MenuScene::createScene();
    if (bgm_open&&!bgm->isBackgroundMusicPlaying())
        bgm->playBackgroundMusic("/music/bgm.mp3", true);
    if (hit_sound_open)
        hit_sound->playEffect("/music/hit_sound.mp3", false, 1.0f, 1.0f, 1.0f);
    //淡出，切换场景
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, MenuScene));
}

