
#include "Setting.h"
#include "MenuScene.h"
#include "music.h"
USING_NS_CC;

Scene* Setting::createScene()//创建舞台
{
    return Setting::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Setting::init()
{
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();  //获取分辨率（窗口大小）
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    //大的背景
    auto bg = Sprite::create("/SettingScene/SettingBG1.png");
    if (bg == nullptr)
    {
        problemLoading("'/MenuScene/SettingBG1.png'");
    }
    else
    {
        // position the bg on the center of the screen
        bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(bg, 0);
    }
    //返回按钮
    auto backItem = MenuItemImage::create(  //按钮
        "/SettingScene/Btn_Return.PNG",
        "/SettingScene/Btn_ReturnLight.PNG",
        CC_CALLBACK_1(Setting::menuCloseCallback, this));

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
//音xiao开关
    Sprite* hit_sound0;
    Sprite* hit_sound1;
    if (hit_sound_open) {
        hit_sound0 = Sprite::create("/SettingScene/setting02-hd_6.PNG");
        hit_sound1 = Sprite::create("/SettingScene/setting02-hd_11.PNG");
    }
    else {
        hit_sound0 = Sprite::create("/SettingScene/setting02-hd_11.PNG");
        hit_sound1 = Sprite::create("/SettingScene/setting02-hd_6.PNG");
    }
    auto hit_soundON = MenuItemSprite::create(hit_sound0, hit_sound0);
    auto hit_soundOFF = MenuItemSprite::create(hit_sound1, hit_sound1);

    //创建倍速开关的切换菜单项
    auto hit_soundItem = MenuItemToggle::createWithCallback([&](Ref* psender) {
        //若菜单项被点击，切换倍速的模式
        hit_sound_open = !hit_sound_open;
        }, hit_soundON, hit_soundOFF, nullptr);
    //将菜单项加入菜单中，放置在适合的位置
    auto menu1 = Menu::create(hit_soundItem, nullptr);
    hit_soundItem->setAnchorPoint(Vec2(0, 1));
    hit_soundItem->setPosition(Vec2(80 + visibleSize.width / 4 + origin.x, -20 + visibleSize.height * 0.7 + origin.y));
    menu1->setPosition(Vec2::ZERO);
    this->addChild(menu1, 1);
   
//音yue开关
    Sprite* bgm0;
    Sprite* bgm1;
    if (bgm_open) {
        bgm0 = Sprite::create("/SettingScene/setting02-hd_15.PNG");
        bgm1 = Sprite::create("/SettingScene/setting02-hd_21.PNG");
    }
    else{
        bgm0 = Sprite::create("/SettingScene/setting02-hd_21.PNG");
        bgm1 = Sprite::create("/SettingScene/setting02-hd_15.PNG");
    }
    auto bgmON = MenuItemSprite::create(bgm0, bgm0);
    auto bgmOFF = MenuItemSprite::create(bgm1, bgm1);

    //创建倍速开关的切换菜单项
    auto bgmItem = MenuItemToggle::createWithCallback([&](Ref* psender) {
        //若菜单项被点击，切换倍速的模式
        if (bgm_open)
        bgm->stopBackgroundMusic();
        else
            bgm->playBackgroundMusic("/music/bgm.mp3");
        bgm_open = !bgm_open;
        }, bgmON, bgmOFF, nullptr);
    //将菜单项加入菜单中，放置在适合的位置
    auto menu0 = Menu::create(bgmItem, nullptr);
    bgmItem->setAnchorPoint(Vec2(0, 1));
    bgmItem->setPosition(Vec2(290 + visibleSize.width / 4 + origin.x, -20 + visibleSize.height * 0.7 + origin.y));
    menu0->setPosition(Vec2::ZERO);
    this->addChild(menu0, 1);


    //文字提示
    auto zi_yinxiao = Sprite::create("/SettingScene/setting02-hd_0.PNG");
    if (zi_yinxiao == nullptr)
    {
        problemLoading("'setting02-hd_0.png'");
    }
    else
    {
        // position the bg on the center of the screen
        zi_yinxiao->setPosition(Vec2(140 + visibleSize.width / 4 + origin.x, visibleSize.height * 0.7 + origin.y));

        // add the sprite as a child to this layer
        
    }
    this->addChild(zi_yinxiao, 0);
    auto zi_yinyue = Sprite::create("/SettingScene/setting02-hd_2.PNG");
    if (zi_yinyue == nullptr)
    {
        problemLoading("'setting02-hd_2.png'");
    }
    else
    {
        // position the bg on the center of the screen
        zi_yinyue->setPosition(Vec2(350 + visibleSize.width / 4 + origin.x, visibleSize.height * 0.7 + origin.y));
        // add the sprite as a child to this layer
        this->addChild(zi_yinyue, 0);
    }
    auto xuanxiang = Sprite::create("/SettingScene/setting02-hd_45.PNG");
    if (xuanxiang == nullptr)
    {
        problemLoading("'setting02-hd_45.png'");
    }
    else
    {
        // position the bg on the center of the screen
        xuanxiang->setAnchorPoint(Vec2(0.5, 1));
        xuanxiang->setPosition(Vec2(visibleSize.width / 2 + origin.x, -25+visibleSize.height + origin.y));
        
        // create menu, it's an autorelease object
        // add the sprite as a child to this layer
        this->addChild(xuanxiang, 0);
    }

    auto word1 = Label::createWithTTF("ABOUT US", "fonts/Marker Felt.ttf", 26);
    word1->setColor(Color3B::WHITE);
    word1->enableOutline(Color4B::BLACK, 1);
    word1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(word1, 0);

    auto word2 = Label::createWithTTF("2250766 Gong Chenhao", "fonts/Marker Felt.ttf", 30);
    word2->setColor(Color3B::WHITE);
    word2->enableOutline(Color4B::BLACK, 1);
    word2->setPosition(Vec2(visibleSize.width / 2 + origin.x, -60+visibleSize.height / 2 + origin.y));
    this->addChild(word2, 0);

    auto word3 = Label::createWithTTF("2251328 Shen Yufan", "fonts/Marker Felt.ttf", 30);
    word3->setColor(Color3B::WHITE);
    word3->enableOutline(Color4B::BLACK, 1);
    word3->setPosition(Vec2(visibleSize.width / 2 + origin.x, -120 + visibleSize.height / 2 + origin.y));
    this->addChild(word3, 0);

    return true;
}


void Setting::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    auto MenuScene = MenuScene::createScene();
    if (bgm_open&&!bgm->isBackgroundMusicPlaying())
        bgm->playBackgroundMusic("/music/bgm.mp3", true);
    if (hit_sound_open)
        hit_sound->playEffect("/music/hit_sound.mp3", false, 1.0f, 1.0f, 1.0f);
    //淡出，切换场景
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, MenuScene));
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);

}
void Setting::Closebgm(Ref* pSender)
{
    if (bgm_open)
        bgm->stopBackgroundMusic();
    else
        bgm->playBackgroundMusic("/music/bgm.mp3");
    bgm_open = !bgm_open;
}

void Setting::CloseHitSound(Ref* pSender)
{
    hit_sound_open = !hit_sound_open;
}