#include "MenuScene.h"
#include "Helperb.h"
#include "Helpera.h"
#include "Helper.h"
#include"LevelSelectionScene.h"
#include "music.h"
USING_NS_CC;

/*��������*/
Scene* Helpera::createScene()
{
    return Helpera::create();
}

/*������*/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in Helper.cpp\n");
}


/*��ʼ������*/
bool Helpera::init()
{
    if (!Scene::init())  //��ʼ������
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();  //��ȡ�ֱ��ʣ����ڴ�С��
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //���ñ���ͼ
    auto mainbackground = Sprite::create("/HelperScene/help_3-hd_bg.png");
    if (mainbackground == nullptr)   //�Ҳ�����ͼƬ
    {
        problemLoading("'mainbackground.png'");
    }
    else
    { 
        //����ͼƬ
        mainbackground->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y )); 

        //��mainbackground�������������
        this->addChild(mainbackground, 0);   
    }
    //���ذ�ť
    auto backItem = MenuItemImage::create(  //��ť
        "/HelperScene/help_1-hd_67.PNG",
        "/HelperScene/help_1-hd_38.PNG",
        CC_CALLBACK_1(Helpera::CloseCallback, this));

    if (backItem == nullptr ||
        backItem->getContentSize().width <= 0 ||
        backItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");  //���ִ���
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

    //����װ��
    
    auto xuanxiang = MenuItemImage::create(  //��ť
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

    auto xuanxiang2 = MenuItemImage::create(  //��ť
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
    //����
    auto show = Sprite::create("/HelperScene/help_3-hd_monster.png");
    show->setAnchorPoint(Vec2(0.5, 1));
    show->setPosition(Vec2(visibleSize.width / 2 + origin.x,-90+visibleSize.height + origin.y));
    this->addChild(show, 1);
    //����
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
    //����ð��ģʽѡ�س���
    auto helper = Helper::createScene();
    if (hit_sound_open)
        hit_sound->playEffect("/music/hit_sound.mp3", false, 1.0f, 1.0f, 1.0f);
    //�������л�����
    Director::getInstance()->replaceScene(helper);
}
void Helpera::goto_helper2(Ref* pSender)
{
    //����ð��ģʽѡ�س���
    auto helper = Helperb::createScene();
    if (hit_sound_open)
        hit_sound->playEffect("/music/hit_sound.mp3", false, 1.0f, 1.0f, 1.0f);
    //�������л�����
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
    //�������л�����
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, MenuScene));
}

