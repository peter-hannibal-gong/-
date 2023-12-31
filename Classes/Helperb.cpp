#include "MenuScene.h"
#include "Helperb.h"
#include "Helpera.h"
#include "Helper.h"
#include"LevelSelectionScene.h"
#include "music.h"
USING_NS_CC;

/*��������*/
Scene* Helperb::createScene()
{
    return Helperb::create();
}

/*������*/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in Helper.cpp\n");
}


/*��ʼ������*/
bool Helperb::init()
{
    if (!Scene::init())  //��ʼ������
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();  //��ȡ�ֱ��ʣ����ڴ�С��
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //���ñ���ͼ
    auto mainbackground = Sprite::create("/NestScene/help_3-hd_bg.png");
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
        CC_CALLBACK_1(Helperb::CloseCallback, this));

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
    auto xuanxiang = MenuItemImage::create(  //��ť
        "/HelperScene/help_1-hd_33_normal.PNG",
        "/HelperScene/help_1-hd_33.PNG",
        CC_CALLBACK_1(Helperb::goto_helper, this));
    if (xuanxiang == nullptr ||
        xuanxiang->getContentSize().width <= 0 ||
        xuanxiang->getContentSize().height <= 0)
    {
        problemLoading("'xuanxiang'");  //���ִ���
    }
    else
    {
        xuanxiang->setScale(1.5);
        xuanxiang->setAnchorPoint(Vec2(0.5, 1));
        xuanxiang->setPosition(Vec2(visibleSize.width / 2 - xuanxiang->getContentSize().width + origin.x, -17 + visibleSize.height + origin.y));
        auto menu = Menu::create(xuanxiang, NULL);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu, 1);
    }
    auto xuanxiang1 = MenuItemImage::create(  //��ť
        "/HelperScene/help_1-hd_71_normal.PNG",
        "/HelperScene/help_1-hd_71.PNG",
        CC_CALLBACK_1(Helperb::goto_helper1, this));
    if (xuanxiang1 == nullptr ||
        xuanxiang1->getContentSize().width <= 0 ||
        xuanxiang1->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");  //���ִ���
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
    auto xuanxiang2 = Sprite::create("/HelperScene/help_1-hd_66.PNG");
    if (xuanxiang2 == nullptr)
    {
        problemLoading("'setting02-hd_45.png'");
    }
    else
    {
        xuanxiang2->setAnchorPoint(Vec2(0.5, 1));
        xuanxiang2->setPosition(Vec2(visibleSize.width / 2 + xuanxiang2->getContentSize().width + origin.x, -28 + visibleSize.height + origin.y));
        this->addChild(xuanxiang2, 0);
    }

    //�ײ�װ��
    auto bottom = Sprite::create("/HelperScene/help_1-hd_0.PNG");
    if (bottom == nullptr)   //�Ҳ�����ͼƬ
    {
        problemLoading("'bottom.png'");
    }
    else
    {
        //����ͼƬ
        bottom->setPosition(Vec2(origin.x + visibleSize.width / 2 + 13, origin.y + 35));

        //��������볡����
        this->addChild(bottom);
    }

    auto num_max = Sprite::create("/HelperScene/num_3.png");
    if (num_max == nullptr)   //�Ҳ�����ͼƬ
    {
        problemLoading("'num_3.png'");
    }
    else
    {
        //����ͼƬ
        num_max->setPosition(Vec2(origin.x + visibleSize.width / 2 + 10, origin.y + 35));
        this->addChild(num_max);
    }
    auto xiegang = Sprite::create("/HelperScene/num_-1.png");
    if (xiegang == nullptr)   //�Ҳ�����ͼƬ
    {
        problemLoading("'num_-1.png'");
    }
    else
    {
        //����ͼƬ
        xiegang->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 35));
        this->addChild(xiegang);
    }
    auto num1 = Sprite::create("/HelperScene/num_1.png");
    if (num1 == nullptr)   //�Ҳ�����ͼƬ
    {
        problemLoading("'num1.png'");
    }
    else
    {
        //����ͼƬ
        num1->setPosition(Vec2(origin.x + visibleSize.width / 2 - 10, origin.y + 35));
        this->addChild(num1);
    }
    auto num2 = Sprite::create("/HelperScene/num_2.png");
    if (num2 == nullptr)   //�Ҳ�����ͼƬ
    {
        problemLoading("'num2.png'");
    }
    else
    {
        //����ͼƬ
        //num2->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 35));
        this->addChild(num2);
    }
    auto num3 = Sprite::create("/HelperScene/num_3.png");
    if (num3 == nullptr)   //�Ҳ�����ͼƬ
    {
        problemLoading("'num3.png'");
    }
    else
    {
        //����ͼƬ
        //num3->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 35));
        this->addChild(num3);
    }
    //������ͼ���ڵĲ�
    auto Map_Layer = Layer::create();
    Map_Layer->setPosition(Vec2::ZERO);
    this->addChild(Map_Layer);

    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    //����һ����menu�����ڴ�ŵ�ͼ����������Map_Layer��
    auto menu1 = Menu::create();
    menu1->setPosition(Vec2::ZERO);
    Map_Layer->addChild(menu1);

    //ͼ����λ��

    /*-----------��һ��map---------*/
    auto Map0_Item = MenuItemImage::create("/HelperScene/tower_1.png", "/HelperScene/tower_1.png");
    Map0_Item->setScale(0.9);
    Map0_Item->setCallback([this](Ref* psender) {; });
    if (Map0_Item == nullptr || Map0_Item->getContentSize().width <= 0 || Map0_Item->getContentSize().height <= 0) {
        problemLoading("'tower_1.png'");
    }
    else {

        //����ͼƬ
        Map0_Item->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 10));

        //����һ�ŵ�ͼ�������
        menu1->addChild(Map0_Item);
    }

    /*-----------�ڶ���map---------*/
    auto Map1_Item = MenuItemImage::create("/HelperScene/tower_2.png", "/HelperScene/tower_2.png");
    Map1_Item->setScale(0.9);
    Map1_Item->setCallback([this](Ref* psender) {; });

    if (Map1_Item == nullptr || Map1_Item->getContentSize().width <= 0 || Map1_Item->getContentSize().height <= 0) {
        problemLoading("'tower_2.png'");
    }
    else {

        //����ͼƬ
        Map1_Item->setPosition(Vec2(origin.x + visibleSize.width / 2 * 3, origin.y + visibleSize.height / 2 + 10));

        //����һ�ŵ�ͼ�������
        menu1->addChild(Map1_Item);
    }

    /*-----------������map---------*/
    auto Map2_Item = MenuItemImage::create("/HelperScene/tower_4.png", "/HelperScene/tower_4.png");
    Map2_Item->setScale(0.9);
    Map2_Item->setCallback([this](Ref* psender) {; });
    if (Map2_Item == nullptr || Map2_Item->getContentSize().width <= 0 || Map2_Item->getContentSize().height <= 0) {
        problemLoading("'tower_4.png'");
    }
    else {

        //����ͼƬ
        Map2_Item->setPosition(Vec2(origin.x + visibleSize.width / 2 * 5, origin.y + visibleSize.height / 2 + 10));

        //���ڶ��ŵ�ͼ�������
        menu1->addChild(Map2_Item);
    }

    //����ҳ��ť
    auto LeftArrow = MenuItemImage::create("/MapChooseScene/LeftArrow.png", "/MapChooseScene/LeftArrowSelected.png");
    //���ñ���
    LeftArrow->setScale(0.8);
    LeftArrow->setCallback([visibleSize, Map_Layer, num1, num2, num3, this](Ref* psender) {//�ص�����
        if (Chapter >= 1) {
            Chapter--;
            Map_Layer->runAction(MoveBy::create(0.4, Vec2(visibleSize.width, 0)));
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
                break;
            }
        }
        });
    LeftArrow->setPosition(Vec2(origin.x + visibleSize.width * 0.04 + 5, origin.y + visibleSize.height / 2));
    menu->addChild(LeftArrow);

    //���ҷ�ҳ��ť
    auto RightArrow = MenuItemImage::create("/MapChooseScene/RightArrow.png", "/MapChooseScene/RightArrowSelected.png");
    RightArrow->setScale(0.8);
    RightArrow->setCallback([visibleSize, Map_Layer, num1, num2, num3, this](Ref* psender) {//�ص�����
        if (Chapter <= 1) {
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
                break;
            }
        }
        });
    RightArrow->setPosition(Vec2(origin.x + visibleSize.width * 0.96 - 5, origin.y + visibleSize.height / 2));
    menu->addChild(RightArrow);
    
    return true;

}
void Helperb::goto_helper(Ref* pSender)
{
    //����ð��ģʽѡ�س���
    auto helper = Helper::createScene();
    if (hit_sound_open)
        hit_sound->playEffect("/music/hit_sound.mp3", false, 1.0f, 1.0f, 1.0f);
    //�������л�����
    Director::getInstance()->replaceScene(helper);
}
void Helperb::goto_helper1(Ref* pSender)
{
    //����ð��ģʽѡ�س���
    auto helper = Helpera::createScene();
    if (hit_sound_open)
        hit_sound->playEffect("/music/hit_sound.mp3", false, 1.0f, 1.0f, 1.0f);
    //�������л�����
    Director::getInstance()->replaceScene( helper);
}

void Helperb::CloseCallback(cocos2d::Ref* pSender) 
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

