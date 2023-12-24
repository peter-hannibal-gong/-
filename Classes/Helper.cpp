#include "MenuScene.h"
#include "Helper.h"
USING_NS_CC;

/*��������*/
Scene* Helper::createScene()
{
    return Helper::create();
}

/*������*/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in Helper.cpp\n");
}


/*��ʼ������*/
bool Helper::init()
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
        CC_CALLBACK_1(Helper::CloseCallback, this));

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

    return true;

}

void Helper::CloseCallback(cocos2d::Ref* pSender) 
{
    //Close the cocos2d-x game scene and quit the application
    auto MenuScene = MenuScene::createScene();

    //�������л�����
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, MenuScene));
}

