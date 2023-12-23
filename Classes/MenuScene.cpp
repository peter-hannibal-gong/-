#include "MenuScene.h"
#include "Scene1.h"
#include<string>
USING_NS_CC;

/*创建场景*/
Scene* MenuScene::createScene()
{
    return MenuScene::create();
}

/*错误处理*/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MenuScene.cpp\n");
}


/*初始化场景*/
bool MenuScene::init()
{
  
    if (!Scene::init())  //初始化场景
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();  //获取分辨率（窗口大小）
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //放置背景图
    auto mainbackground = Sprite::create("/MenuScene/mainbackground.png");
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


    //放置大云朵
    auto bigcloud = Sprite::create("/MenuScene/bigcloud.png");
    if (bigcloud == nullptr)   //找不到该图片
    {
        problemLoading("'bigcloud.png'");
    }
    else
    {
        //设置比例
        bigcloud->setScale(0.8);

        //放置图片
        bigcloud->setPosition(Vec2(origin.x - bigcloud->getContentSize().width,origin.y + visibleSize.height * 0.85)); 

        //设置透明度
        bigcloud->setOpacity(95);

        //从左向右飘到界面外
        auto bigcloud_move1 = MoveTo::create(5, Vec2(origin.x + visibleSize.width * 2, origin.y + visibleSize.height * 0.85));

        //回到原来位置
        auto bigcloud_move2 = MoveTo::create(0, Vec2(origin.x - bigcloud->getContentSize().width, origin.y + visibleSize.height * 0.85));

        //动作序列，先从左到右，暂停3s，回到原来位置
        auto bigcloud_sequence = Sequence::create(bigcloud_move1, DelayTime::create(3), bigcloud_move2, nullptr);

        //无限循环大云朵动作序列
        bigcloud->runAction(RepeatForever::create(bigcloud_sequence));

        this->addChild(bigcloud);         //将bigcloud加入这个场景中

    }

    //放置小云朵
    auto smallcloud = Sprite::create("/MenuScene/smallcloud.png");
    if (smallcloud == nullptr)   //找不到该图片
    {
        problemLoading("'smallcloud.png'");
    }
    else
    { 
        //放置图片
        smallcloud->setPosition(Vec2(origin.x - smallcloud->getContentSize().width,origin.y + visibleSize.height * 0.77));

        //设置透明度
        smallcloud->setOpacity(90); 
      
        //从左向右飘到界面外
        auto smallcloud_move2 = MoveTo::create(3, Vec2(origin.x + visibleSize.width*2, origin.y + visibleSize.height * 0.77));

        //回到原来位置
        auto smallcloud_move1 = MoveTo::create(0, Vec2(origin.x-smallcloud->getContentSize().width, origin.y + visibleSize.height * 0.77));

        //动作序列，先从左到右，暂停3s，回到原来位置
        auto smallcloud_sequence = Sequence::create(smallcloud_move1, DelayTime::create(3), smallcloud_move2, nullptr);

        //无限循环小云朵动作序列
        smallcloud->runAction(RepeatForever::create(smallcloud_sequence));

        //将smallcloud加入场景中
        this->addChild(smallcloud);  
    }

    //放置萝卜 
    const int rabbit_leaf_hang_time = 1;
    const int rabbit_leaf_hang_range = 10;
    //放置左叶子
    auto leaf1 = Sprite::create("/MenuScene/leaf1.png");
    if (leaf1 == nullptr)   //找不到该图片
    {
        problemLoading("leaf1.png'");
    }
    else
    {
        auto leaf1size = leaf1->getContentSize();
        //放置图片
        leaf1->setPosition(Vec2(origin.x + leaf1size.width/2+ visibleSize.width / 2 - 60, origin.y - leaf1size.height/2 + visibleSize.height / 2 + 130));
        
        leaf1->setAnchorPoint(Vec2(1, 0));
        //从左向右飘到界面外
        auto leaf1_move1 = RotateTo::create(rabbit_leaf_hang_time, -rabbit_leaf_hang_range);
        //回到原来位置
        auto leaf1_move2 = RotateTo::create(rabbit_leaf_hang_time, rabbit_leaf_hang_range);
        //回到原来位置
        auto leaf1_move3 = RotateTo::create(rabbit_leaf_hang_time, 0);
        //动作序列，先从左到右，暂停3s，回到原来位置
        auto leaf1_sequence = Sequence::create(leaf1_move1, leaf1_move2, leaf1_move3,DelayTime::create(3), nullptr);
        
        //无限循环小云朵动作序列
        leaf1->runAction(RepeatForever::create(leaf1_sequence));
        //将左叶子加入场景中
        this->addChild(leaf1);
        
    }

    //放置右叶子
    auto leaf2 = Sprite::create("/MenuScene/leaf2.png");
    if (leaf2 == nullptr)   //找不到该图片
    {
        problemLoading("leaf2.png'");
    }
    else
    {   
        auto leaf2size = leaf2->getContentSize();
        //放置图片
        leaf2->setPosition(Vec2(origin.x - leaf2size.width / 2 + visibleSize.width / 2 +90, origin.y - leaf2size.height / 2 + visibleSize.height / 2 + 130));        

        leaf2->setAnchorPoint(Vec2(0, 0));
        //从左向右飘到界面外
        auto leaf2_move1 = RotateTo::create(rabbit_leaf_hang_time, -rabbit_leaf_hang_range);
        //回到原来位置
        auto leaf2_move2 = RotateTo::create(rabbit_leaf_hang_time, rabbit_leaf_hang_range);
        //回到原来位置
        auto leaf2_move3 = RotateTo::create(rabbit_leaf_hang_time, 0);
        //动作序列，先从左到右，暂停3s，回到原来位置
        auto leaf2_sequence = Sequence::create(leaf2_move1, leaf2_move2, leaf2_move3, DelayTime::create(3), nullptr);

        //无限循环小云朵动作序列
        leaf2->runAction(RepeatForever::create(leaf2_sequence));
        //将左叶子加入场景中
        this->addChild(leaf2);


    }

    //放置中间的叶子
    auto leaf3 = Sprite::create("/MenuScene/leaf3.png");
    if (leaf3 == nullptr)   //找不到该图片
    {
        problemLoading("leaf3.png'");
    }
    else
    {
        auto leaf3size = leaf3->getContentSize();
        //放置图片
        leaf3->setPosition(Vec2(origin.x + visibleSize.width / 2 + 10, origin.y - leaf3size.height / 2 + visibleSize.height / 2 + 160));


        leaf3->setAnchorPoint(Vec2(0.5, 0));
        //从左向右飘到界面外
        auto leaf3_move1 = RotateTo::create(rabbit_leaf_hang_time, -rabbit_leaf_hang_range);
        //回到原来位置
        auto leaf3_move2 = RotateTo::create(rabbit_leaf_hang_time, rabbit_leaf_hang_range);
        //回到原来位置
        auto leaf3_move3 = RotateTo::create(rabbit_leaf_hang_time, 0);
        //动作序列，先从左到右，暂停3s，回到原来位置
        auto leaf3_sequence = Sequence::create(leaf3_move1, leaf3_move2, leaf3_move3, DelayTime::create(3), nullptr);

        //无限循环小云朵动作序列
        leaf3->runAction(RepeatForever::create(leaf3_sequence));
        //将左叶子加入场景中
        this->addChild(leaf3);


    }

    //放置萝卜
    auto carrot = Sprite::create("/MenuScene/carrot.png");
    if (smallcloud == nullptr)   //找不到该图片
    {
        problemLoading("'carrot.png'");
    }
    else
    {
        //放置图片
        carrot->setPosition(Vec2(origin.x + visibleSize.width / 2 + 10, origin.y + visibleSize.height / 2 + 40));

        //将萝卜加入场景中
        this->addChild(carrot);
    }

    //放置标题
    auto title = Sprite::create("/MenuScene/title.png");
    if (title == nullptr)   //找不到该图片
    {
        problemLoading("'title.png'");
    }
    else
    {
        //设置比例
        bigcloud->setScale(0.9);

        //放置图片
        title->setPosition(Vec2(origin.x + visibleSize.width / 2+35, origin.y + visibleSize.height / 2-40));

        //将标题加入场景中
        this->addChild(title);
    }
  
    //放置怪物
    auto monster = Sprite::create("/MenuScene/monster.png");
    if (monster == nullptr)   //找不到该图片
    {
        problemLoading("'monster.png'");
    }
    else
    {
        //设置比例
        monster->setScale(0.9);

        //放置图片
        monster->setPosition(Vec2(origin.x + visibleSize.width / 5, origin.y + visibleSize.height*0.8));

        //从上到下
        auto monster_move1 = MoveTo::create(1.25, Vec2(monster->getPositionX(), monster->getPositionY() - 25));

        //从下到上
        auto monster_move2 = MoveTo::create(1.25, Vec2(monster->getPositionX(), monster->getPositionY() + 25));

        //动作序列，先从左到右，暂停0s，回到原来位置
        auto monster_sequence = Sequence::create(monster_move1, DelayTime::create(0), monster_move2, nullptr);

        //无限循环怪物动作序列
        monster->runAction(RepeatForever::create(monster_sequence));
        
        //将怪物加入场景中
        this->addChild(monster);
    }


    //创建菜单
    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
 

    //冒险模式
    auto AdventureModel_Item = MenuItemImage::create("/MenuScene/AdventureModel.png", "/MenuScene/AdventureModelSelected.png", CC_CALLBACK_1(MenuScene::goto_adventure, this));

    if (AdventureModel_Item == nullptr    || AdventureModel_Item->getContentSize().width <= 0 ||AdventureModel_Item->getContentSize().height <= 0) {
        problemLoading("'AdventureModel.png'and 'AdventureModelSelected.png'");
    }
    else {
        //设置比例
        AdventureModel_Item->setScale(0.9);

        //放置图片
        AdventureModel_Item->setPosition(Vec2(origin.x + visibleSize.width / 5, origin.y + visibleSize.height / 8));

        //将冒险模式加入菜单中
        menu->addChild(AdventureModel_Item);
    }


    //BOSS模式按键
    auto BossModel_Item = MenuItemImage::create("/MenuScene/BossModel.png", "/MenuScene/BossModelSelected.png", CC_CALLBACK_1(MenuScene::CloseCallback, this));

    if (BossModel_Item == nullptr || BossModel_Item->getContentSize().width <= 0 || BossModel_Item->getContentSize().height <= 0) {
        problemLoading("'BosseModel.png' and 'BosseModelSelected.png'");
    }
    else {
        //设置比例
        BossModel_Item->setScale(0.9);

        //放置图片
        BossModel_Item->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 8));

        //将BOSS模式加入菜单中
        menu->addChild(BossModel_Item);
    }

    //怪物窝按键
    auto MonsterNest_Item = MenuItemImage::create("/MenuScene/MonsterNest.png", "/MenuScene/MonsterNestSelected.png", CC_CALLBACK_1(MenuScene::CloseCallback, this));

    if (MonsterNest_Item == nullptr || MonsterNest_Item->getContentSize().width <= 0 || MonsterNest_Item->getContentSize().height <= 0) {
        problemLoading("'MonsterNest.png' and 'MonsterNestSelected.png'");
    }
    else {
        //设置比例
        MonsterNest_Item->setScale(0.9);

        //放置图片
        MonsterNest_Item->setPosition(Vec2(origin.x + visibleSize.width / 5 * 4, origin.y + visibleSize.height / 8));

        //将怪物窝加入菜单中
        menu->addChild(MonsterNest_Item);
    }

    //设置按键
    auto Set_Item = MenuItemImage::create("/MenuScene/Set.png", "/MenuScene/SetSelected.png", CC_CALLBACK_1(MenuScene::CloseCallback, this));
    if (Set_Item == nullptr) {
        problemLoading("'Set.png' and 'SetSelected.png'");
    }
    else {
        //放置图片
        Set_Item->setPosition(Vec2(origin.x + visibleSize.width / 5, origin.y + visibleSize.height / 3));

        //将设置按键加入菜单中
        menu->addChild(Set_Item);
    }

    //帮助按键
    auto Help_Item = MenuItemImage::create("/MenuScene/Help.png", "/MenuScene/HelpSelected.png", CC_CALLBACK_1(MenuScene::CloseCallback, this));
    if (Help_Item == nullptr) {
        problemLoading("'Help.png' and 'HelpSelected.png'");
    }
    else {
        //放置图片
        Help_Item->setPosition(Vec2(origin.x + visibleSize.width / 5 * 4 , origin.y + visibleSize.height / 3));

        //将帮助按键加入菜单
        menu->addChild(Help_Item);
    }



    //将菜单按键加入场景中
    this->addChild(menu);

    return true;

}


void  MenuScene::goto_adventure(Ref* psender) 
{
    //创建冒险模式选关场景
    auto GameScene1 = Scene1::createScene();

    //淡出，切换场景
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