#include "MapChooseScene.h"
#include "MenuScene.h"
#include"LevelSelectionScene.h"
USING_NS_CC;

/*��������*/
Scene* MapChooseScene::createScene()
{
    return MapChooseScene::create();
}

/*������*/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MapChooseScene.cpp\n");
}


/*��ʼ������*/
bool MapChooseScene::init()
{

    if (!Scene::init())  //��ʼ������
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();  //��ȡ�ֱ��ʣ����ڴ�С��
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //���ñ���ͼ
    auto background = Sprite::create("/MapChooseScene/background.png");
    if (background == nullptr)   //�Ҳ�����ͼƬ
    {
        problemLoading("'background.png'");
    }
    else
    {
        //����ͼƬ
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        //��mainbackground�������������
        this->addChild(background);
    }

    //�����˵�
    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);


    //�������˵�����
    auto BackHome_Item = MenuItemImage::create("/MapChooseScene/BackHome.png", "/MapChooseScene/BackHomeSelected.png");
    BackHome_Item->setCallback([this](Ref* psender) {//�ص�����
       
        auto menu_scene = MenuScene::createScene();//�������˵���ӦScene
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, menu_scene));//�л���MenuScene
        });
    BackHome_Item->setPosition(Vec2(origin.x + visibleSize.width * 0.05,origin.y + visibleSize.height * 0.95));
    menu->addChild(BackHome_Item);

    //������ť
    auto Helper_Item = MenuItemImage::create("/MapChooseScene/Helper.png", "/MapChooseScene/HelperSelected.png");
    Helper_Item->setCallback([this](Ref* psender) {//�ص�����

        auto menu_scene = MenuScene::createScene();//�������˵���ӦScene
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, menu_scene));//�л���MenuScene
        });
    Helper_Item->setPosition(Vec2(origin.x + visibleSize.width * 0.95, origin.y + visibleSize.height * 0.95));
    menu->addChild(Helper_Item);


    //������ͼ���ڵĲ�
    auto Map_Layer = Layer::create();
    Map_Layer->setPosition(Vec2::ZERO);
    this->addChild(Map_Layer);


    auto CarrotMap = Sprite::create("/MapChooseScene/carrotmap.png");
    CarrotMap->setPosition(Vec2(origin.x - visibleSize.width / 2 + 10, origin.y + visibleSize.height / 2 - 30));
    Map_Layer->addChild(CarrotMap);

    //����һ����menu�����ڴ�ŵ�ͼ����������Map_Layer��
    auto menu1 = Menu::create();
    menu1->setPosition(Vec2::ZERO);
    Map_Layer->addChild(menu1);


     /*-----------��һ��map---------*/
    auto Map1_Item = MenuItemImage::create("/MapChooseScene/map1.png", "/MapChooseScene/map1.png");
    Map1_Item->setCallback([this](Ref* psender) {//�ص�����

        auto LevelSelection = LevelSelectionScene::createScene();//�������˵���ӦScene
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, LevelSelection));//�л���MenuScene
        });

    if (Map1_Item == nullptr || Map1_Item->getContentSize().width <= 0 || Map1_Item->getContentSize().height <= 0) {
        problemLoading("'Map1.png'");
    }
    else {

        //����ͼƬ
        Map1_Item->setPosition(Vec2(origin.x + visibleSize.width / 2 + 10, origin.y + visibleSize.height / 2 - 30));

        //����һ�ŵ�ͼ�������
        menu1->addChild(Map1_Item);
    }

    /*-----------�ڶ���map---------*/
    auto Map2_Item = MenuItemImage::create("/MapChooseScene/map2.png", "/MapChooseScene/map2.png");
    Map2_Item->setCallback([this](Ref* psender) {//�ص�����
        ;
        //auto menu_scene = MenuScene::createScene();//�������˵���ӦScene
        //Director::getInstance()->replaceScene(TransitionFade::create(1.0f, menu_scene));//�л���MenuScene
        });

    if (Map2_Item == nullptr || Map2_Item->getContentSize().width <= 0 || Map2_Item->getContentSize().height <= 0) {
        problemLoading("'Map.png'");
    }
    else {
                
        //����ͼƬ
        Map2_Item->setPosition(Vec2(origin.x + visibleSize.width / 2 *3+ 10, origin.y + visibleSize.height / 2 - 30));

        //���ڶ��ŵ�ͼ�������
        menu1->addChild(Map2_Item);
    }

    /*-----------������map---------*/
    auto Map3_Item = MenuItemImage::create("/MapChooseScene/map3.png", "/MapChooseScene/map3.png");
    Map3_Item->setCallback([this](Ref* psender) {//�ص�����
        ;
        // auto menu_scene = MenuScene::createScene();//�������˵���ӦScene
        //Director::getInstance()->replaceScene(TransitionFade::create(1.0f, menu_scene));//�л���MenuScene
        });

    if (Map3_Item == nullptr || Map3_Item->getContentSize().width <= 0 || Map3_Item->getContentSize().height <= 0) {
        problemLoading("'Map3.png'");
    }
    else {

        //����ͼƬ
        Map3_Item->setPosition(Vec2(origin.x + visibleSize.width / 2 * 5 + 10, origin.y + visibleSize.height / 2 - 30));

        //�������ŵ�ͼ�������
        menu1->addChild(Map3_Item);
    }

    //����ҳ��ť
    auto LeftArrow = MenuItemImage::create("/MapChooseScene/LeftArrow.png", "/MapChooseScene/LeftArrowSelected.png");
    LeftArrow->setCallback([visibleSize, Map_Layer,this](Ref* psender) {//�ص�����
        if (Chapter >= 1 ) {
            Chapter--;
            Map_Layer->runAction(MoveBy::create(0.4, Vec2(visibleSize.width, 0)));
        }
    });
    LeftArrow->setPosition(Vec2(origin.x + visibleSize.width * 0.08,origin.y + visibleSize.height / 2));
    menu->addChild(LeftArrow);

    //���ҷ�ҳ��ť
    auto RightArrow = MenuItemImage::create("/MapChooseScene/RightArrow.png", "/MapChooseScene/RightArrowSelected.png");
    RightArrow->setCallback([visibleSize, Map_Layer, this](Ref* psender) {//�ص�����
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