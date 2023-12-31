#include "MenuScene.h"
#include "Helperb.h"
#include "Helpera.h"
#include "Helper.h"
#include"LevelSelectionScene.h"
#include "music.h"
USING_NS_CC;

/*创建场景*/
Scene* Helpera::createScene()
{
    return Helpera::create();
}

/*错误处理*/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in Helper.cpp\n");
}


/*初始化场景*/
bool Helpera::init()
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
        CC_CALLBACK_1(Helpera::CloseCallback, this));

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
    
    auto xuanxiang = MenuItemImage::create(  //按钮
        "/HelperScene/help_1-hd_33_normal.PNG",
        "/HelperScene/help_1-hd_33.PNG",
        CC_CALLBACK_1(Helpera::goto_helper, this));
    {
        xuanxiang->setScale(1.5);
        xuanxiang->setAnchorPoint(Vec2(0.5, 1));
        xuanxiang->setPosition(Vec2(visibleSize.width / 2 - xuanxiang->getContentSize().width + origin.x, -17 + visibleSize.height + origin.y));
        auto menu = Menu::create(xuanxiang, NULL);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu, 1);
    }
    auto xuanxiang1 = Sprite::create("/HelperScene/help_1-hd_71.PNG");
    xuanxiang1->setAnchorPoint(Vec2(0.5, 1));
    xuanxiang1->setPosition(Vec2(visibleSize.width / 2 + origin.x, -28 + visibleSize.height + origin.y));
    this->addChild(xuanxiang1, 1);

    auto xuanxiang2 = MenuItemImage::create(  //按钮
        "/HelperScene/help_1-hd_66_normal.PNG",
        "/HelperScene/help_1-hd_66.PNG",
        CC_CALLBACK_1(Helpera::goto_helper2, this));
    {
        xuanxiang2->setScale(1.5);
        xuanxiang2->setAnchorPoint(Vec2(0.5, 1));
        xuanxiang2->setPosition(Vec2(visibleSize.width / 2 + xuanxiang2->getContentSize().width + origin.x, -17 + visibleSize.height + origin.y));
        auto menu0 = Menu::create(xuanxiang2, NULL);
        menu0->setPosition(Vec2::ZERO);
        this->addChild(menu0, 1);
    }
    //主体
    auto show = Sprite::create("/HelperScene/help_3-hd_monster.png");
    show->setAnchorPoint(Vec2(0.5, 1));
    show->setPosition(Vec2(visibleSize.width / 2 + origin.x,-90+visibleSize.height + origin.y));
    this->addChild(show, 1);
    //文字
    auto sudu1 = Sprite::create("/HelperScene/help_1-hd_29.PNG");
    sudu1->setPosition(Vec2(-155+visibleSize.width / 2 + origin.x,-92 + visibleSize.height/2 + origin.y));
    this->addChild(sudu1, 1);
    auto sudu2 = Sprite::create("/HelperScene/help_1-hd_29.PNG");
    sudu2->setPosition(Vec2(138+visibleSize.width / 2 + origin.x,-92 + visibleSize.height/2 + origin.y));
    this->addChild(sudu2, 1);
    auto xueliang1 = Sprite::create("/HelperScene/help_1-hd_3.PNG");
    xueliang1->setPosition(Vec2(-155 + visibleSize.width / 2 + origin.x, -139 + visibleSize.height / 2 + origin.y));
    this->addChild(xueliang1, 1);
    auto xueliang2 = Sprite::create("/HelperScene/help_1-hd_3.PNG");
    xueliang2->setPosition(Vec2(138 + visibleSize.width / 2 + origin.x, -139 + visibleSize.height / 2 + origin.y));
    this->addChild(xueliang2, 1);

}
void Helpera::goto_helper(Ref* pSender)
{
    //创建冒险模式选关场景
    auto helper = Helper::createScene();
    if (hit_sound_open)
        hit_sound->playEffect("/music/hit_sound.mp3", false, 1.0f, 1.0f, 1.0f);
    //淡出，切换场景
    Director::getInstance()->replaceScene(helper);
}
void Helpera::goto_helper2(Ref* pSender)
{
    //创建冒险模式选关场景
    auto helper = Helperb::createScene();
    if (hit_sound_open)
        hit_sound->playEffect("/music/hit_sound.mp3", false, 1.0f, 1.0f, 1.0f);
    //淡出，切换场景
    Director::getInstance()->replaceScene( helper);
}

void Helpera::CloseCallback(cocos2d::Ref* pSender) 
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

