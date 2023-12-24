#include "MenuScene.h"
#include "Helper.h"
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
    auto mainbackground = Sprite::create("/NestScene/help_3-hd_bg.png");
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

    return true;

}

void Helper::CloseCallback(cocos2d::Ref* pSender) 
{
    //Close the cocos2d-x game scene and quit the application
    auto MenuScene = MenuScene::createScene();

    //淡出，切换场景
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, MenuScene));
}

