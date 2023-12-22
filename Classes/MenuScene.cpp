#include "MenuScene.h"
#include "Scene1.h"
#include<string>
USING_NS_CC;

/*��������*/
Scene* MenuScene::createScene()
{
    return MenuScene::create();
}

/*������*/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MenuScene.cpp\n");
}


/*��ʼ������*/
bool MenuScene::init()
{
  
    if (!Scene::init())  //��ʼ������
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();  //��ȡ�ֱ��ʣ����ڴ�С��
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //���ñ���ͼ
    auto mainbackground = Sprite::create("/MenuScene/mainbackground.png");
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


    //���ô��ƶ�
    auto bigcloud = Sprite::create("/MenuScene/bigcloud.png");
    if (bigcloud == nullptr)   //�Ҳ�����ͼƬ
    {
        problemLoading("'bigcloud.png'");
    }
    else
    {
        //���ñ���
        bigcloud->setScale(0.8);

        //����ͼƬ
        bigcloud->setPosition(Vec2(origin.x - bigcloud->getContentSize().width,origin.y + visibleSize.height * 0.85)); 

        //����͸����
        bigcloud->setOpacity(95);

        //��������Ʈ��������
        auto bigcloud_move1 = MoveTo::create(5, Vec2(origin.x + visibleSize.width * 2, origin.y + visibleSize.height * 0.85));

        //�ص�ԭ��λ��
        auto bigcloud_move2 = MoveTo::create(0, Vec2(origin.x - bigcloud->getContentSize().width, origin.y + visibleSize.height * 0.85));

        //�������У��ȴ����ң���ͣ3s���ص�ԭ��λ��
        auto bigcloud_sequence = Sequence::create(bigcloud_move1, DelayTime::create(3), bigcloud_move2, nullptr);

        //����ѭ�����ƶ䶯������
        bigcloud->runAction(RepeatForever::create(bigcloud_sequence));

        this->addChild(bigcloud);         //��bigcloud�������������

    }


    //����С�ƶ�
    auto smallcloud = Sprite::create("/MenuScene/smallcloud.png");
    if (smallcloud == nullptr)   //�Ҳ�����ͼƬ
    {
        problemLoading("'smallcloud.png'");
    }
    else
    { 
        //����ͼƬ
        smallcloud->setPosition(Vec2(origin.x - smallcloud->getContentSize().width,origin.y + visibleSize.height * 0.77));

        //����͸����
        smallcloud->setOpacity(90); 
      
        //��������Ʈ��������
        auto smallcloud_move2 = MoveTo::create(3, Vec2(origin.x + visibleSize.width*2, origin.y + visibleSize.height * 0.77));

        //�ص�ԭ��λ��
        auto smallcloud_move1 = MoveTo::create(0, Vec2(origin.x-smallcloud->getContentSize().width, origin.y + visibleSize.height * 0.77));

        //�������У��ȴ����ң���ͣ3s���ص�ԭ��λ��
        auto smallcloud_sequence = Sequence::create(smallcloud_move1, DelayTime::create(3), smallcloud_move2, nullptr);

        //����ѭ��С�ƶ䶯������
        smallcloud->runAction(RepeatForever::create(smallcloud_sequence));

        //��smallcloud���볡����
        this->addChild(smallcloud);  
    }



    //�����ܲ� 

    //������Ҷ��
    auto leaf1 = Sprite::create("/MenuScene/leaf1.png");
    if (leaf1 == nullptr)   //�Ҳ�����ͼƬ
    {
        problemLoading("leaf1.png'");
    }
    else
    {
        //����ͼƬ
        leaf1->setPosition(Vec2(origin.x + visibleSize.width / 2-60 , origin.y + visibleSize.height / 2 +130));

        //����Ҷ�Ӽ��볡����
        this->addChild(leaf1);
    }

    //������Ҷ��
    auto leaf2 = Sprite::create("/MenuScene/leaf2.png");
    if (leaf2 == nullptr)   //�Ҳ�����ͼƬ
    {
        problemLoading("leaf2.png'");
    }
    else
    {
        //����ͼƬ
        leaf2->setPosition(Vec2(origin.x + visibleSize.width / 2 +90, origin.y + visibleSize.height / 2 + 130));

        //����Ҷ�Ӽ��볡����
        this->addChild(leaf2);
    }

    //�����м��Ҷ��
    auto leaf3 = Sprite::create("/MenuScene/leaf3.png");
    if (leaf3 == nullptr)   //�Ҳ�����ͼƬ
    {
        problemLoading("leaf3.png'");
    }
    else
    {
        //����ͼƬ
        leaf3->setPosition(Vec2(origin.x + visibleSize.width / 2 + 10, origin.y + visibleSize.height / 2 + 160));

        //���м��Ҷ�Ӽ��볡����
        this->addChild(leaf3);
    }

    //�����ܲ�
    auto carrot = Sprite::create("/MenuScene/carrot.png");
    if (smallcloud == nullptr)   //�Ҳ�����ͼƬ
    {
        problemLoading("'carrot.png'");
    }
    else
    {
        //����ͼƬ
        carrot->setPosition(Vec2(origin.x + visibleSize.width / 2 + 10, origin.y + visibleSize.height / 2 + 40));

        //���ܲ����볡����
        this->addChild(carrot);
    }

    //���ñ���
    auto title = Sprite::create("/MenuScene/title.png");
    if (title == nullptr)   //�Ҳ�����ͼƬ
    {
        problemLoading("'title.png'");
    }
    else
    {
        //���ñ���
        bigcloud->setScale(0.9);

        //����ͼƬ
        title->setPosition(Vec2(origin.x + visibleSize.width / 2+35, origin.y + visibleSize.height / 2-40));

        //��������볡����
        this->addChild(title);
    }
  
    //���ù���
    auto monster = Sprite::create("/MenuScene/monster.png");
    if (monster == nullptr)   //�Ҳ�����ͼƬ
    {
        problemLoading("'monster.png'");
    }
    else
    {
        //���ñ���
        bigcloud->setScale(0.9);

        //����ͼƬ
        monster->setPosition(Vec2(origin.x + visibleSize.width / 5, origin.y + visibleSize.height*0.8));

        //��������볡����
        this->addChild(monster);
    }



    //�����˵�
    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
 

    //ð��ģʽ
    auto AdventureModel_Item = MenuItemImage::create("/MenuScene/AdventureModel.png", "/MenuScene/AdventureModelSelected.png", CC_CALLBACK_1(MenuScene::goto_adventure, this));

    if (AdventureModel_Item == nullptr    || AdventureModel_Item->getContentSize().width <= 0 ||AdventureModel_Item->getContentSize().height <= 0) {
        problemLoading("'AdventureModel.png'and 'AdventureModelSelected.png'");
    }
    else {
        //���ñ���
        AdventureModel_Item->setScale(0.9);

        //����ͼƬ
        AdventureModel_Item->setPosition(Vec2(origin.x + visibleSize.width / 5, origin.y + visibleSize.height / 8));

        //��ð��ģʽ����˵���
        menu->addChild(AdventureModel_Item);
    }


    //BOSSģʽ����
    auto BossModel_Item = MenuItemImage::create("/MenuScene/BossModel.png", "/MenuScene/BossModelSelected.png", CC_CALLBACK_1(MenuScene::CloseCallback, this));

    if (BossModel_Item == nullptr || BossModel_Item->getContentSize().width <= 0 || BossModel_Item->getContentSize().height <= 0) {
        problemLoading("'BosseModel.png' and 'BosseModelSelected.png'");
    }
    else {
        //���ñ���
        BossModel_Item->setScale(0.9);

        //����ͼƬ
        BossModel_Item->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 8));

        //��BOSSģʽ����˵���
        menu->addChild(BossModel_Item);
    }

    //�����Ѱ���
    auto MonsterNest_Item = MenuItemImage::create("/MenuScene/MonsterNest.png", "/MenuScene/MonsterNestSelected.png", CC_CALLBACK_1(MenuScene::CloseCallback, this));

    if (MonsterNest_Item == nullptr || MonsterNest_Item->getContentSize().width <= 0 || MonsterNest_Item->getContentSize().height <= 0) {
        problemLoading("'MonsterNest.png' and 'MonsterNestSelected.png'");
    }
    else {
        //���ñ���
        MonsterNest_Item->setScale(0.9);

        //����ͼƬ
        MonsterNest_Item->setPosition(Vec2(origin.x + visibleSize.width / 5 * 4, origin.y + visibleSize.height / 8));

        //�������Ѽ���˵���
        menu->addChild(MonsterNest_Item);
    }

    //���ð���
    auto Set_Item = MenuItemImage::create("/MenuScene/Set.png", "/MenuScene/SetSelected.png", CC_CALLBACK_1(MenuScene::CloseCallback, this));
    if (Set_Item == nullptr) {
        problemLoading("'Set.png' and 'SetSelected.png'");
    }
    else {
        //����ͼƬ
        Set_Item->setPosition(Vec2(origin.x + visibleSize.width / 5, origin.y + visibleSize.height / 3));

        //�����ð�������˵���
        menu->addChild(Set_Item);
    }

    //��������
    auto Help_Item = MenuItemImage::create("/MenuScene/Help.png", "/MenuScene/HelpSelected.png", CC_CALLBACK_1(MenuScene::CloseCallback, this));
    if (Help_Item == nullptr) {
        problemLoading("'Help.png' and 'HelpSelected.png'");
    }
    else {
        //����ͼƬ
        Help_Item->setPosition(Vec2(origin.x + visibleSize.width / 5 * 4 , origin.y + visibleSize.height / 3));

        //��������������˵�
        menu->addChild(Help_Item);
    }



    //���˵��������볡����
    this->addChild(menu);

    return true;

}


void  MenuScene::goto_adventure(Ref* psender) 
{
    //����ð��ģʽѡ�س���
    auto GameScene1 = Scene1::createScene();

    //�������л�����
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameScene1));
}



void MenuScene::CloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}