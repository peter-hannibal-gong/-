#include "Scene1.h"
#include "ui/CocosGUI.h"
#include"FlyMonster.h"
#include"PinkMonster.h"
#include"GreenMonster.h"
#include "TowerShit.h"
#include"TowerBottle.h"
#include"MonsterFactory.h"
#include"carrot.h"
#include<vector>
#include"LevelSelectionScene.h"

//暂时存储要进行操作的位置
int gchx = -1;
int gchy = -1;
int TowerType;
std::vector <FlyMonster*> m;  //用于存放怪物
Scene* se; //保存当前的场景
int type_monster = 1;  //当前要生产的怪物类型

/*创建舞台*/
Scene* Scene1::createScene()
{
    return Scene1::create();
}

/*错误判断*/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in Scene1.cpp\n");
}

/*将坐标转化为格点坐标*/
Position Scene1::transition(int x, int y)
{
    Position p; 
    
    p.i = 6 - (y / 80);
    p.j = (x / 80) ;
   
    return p;
}

/*初始化*/
bool Scene1::init()
{

    if (!Scene::init())
    {
        return false;
    }
    //清空保存怪物的vector数组
    m.clear();   

    //获取分辨率（窗口大小）
    auto visibleSize = Director::getInstance()->getVisibleSize(); 
    //原点位置
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    se = this;

    //添加背景
    auto background = Sprite::create("/Theme/Theme1/background.png"); 
    if (background == nullptr)
    {
        problemLoading("'/Theme/Theme1/background.png'");
    }
    else {
        this->addChild(background, 0);
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    }

    // 添加地图
    auto map01 = Sprite::create("/Theme/Theme1/map01.png");
    if (map01 == nullptr)
    {
        problemLoading("'/Theme/Theme1/map01.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        map01->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 80));

        // add the sprite as a child to this layer
        this->addChild(map01, 0);
    }

    // 添加怪物木牌
    auto Board = Sprite::create("Board.png");
    if (Board == nullptr)
    {
        problemLoading("'Board.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        Board->setPosition(Vec2(visibleSize.width / 12*2-40 + origin.x, visibleSize.height /7*5+20 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(Board, 0);
    }


    // 添加菜单图片
    auto Menu_Sprite = Sprite::create("/Theme/Theme1/menu.png");
    if (Menu_Sprite == nullptr)
    {
        problemLoading("'/Theme/Theme1/menu.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        Menu_Sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height  + origin.y - Menu_Sprite->getContentSize().height / 2));

        // add the sprite as a child to this layer
        this->addChild(Menu_Sprite, 0);
    }

    /*---------------money显示---------------*/

    //将钱转化为字符串，用32号字显示
    auto Money_Label = Label::createWithTTF(std::to_string(money), "/fonts/Marker Felt.ttf", 28);

    Money_Label->setName("MoneyLabel");
    //设置锚点
    Money_Label->setAnchorPoint(Vec2(0, 0.5));

    Money_Label->setPosition(Vec2(origin.x + visibleSize.width * 0.11,origin.y + visibleSize.height * 0.95));
    this->addChild(Money_Label);


    /*---------------波数显示---------------*/

    //波数面板显示
    auto Wave_Board = Sprite::create("/Theme/Theme1/Wave_Board.png");
    Wave_Board->setPosition(Vec2(origin.x + visibleSize.width * 0.43,origin.y + visibleSize.height * 0.95));
    this->addChild(Wave_Board);

    //当前波数显示
    auto Wave_Label = Label::createWithTTF(std::to_string(wave / 10 % 10) + "    " + std::to_string(wave % 10), "/fonts/Marker Felt.ttf", 28);
    Wave_Label->setName("WavesLabel");
    Wave_Label->setColor(Color3B::YELLOW);
    Wave_Label->setPosition(Vec2(origin.x + visibleSize.width * 0.43,origin.y + visibleSize.height * 0.94));
    this->addChild(Wave_Label);

    //总波数显示
    auto TotalWave_Label = Label::createWithTTF("/ " + std::to_string(Total_Wave_Number) + "Waves", "/fonts/Marker Felt.ttf", 28);
    TotalWave_Label->setPosition(Vec2(origin.x + visibleSize.width * 0.55,origin.y + visibleSize.height * 0.94));
    this->addChild(TotalWave_Label);

    /*-------------倍速开关显示-------------*/
 
    //创建精灵及对应的菜单项
    auto Normal_Speed_Item = Sprite::create("/Theme/Theme1/NormalSpeed.png");
    auto speed_up_off = MenuItemSprite::create(Normal_Speed_Item, Normal_Speed_Item);

    auto Double_Speed_Item = Sprite::create("/Theme/Theme1/DoubleSpeed.png");
    auto speed_up_on = MenuItemSprite::create(Double_Speed_Item, Double_Speed_Item);

    //创建倍速开关的切换菜单项
    auto SpeedItemtoggle = MenuItemToggle::createWithCallback([&](Ref* psender) {
        //若菜单项被点击，切换倍速的模式
        if (Acceleration_Switch == 0) {
            Acceleration_Switch = 1;
        }
        else {
            Acceleration_Switch = 0;
        }
        }, speed_up_off, speed_up_on, nullptr);
    //将菜单项加入菜单中，放置在适合的位置
    auto menu = Menu::create(SpeedItemtoggle,nullptr);
    SpeedItemtoggle->setPosition(Vec2(origin.x + visibleSize.width * 0.72, origin.y + visibleSize.height * 0.94));

    //放置菜单，将菜单加入场景中
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);  

    
    /*-------------暂停按键显示-------------*/

    //创建“暂停中”图标
    auto Pause_Sprite = Sprite::create("/Theme/Theme1/paused.png");
    if (Pause_Sprite == nullptr)
    {
        problemLoading("'/Theme/Theme1/paused.png'");
    }
    else
    {
        Pause_Sprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.95));
        this->addChild(Pause_Sprite);  
        //初始为不可见
        Pause_Sprite->setVisible(false);
        Pause_Sprite->setScale(1.2);
    }


    //创建精灵及对应的菜单项
    auto Pause_off_Item = Sprite::create("/Theme/Theme1/PauseOff.png");
    auto Pause_off = MenuItemSprite::create(Pause_off_Item, Pause_off_Item);
    auto Pause_on_Item = Sprite::create("/Theme/Theme1/PauseOn.png");
    auto Pause_on = MenuItemSprite::create(Pause_on_Item, Pause_on_Item);

    //创建暂停开关的切换菜单项
    auto PauseItemtoggle = MenuItemToggle::createWithCallback([=](Ref* psender) {
        //播放音效
        if (Pause_Switch == 0) {
            Pause_Switch = 1;
            //“暂停中”可见
            Pause_Sprite->setVisible(true);
            //波数显示关闭
            Wave_Board->setVisible(false);
            Wave_Label->setVisible(false);
            TotalWave_Label->setVisible(false);
        }
        else {
            Pause_Switch = 0;
            //“暂停中”不可见
            Pause_Sprite->setVisible(false);
            //波数显示开启
            Wave_Board->setVisible(true);
            Wave_Label->setVisible(true);
            TotalWave_Label->setVisible(true);
        }
        }, Pause_off, Pause_on, nullptr);

    //将菜单项放置在合适位置，加入菜单中
    PauseItemtoggle->setPosition(Vec2(origin.x + visibleSize.width * 0.83,origin.y + visibleSize.height * 0.94));
    menu->addChild(PauseItemtoggle);

    /*-------------选项按键显示-------------*/

    //auto MenuItem = Button::create("/GameScene/touming-hd.pvr_28.PNG", "/GameScene/touming-hd.pvr_26.PNG");



    //触摸格点显示格子
    Sprite* grid[7][12];
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 12; j++) {
            //将格子加入场景中
            grid[i][j] = Sprite::create("Grid.png");
            grid[i][j]->setPosition(Vec2(40 + 80 * j, 40 + (6 - i)*80));
            this->addChild(grid[i][j], 2);

            //设置标签值
            grid[i][j]->setTag(i * 100 + j);  

            //初始为不可见
            grid[i][j]->setVisible(false); 
          
        }
    }

    //炮塔显示数组,四维分别为7行，12列，2种塔，塔的可购买和不可购买图片
    Sprite* Tower[7][12][2][2];
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 12; j++) {

            //图标初始均为不可见
            /*-------------------------瓶子炮塔------------------------*/
            //不可购买图标
            Tower[i][j][0][0] = Sprite::create("Theme/Theme1/TBottle0.png");
            Tower[i][j][0][0]->setPosition(Vec2(grid[i][j]->getPosition().x - Tower[i][j][0][0]->getContentSize().width / 2,
                grid[i][j]->getPosition().y + Tower[i][j][0][0]->getContentSize().height));
            this->addChild(Tower[i][j][0][0],2);
            Tower[i][j][0][0]->setVisible(false);
            Tower[i][j][0][0]->setTag(100*i+j+1000);

            //可购买图标
            Tower[i][j][0][1] = Sprite::create("Theme/Theme1/TBottle1.png");
            Tower[i][j][0][1]->setPosition(Vec2(grid[i][j]->getPosition().x - Tower[i][j][0][1]->getContentSize().width / 2,
                grid[i][j]->getPosition().y + Tower[i][j][0][1]->getContentSize().height));
            this->addChild(Tower[i][j][0][1],2);
            Tower[i][j][0][1]->setVisible(false);
            Tower[i][j][0][1]->setTag(100 * i + j +2000);

            /*-------------------------便便炮塔------------------------*/
            //不可购买图标
            Tower[i][j][1][0] = Sprite::create("Theme/Theme1/TShit0.png");
            Tower[i][j][1][0]->setPosition(Vec2(grid[i][j]->getPosition().x + Tower[i][j][1][0]->getContentSize().width / 2,
                grid[i][j]->getPosition().y + Tower[i][j][1][0]->getContentSize().height));
            this->addChild(Tower[i][j][1][0],2);
            Tower[i][j][1][0]->setVisible(false);
            Tower[i][j][1][0]->setTag(100 * i + j+3000);

            //可购买图标
            Tower[i][j][1][1] = Sprite::create("Theme/Theme1/TShit1.png");
            Tower[i][j][1][1]->setPosition(Vec2(grid[i][j]->getPosition().x + Tower[i][j][1][1]->getContentSize().width / 2,
                grid[i][j]->getPosition().y + Tower[i][j][1][1]->getContentSize().height));
            this->addChild(Tower[i][j][1][1],2);
            Tower[i][j][1][1]->setVisible(false);
            Tower[i][j][1][1]->setTag(100 * i + j + 4000);
        }



    //Game_Start();

  

    auto mouseListener = EventListenerMouse::create();

    mouseListener->onMouseDown = CC_CALLBACK_1(Scene1::gch_onMouseDown, this);


    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    
   
    auto carrot = Carrot::createSprite();
    carrot->setTag(-10);
    carrot->setPosition(Vec2(80*11-40,80*6));
    this->addChild(carrot);
    //auto flymonster = FlyMonster::createSprite();
    //this->addChild(flymonster, 2);

    //auto pinkmonster = PinkMonster::createSprite();
    //this->addChild(pinkmonster,2);

    //auto greenmonster = GreenMonster::createSprite();
    //this->addChild(greenmonster,2);

    //0.2秒刷新一次金钱
    schedule(CC_SCHEDULE_SELECTOR(Scene1::updateMoney), 0.2f);

    //10秒刷新波数
    schedule(CC_SCHEDULE_SELECTOR(Scene1::updateWave), 3.0f);

    //每1秒出现一只怪物 
    schedule(CC_SCHEDULE_SELECTOR(Scene1::updateMonster), 1.0f);
    
    //监测活着的怪物
    schedule(CC_SCHEDULE_SELECTOR(Scene1::AliveMonster), 0.2f);

    //监测是否有怪物到达萝卜处吃掉萝卜
    schedule(CC_SCHEDULE_SELECTOR(Scene1::If_Attack_Carrot), 0.2f);

   


    
    return true;
}

/*实时更新金钱*/
void Scene1::updateMoney(float dt)
{
    //根据当前的money更新label
    auto node = getChildByName("MoneyLabel");

    Label* Money_Label = static_cast<Label*>(node);

    Money_Label ->setString(std::to_string(money));

}

/*实时更新波数*/
void Scene1::updateWave(float dt)
{
    
    //波数加一，并且更新显示
    wave++;
    if (wave <= Total_Wave_Number) {
        auto node = getChildByName("WavesLabel");

        Label* Wave_Label = static_cast<Label*>(node);

        Wave_Label->setString(std::to_string(wave / 10 % 10) + "    " + std::to_string(wave % 10));

    }
    else { //超过最大波数不更新波数标签
        //游戏结束，若萝卜还有血量，则游戏结束
        //跳转

    }
    //当进行到最后一波时，停止计数
    if (wave == Total_Wave_Number+1) {
        unschedule(CC_SCHEDULE_SELECTOR(Scene1::updateWave)); 
    }

}

/*间隔一定时间生产怪物*/
void Scene1::updateMonster(float dt)
{
  
    //定义一个怪物工厂，用于产生怪物
    MonsterFactory p;

    //通过数组位置保存的怪物类型，生成相应类型的怪物
    type_monster = Monster_Wave[wave - 1][Monster_Order];
    Sprite* sp = p.Produce_Monster(Monster_Wave[wave - 1][Monster_Order]);
    FlyMonster* Monster = dynamic_cast<FlyMonster*>(sp);

    
    this->addChild(Monster);

    //将怪物放入vector数组中
    m.push_back(Monster);
  
    //当前这只怪在当前波的序号
    Monster_Order = (Monster_Order + 1) % Monster_Number;

    //当进行到最后一波的最后一只怪物的时候,停止计数
    if (wave == Total_Wave_Number&& Monster_Order== Monster_Number-1) {
        unschedule(CC_SCHEDULE_SELECTOR(Scene1::updateMonster));
    }

}

//监测是否有怪物到达终点，吃到萝卜
void Scene1::If_Attack_Carrot(float dt)
{

    int count = 0;
    Node* n = this->getChildByTag(-10);
    Carrot* carrot = static_cast<Carrot*>(n);
   
    for (int i = 0; i < m.size(); i++) 
        if (m[i]->getHp() > 0) { //活着        
            int x = m[i]->getPosition().x;
            int y = m[i]->getPosition().y;

            if (x >= 10 * 80 && x <= 10 * 80 + 80 && y >= 5 * 80 && y <= 5 * 80 + 80) //如果在终点
                count++;

        }
    //
    int f=carrot->SetHp(count);
    if (f) {  //如果萝卜血量为0，跳转
        goto_LevelSelection();
    }
        
}

/*跳转到关卡选择界面*/
void  Scene1::goto_LevelSelection()
{
    //创建冒险模式选关场景
    auto LevelSelection = LevelSelectionScene::createScene();

    //淡出，切换场景
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, LevelSelection));
}

//实时更新怪物是否死亡
void Scene1::AliveMonster(float dt)
{
    for (int i = 0; i < m.size(); i++)  
        if (m[i]->getHp() <= 0 && m[i]->survival==1) {    //如果怪物的血量小于等于0，将其存活状态变成0
            money = money + m[i]->getValue();   //加钱
            m[i]->survival = 0;                 //存活状态变成0
        }
    
}

/*鼠标事件*/
void Scene1::gch_onMouseDown(Event* event)
{

    //获取事件
    EventMouse* e = (EventMouse*)event;

    //获取鼠标位置
    int x = e->getCursorX();
    int y = e->getCursorY();

    //点击的位置在菜单栏
    if (y >= 560)
        return;

    //当前鼠标点击的格子位置
    Position p = transition(x, y);

    //通过标签来获取当前的格子 
    Node* n = this->getChildByTag(p.i * 100 + p.j);
    Sprite* Grid_Selcted = static_cast<Sprite*>(n);
    //点击史
    if (grid_is_visible == 0 &&range_is_visible==0 && Map1[p.i][p.j]/100 == Shit) {
    
        //通过tag获取点击的炮塔对象
        Node* node = this->getChildByTag(p.i * 100 + p.j + 5000);
        TowerShit* Tower = static_cast<TowerShit*>(node);
        Tower->Show_RangeAndGrade(this,money);
                  
        range_is_visible = 1;
        TowerType = Shit; //当前显示范围的炮塔为便便
        gchx = p.i;
        gchy = p.j;   //保存当前塔的位置
        return;
    } 
    //点击瓶子
    else if (grid_is_visible == 0 && range_is_visible == 0 && Map1[p.i][p.j] / 100 == Bottle) {
        //瓶子升级界面

        //通过tag获取点击的炮塔对象
        Node* node = this->getChildByTag(p.i * 100 + p.j + 11000);
        TowerBottle* Tower = static_cast<TowerBottle*>(node);
        Tower->Show_RangeAndGrade(this, money);

        range_is_visible = 1;
        TowerType = Bottle; //当前显示范围的炮塔为便便
        gchx = p.i;
        gchy = p.j;   //保存当前塔的位置
        return;
    }

    //点击道路
    else if (grid_is_visible == 0 && range_is_visible == 0 && Map1[p.i][p.j] / 100 == LOAD) {
        //有怪打怪，没怪显示红色                                                                                                                  
        return;
    }
    //点击障碍物
    else if (grid_is_visible == 0 && range_is_visible == 0 && Map1[p.i][p.j] / 100 == BLOCK) {
        //优先攻击障碍物
        return;
    }
    //点击位置为空且场上无购买选项
    else if (grid_is_visible == 0 && range_is_visible == 0 && Map1[p.i][p.j]/100 == EMPTY)
    {
        Grid_Selcted->setVisible(true);
        grid_is_visible = 1;

        gchx = p.i;
        gchy = p.j;
        //其他格子不显示
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 12; j++) {
                if (i * 100 + j != p.i * 100 + p.j) {

                    //通过标签来获取该位置的格子
                    Node* n = this->getChildByTag(i * 100 + j);
                    Sprite* Grid_Selcted1 = static_cast<Sprite*>(n);

                    //不显示
                    Grid_Selcted1->setVisible(false);
                }
            }
        }
        //显示购买界面
        auto Tower1 = Sprite::create();
        auto Tower2 = Sprite::create();

        //钱不够显示灰色界面，钱够显示有色界面
        if (money < 100) {
            Node* n = this->getChildByTag(p.i * 100 + p.j + 1000);
            Tower1 = static_cast<Sprite*>(n);
        }
        else {
            Node* n = this->getChildByTag(p.i * 100 + p.j + 2000);
            Tower1 = static_cast<Sprite*>(n);
        }

        if (money < 120) {
            Node* n = this->getChildByTag(p.i * 100 + p.j + 3000);
            Tower2 = static_cast<Sprite*>(n);
        }
        else {
            Node* n = this->getChildByTag(p.i * 100 + p.j + 4000);
            Tower2 = static_cast<Sprite*>(n);
        }

        Tower1->setVisible(true);
        Tower2->setVisible(true);
    }

    //场上有购买界面
    else if (grid_is_visible == 1) {
        //显示格子的时候，若点击，需要判断是否购买炮塔和取消显示
        grid_is_visible = 0;
        Sprite* Grid_Selected;
        Sprite* Tower1;
        Sprite* Tower2;

        int i1, j1;
        int x1;
        int y1;  //保存当前显示的格子的位置

        //获取当前显示的格子的位置
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 12; j++) {
                //通过标签来获取该位置的格子
                Node* n = this->getChildByTag(i * 100 + j);
                Sprite* Grid = static_cast<Sprite*>(n);

                if (Grid->isVisible()) {
                    Grid_Selected = Grid;
                    x1 = 40 + 80 * j;
                    y1 = 40 + (6 - i) * 80;
                    i1 = i;
                    j1 = j;
                }
            }
        }
        //获取当前显示的购买界面的位置
        for (int i = 0; i < 7; i++)
            for (int j = 0; j < 12; j++)
                for (int k = 0; k <= 1; k++)
                    for (int t = 0; t <= 1; t++) {
                        Node* n = this->getChildByTag(i * 100 + j + (k * 2 + t + 1) * 1000);
                        Sprite* Tower = static_cast<Sprite*>(n);

                        if (Tower->isVisible()) {
                            if (k == 0)
                                Tower1 = Tower;

                            if (k == 1)
                                Tower2 = Tower;
                        }

                    }

        //若按下位置在第一个炮塔图标内
        if (x >= Tower1->getPosition().x - Tower1->getContentSize().width / 2 &&
            x <= Tower1->getPosition().x + Tower1->getContentSize().width / 2 &&
            y >= Tower1->getPosition().y - Tower1->getContentSize().height / 2 &&
            y <= Tower1->getPosition().y + Tower1->getContentSize().height / 2) {
            if (money >= 100) {//若钱够，则建造

                log("build_tower(position, tower_available[0])");

                //花钱
                money = money - 100;

                //格子不可见
                Grid_Selcted->setVisible(false);


                //地图上该点为炮塔
                //Map1[p.i][p.j] = Bottle1;
                Map1[gchx][gchy] = Bottle1;
                gchx = -1;
                gchy = -1;

                //建造便便炮塔
                auto Bottle_Tower = TowerBottle::createSprite();

                //设置该塔的标签
                Bottle_Tower->setTag(100 * i1 + j1 + 11000);
                //建造瓶子炮塔
             
                Bottle_Tower->setPosition(Vec2(x1, y1));
                //Bottle_Tower->setTag(x1 * 1000 + y1 * 10);
                this->addChild(Bottle_Tower);

            }
        }
        else if (//若按下位置在第二个炮塔图标内
            x >= Tower2->getPosition().x - Tower2->getContentSize().width / 2 &&
            x <= Tower2->getPosition().x + Tower2->getContentSize().width / 2 &&
            y >= Tower2->getPosition().y - Tower2->getContentSize().height / 2 &&
            y <= Tower2->getPosition().y + Tower2->getContentSize().height / 2) {
            if (money >= 120) {//若钱够，则建造
                // build_tower(position, tower_available[1]);
                log("build_tower(position, tower_available[1])");

                //花钱
                money = money - 120;

                //格子不可见
                Grid_Selcted->setVisible(false);

                //地图上该点为便便炮塔
                Map1[gchx][gchy] = Shit1;

                //建造便便炮塔
                auto Shit_Tower = TowerShit::createSprite();

                //设置该塔的标签
                Shit_Tower->setTag(100*i1+j1+5000);

                //auto Shit_Tower = Sprite::create("Theme/Shit/SmallShit.png");
                Shit_Tower->setPosition(Vec2(x1, y1));
                //Shit_Tower->setTag(x1 * 10000 + y1 * 100);
                this->addChild(Shit_Tower);

             
            }

        }

        //都不可见
        Grid_Selected->setVisible(false);
        Tower1->setVisible(false);
        Tower2->setVisible(false);
    }
    //场上有攻击范围显示和升级界面
    else if (range_is_visible == 1) {

        int f = 1;  //判断是否卖出
        if (TowerType == Shit) {
            Node* node = this->getChildByTag(gchx * 100 + gchy + 5000);
            TowerShit* Tower = static_cast<TowerShit*>(node);

            //若按下的位置在升级位置
            if ((x >= gchy * 80 && x <= gchy * 80 + 80 && y >= (6 - gchx) * 80 + 80 && y <= (6 - gchx) * 80 + 160)) {
                if (money >= Tower->upgradecost[Tower->level]) { //钱够
                    //升级，更换塔的形象
                    Tower->Upgrade(this);
                    //Tower->attack(this, Tower->getPosition(), Vec2(100, 100));
                    //扣钱
                    money = money - Tower->upgradecost[Tower->level];
                }

            }//若按下的位置在出售位置
            else if ((x >= gchy * 80 && x <= gchy * 80 + 80 && y >= (6 - gchx) * 80 - 80 && y <= (6 - gchx) * 80)) {
                //加钱
                money = money + Tower->value[Tower->level];
                //删除该炮塔
                //Node* node = static_cast<Node*>(Tower);
                Tower->stopschedule();
                Tower->Hide_RangeAndGrade(this);  //取消显示范围要在删除之前
                Tower->removeFromParent();
                f = 0;
                //Tower->setVisible(false);
                //delete Tower;
                Map1[gchx][gchy] = EMPTY;
            }
            if (f)
                Tower->Hide_RangeAndGrade(this);

            //点击完成后范围不可见
            range_is_visible = 0;
        }
        if (TowerType == Bottle) {
            Node* node = this->getChildByTag(gchx * 100 + gchy + 11000);
            TowerBottle* Tower = static_cast<TowerBottle*>(node);

            //若按下的位置在升级位置
            if ((x >= gchy * 80 && x <= gchy * 80 + 80 && y >= (6 - gchx) * 80 + 80 && y <= (6 - gchx) * 80 + 160)) {
                if (money >= Tower->upgradecost[Tower->level]) { //钱够
                    //升级，更换塔的形象
                    Tower->Upgrade(this);
                    //Tower->attack(this, Tower->getPosition(), Vec2(100, 100));
                    //扣钱
                    money = money - Tower->upgradecost[Tower->level];
                }

            }//若按下的位置在出售位置
            else if ((x >= gchy * 80 && x <= gchy * 80 + 80 && y >= (6 - gchx) * 80 - 80 && y <= (6 - gchx) * 80)) {
                //加钱
                money = money + Tower->value[Tower->level];
                //删除该炮塔
                //Node* node = static_cast<Node*>(Tower);
                Tower->stopschedule();
                Tower->Hide_RangeAndGrade(this);  //取消显示范围要在删除之前
                Tower->removeFromParent();
                f = 0;
                //Tower->setVisible(false);
                //delete Tower;
                Map1[gchx][gchy] = EMPTY;
            }
            if (f)
                Tower->Hide_RangeAndGrade(this);

            //点击完成后范围不可见
            range_is_visible = 0;
        }
    }
    else {
            auto lllzty = Sprite::create("grossini.png");
            lllzty->setPosition(Vec2(100, 100));
            this->addChild(lllzty, 3);
        }

    
}

/*鼠标点击显示格子和购买炮塔界面*/
void Scene1::onMouseDown(Event* event)
{
    //获取事件
    EventMouse* e = (EventMouse*)event;
    
    //获取鼠标位置
    int x = e->getCursorX();
    int y = e->getCursorY();
    
    if (y < 560) {   //点击的位置不在菜单栏

        //当前鼠标点击的格子位置
        Position p = transition(x, y);

        //通过标签来获取当前的格子 
        Node* n = this->getChildByTag(p.i * 100 + p.j);
        Sprite* Grid_Selcted = static_cast<Sprite*>(n);

        //未显示格子的时候，若点击，需要显示格子和购买界面
        if (grid_is_visible == 0) {

            //该位置不是可放置的点
            if (Map1[p.i][p.j] / 100 != EMPTY) {
                return;
            }
                
             
            Grid_Selcted->setVisible(true);
            grid_is_visible = 1;

            //其他格子不显示
            for (int i = 0; i < 7; i++)
                for (int j = 0; j < 12; j++)
                    if (i * 100 + j != p.i * 100 + p.j) {

                        //通过标签来获取该位置的格子
                        Node* n = this->getChildByTag(i * 100 + j);
                        Sprite* Grid_Selcted1 = static_cast<Sprite*>(n);

                        //不显示
                        Grid_Selcted1->setVisible(false);
                    }


            //显示购买界面
            auto Tower1 = Sprite::create();
            auto Tower2 = Sprite::create();

            //钱不够显示灰色界面，钱够显示有色界面
            if (money < 100) {
                Node* n = this->getChildByTag(p.i * 100 + p.j +1000);
                Tower1 = static_cast<Sprite*>(n);
            }
            else {
                Node* n = this->getChildByTag(p.i * 100 + p.j +2000);
                Tower1 = static_cast<Sprite*>(n);
            }

            if (money < 120) {
                Node* n = this->getChildByTag(p.i * 100 + p.j + 3000);
                Tower2 = static_cast<Sprite*>(n);
            }
            else {
                Node* n = this->getChildByTag(p.i * 100 + p.j + 4000);
                Tower2 = static_cast<Sprite*>(n);
            }

            Tower1->setVisible(true);
            Tower2->setVisible(true);


        }
        else { //显示格子的时候，若点击，需要判断是否购买炮塔和取消显示
            grid_is_visible = 0;
            Sprite* Grid_Selected;
            Sprite* Tower1;
            Sprite* Tower2;

            int i1;
            int j1;

            int x1;
            int y1;  //保存当前显示的格子的位置

            //获取当前显示的格子的位置
            for (int i = 0; i < 7; i++)
                for (int j = 0; j < 12; j++) {
                    //通过标签来获取该位置的格子
                    Node* n = this->getChildByTag(i * 100 + j);
                    Sprite* Grid = static_cast<Sprite*>(n);

                    if (Grid->isVisible()) {
                        Grid_Selected = Grid;
                        x1 = 40 + 80 * j;
                        y1 = 40 + (6 - i) * 80;
                        i1 = i;
                        j1 = j;
                    }

                }

            //获取当前显示的购买界面的位置
            for (int i = 0; i < 7; i++)
                for (int j = 0; j < 12; j++)
                    for (int k = 0; k <= 1; k++)
                        for (int t = 0; t <= 1; t++) {
                            Node* n = this->getChildByTag(i * 100 + j  + (k*2+t+1)*1000);
                            Sprite* Tower = static_cast<Sprite*>(n);

                            if (Tower->isVisible()) {
                                if (k == 0)
                                    Tower1 = Tower;

                                if (k == 1)
                                    Tower2 = Tower;
                            }

                        }

            //若按下位置在第一个炮塔图标内
            if (x >= Tower1->getPosition().x - Tower1->getContentSize().width / 2 &&
                x <= Tower1->getPosition().x + Tower1->getContentSize().width / 2 &&
                y >= Tower1->getPosition().y - Tower1->getContentSize().height / 2 &&
                y <= Tower1->getPosition().y + Tower1->getContentSize().height / 2) {
                if (money >= 100) {//若钱够，则建造

                    log("build_tower(position, tower_available[0])");

                    //花钱
                    money = money - 100;

                    //格子不可见
                    Grid_Selcted->setVisible(false);


                    //地图上该点为炮塔
                    Map1[p.i][p.j] = Bottle1;
                    //建造瓶子炮塔
                    auto Bottle_Tower = Sprite::create("Theme/Bottle/SmallBottle.png");
                    Bottle_Tower->setPosition(Vec2(x1, y1));
                    //Bottle_Tower->setTag(x1 * 1000 + y1 * 10);
                    this->addChild(Bottle_Tower);

                }
            }
            else if (//若按下位置在第二个炮塔图标内
                x >= Tower2->getPosition().x - Tower2->getContentSize().width / 2 &&
                x <= Tower2->getPosition().x + Tower2->getContentSize().width / 2 &&
                y >= Tower2->getPosition().y - Tower2->getContentSize().height / 2 &&
                y <= Tower2->getPosition().y + Tower2->getContentSize().height / 2) {
                if (money >= 120) {//若钱够，则建造
                    // build_tower(position, tower_available[1]);
                    log("build_tower(position, tower_available[1])");

                    //花钱
                    money = money - 120;

                    //格子不可见
                    Grid_Selcted->setVisible(false);

                    //地图上该点为炮塔
                    Map1[p.i][p.j] = Shit1;

                    //建造便便炮塔
                    auto Shit_Tower = TowerShit::createSprite();
                    Shit_Tower->setTag(i1*100+j1+5000);

                    //auto Shit_Tower = Sprite::create("Theme/Shit/SmallShit.png");
                    Shit_Tower->setPosition(Vec2(x1, y1));
                    //Shit_Tower->setTag(x1 * 10000 + y1 * 100);
                    this->addChild(Shit_Tower);
                }

            }

            //都不可见
            Grid_Selected->setVisible(false);
            Tower1->setVisible(false);
            Tower2->setVisible(false);
        }
    }



}

/*游戏开始时倒计时*/
void Scene1::Game_Start()
{
    //获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //暂停游戏主循环
    Director::getInstance()->pause();

    //创建倒计时界面所在的层
    auto CountDown_layer = Layer::create();
    CountDown_layer->setPosition(Vec2::ZERO);
    this->addChild(CountDown_layer);

    //倒计时的背景
    auto CountDownBackground = Sprite::create("/Theme/Theme1/CountDownBackground.png");
    CountDownBackground->setPosition(Vec2(origin.x + visibleSize.width / 2,origin.y + visibleSize.height / 2));
    CountDown_layer->addChild(CountDownBackground);
    //三秒后淡出
    CountDownBackground->runAction(Sequence::create(DelayTime::create(3), FadeOut::create(0.1), nullptr));

    //倒计时圈
    auto Circle = Sprite::create("/Theme/Theme1/CountDownCircle.png");
    Circle->setPosition(Vec2(origin.x + visibleSize.width /2, origin.y + visibleSize.height / 2));
    CountDown_layer->addChild(Circle);
    //旋转360度重复三轮，淡出
    Circle->runAction(Sequence::create(Repeat::create(RotateBy::create(1, -360), 3), FadeOut::create(0.1), nullptr));

    //倒计时的数字3
    auto number3 = Sprite::create("/Theme/Theme1/Number3.png");
    number3->setPosition(Vec2(origin.x + visibleSize.width * 0.51,origin.y + visibleSize.height / 2));
    CountDown_layer->addChild(number3);

    //数字倒计时的动画
    Vector<SpriteFrame*> frame;
    frame.pushBack(SpriteFrame::create("/Theme/Theme1/Number3.png", Rect(0, 0, 95, 114)));
    frame.pushBack(SpriteFrame::create("/Theme/Theme1/Number2.png", Rect(0, 0, 95, 114)));
    frame.pushBack(SpriteFrame::create("/Theme/Theme1/Number1.png", Rect(0, 0, 95, 114)));
    number3->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 1)), FadeOut::create(0.2), nullptr));
      
    //倒计时的时候所有可用格点闪烁
    Sprite* grid[7][12];
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 12; j++) {
            grid[i][j] = Sprite::create("StartGrid.png");
            if (Map1[i][j] == 0) {
                //设置透明度
                //grid[i][j]->setOpacity(100);
                //三秒内闪烁2次
                //grid[i][j]->runAction(Blink::create(3, 2));
            }
        }
    }
    //淡出，删除倒计时所在的层
    CountDown_layer->runAction(Sequence::create(DelayTime::create(3.1), FadeOut::create(0.1), nullptr));
    
    //恢复游戏主循环
    Director::getInstance()->resume();
    

}


void Scene1::CloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
