#include "LevelSelectionScene.h"
#include"MapChooseScene.h"
#include"Scene1.h"
USING_NS_CC;

/*��������*/
Scene* LevelSelectionScene::createScene()
{
    return LevelSelectionScene::create();
}

/*������*/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames inLevelSelectionScene.cpp\n");
}


/*��ʼ������*/
bool LevelSelectionScene::init()
{

    if (!Scene::init())  //��ʼ������
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();  //��ȡ�ֱ��ʣ����ڴ�С��
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //���ñ���ͼ
    auto background = Sprite::create("/LevelSelectionScene/background.png");
    if (background == nullptr)   //�Ҳ�����ͼƬ
    {
        problemLoading("'/LevelSelectionScene/background.png'");
    }
    else
    {
        //����ͼƬ
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        //��mainbackground�������������
        this->addChild(background);
    }

    auto LeftCloud = Sprite::create("/LevelSelectionScene/LeftCloud.png");
    if (LeftCloud == nullptr)   //�Ҳ�����ͼƬ
    {
        problemLoading("'/LevelSelectionScene/LeftCloud.png'");
    }
    else
    {
        //����ͼƬ
        LeftCloud->setPosition(Vec2(origin.x+ LeftCloud->getContentSize().width / 2, origin.y+ LeftCloud->getContentSize().height / 2));

        //��leftcloud�������������
        this->addChild(LeftCloud);
    }

    auto RightCloud = Sprite::create("/LevelSelectionScene/RightCloud.png");
    if (RightCloud == nullptr)   //�Ҳ�����ͼƬ
    {
        problemLoading("'/LevelSelectionScene/RightCloud.png'");
    }
    else
    {
        //����ͼƬ
        RightCloud->setPosition(Vec2(visibleSize.width+origin.x- RightCloud->getContentSize().width / 2, origin.y+ RightCloud->getContentSize().height / 2));

        //��rightcloud�������������
        this->addChild(RightCloud);
    }

    //�����˵�
    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    //���ص�ͼѡ�����İ���
    auto Back_Item = MenuItemImage::create("/LevelSelectionScene/Back.png", "/LevelSelectionScene/BackSelected.png");
    Back_Item->setCallback([this](Ref* psender) {//�ص�����

        auto map_scene = MapChooseScene::createScene();//�������˵���ӦScene
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, map_scene));//�л���MenuScene
        });
    Back_Item->setPosition(Vec2(origin.x + visibleSize.width * 0.05, origin.y + visibleSize.height * 0.95));
    menu->addChild(Back_Item);

    //������ť
    auto Helper_Item = MenuItemImage::create("/LevelSelectionScene/Helper.png", "/LevelSelectionScene/HelperSelected.png");
    Helper_Item->setCallback([this](Ref* psender) {//�ص�����
        ;   //��������
        //auto helper_scene = MapChooseScene::createScene();//�������˵���ӦScene
        //Director::getInstance()->replaceScene(TransitionFade::create(1.0f, helper_scene));//�л���MenuScene
        });
    Helper_Item->setPosition(Vec2(origin.x + visibleSize.width * 0.95, origin.y + visibleSize.height * 0.95));
    menu->addChild(Helper_Item);

    //��ʼ��Ϸ��ť
    auto Start_Item = MenuItemImage::create("/LevelSelectionScene/Start.png", "/LevelSelectionScene/StartSelected.png");
    Start_Item->setCallback([this](Ref* psender) {//�ص�����
        if (level_number == 1) {
            auto Level1 = Scene1::createScene();//������һ�ض�ӦScene
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Level1));//�л���Scene1
        }
        //���Ϊ�ڶ���...
        //���Ϊ������...
        });
    Start_Item->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height * 0.1));
    menu->addChild(Start_Item);


    //����ÿ���ؿ��ĸſ�ͼ���ڵĲ�
    Create_Layer1();

    return true;

}

void LevelSelectionScene::Create_Layer1()
{
    //��ȡ�ֱ��ʣ����ڴ�С��
    auto visibleSize = Director::getInstance()->getVisibleSize();  
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //�����㣬������볡����
    auto layer1 = Layer::create();
    layer1->setPosition(Vec2::ZERO);
    this->addChild(layer1);

    //�����˵������˵��������
    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    layer1->addChild(menu);

    //��һ��
    auto Level1_Item = MenuItemImage::create("/LevelSelectionScene/Level1.png", "/LevelSelectionScene/Level1.png");
    Level1_Item->setCallback([this](Ref* psender) {//�ص�����

        auto Level1 = Scene1::createScene();//������һ�ض�ӦScene
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Level1));//�л���Scene1
        });
    Level1_Item->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height * 0.53));
    menu->addChild(Level1_Item);


    //�ڶ���
    auto Level2_Item = MenuItemImage::create("/LevelSelectionScene/Level2.png", "/LevelSelectionScene/Level2.png");
    Level2_Item->setCallback([this](Ref* psender) {//�ص�����
        
        //auto Level2 = Scene2::createScene();//�����ڶ��ض�ӦScene
        //Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Level2));//�л���Scene2
        });
    Level2_Item->setPosition(Vec2(origin.x + visibleSize.width * 1.05, origin.y + visibleSize.height * 0.53));
    menu->addChild(Level2_Item);


    //������
    auto Level3_Item = MenuItemImage::create("/LevelSelectionScene/Level3.png", "/LevelSelectionScene/Level3.png");
    Level3_Item->setCallback([this](Ref* psender) {//�ص�����
        auto visibleSize = Director::getInstance()->getVisibleSize();  //��ȡ�ֱ��ʣ����ڴ�С��
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
        //auto Level3 = Scene3::createScene();//���������ض�ӦScene
        //Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Level3));//�л���Scene3
        });
    Level3_Item->setPosition(Vec2(origin.x + visibleSize.width * 1.6, origin.y + visibleSize.height * 0.53));
    menu->addChild(Level3_Item);


    //�����¼��ļ�����
    auto listener4 = EventListenerTouchOneByOne::create();
    listener4->onTouchBegan = [layer1](Touch* touch, Event* event) {
        return true;
    };


    //ʵ�ֻ���
    listener4->onTouchMoved = [layer1](Touch* touch, Event* event) {
        float distance = touch->getLocation().x - touch->getPreviousLocation().x;
        layer1->setPositionX(layer1->getPositionX() + distance);
    };
    listener4->onTouchEnded = [=](Touch* touch, Event* event) {
        //��ȡ�����ƶ�������룬���󻬶�����Ϊ�������һ�������Ϊ��
        float distance = touch->getLocation().x - touch->getStartLocation().x;
      
        //�����������ķ�֮һ��Ļ������Ϊ������ҳ
        if (distance > visibleSize.width / 4) {  //����ҳ
            if (level_number>=2) {   //�ڵڶ�ҳ֮���������ҳ
                level_number--;
                //ͨ���ƶ����λ����ʵ�ֵ�ͼ�ı仯
                layer1->runAction(MoveTo::create(0.2, Vec2(origin.x-visibleSize.width*(0.55* level_number-0.55), 0)));
            }
            else  {//��ǰ�ڵ�һҳ��������ô���󻬶����ص���һҳ
                layer1->runAction(MoveTo::create(0.2, Vec2(0 , 0)));
                //��Ч
            }
        }
        else if (distance < -visibleSize.width / 4) { //���һ�ҳ
            if (level_number <=2) { //�ڵڶ�ҳ֮ǰ�������ҷ�ҳ
                level_number++;
                layer1->runAction(MoveTo::create(0.2, Vec2(origin.x -visibleSize.width * (0.55 * level_number - 0.55), 0)));
            }
            else {//��ǰ�ڵ���ҳ��������ô���һ������ص�����ҳ
                layer1->runAction(MoveTo::create(0.2, Vec2(origin.x -visibleSize.width * 1.1, 0)));
                //��Ч
            }
        }
        else {//��С���ķ�֮һ��Ļ������Ϊȡ����ҳ
            layer1->runAction(MoveTo::create(0.2, Vec2(origin.x - visibleSize.width * (0.55 * level_number - 0.55), 0)));
                    
        }
    };
    //���¼������������¼��ַ���
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