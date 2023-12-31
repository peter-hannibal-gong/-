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

//��ʱ�洢Ҫ���в�����λ��
int gchx = -1;
int gchy = -1;
int TowerType;
std::vector <FlyMonster*> m;  //���ڴ�Ź���
Scene* se; //���浱ǰ�ĳ���
int type_monster = 1;  //��ǰҪ�����Ĺ�������

/*������̨*/
Scene* Scene1::createScene()
{
    return Scene1::create();
}

/*�����ж�*/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in Scene1.cpp\n");
}

/*������ת��Ϊ�������*/
Position Scene1::transition(int x, int y)
{
    Position p; 
    
    p.i = 6 - (y / 80);
    p.j = (x / 80) ;
   
    return p;
}

/*��ʼ��*/
bool Scene1::init()
{

    if (!Scene::init())
    {
        return false;
    }
    //��ձ�������vector����
    m.clear();   

    //��ȡ�ֱ��ʣ����ڴ�С��
    auto visibleSize = Director::getInstance()->getVisibleSize(); 
    //ԭ��λ��
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    se = this;

    //��ӱ���
    auto background = Sprite::create("/Theme/Theme1/background.png"); 
    if (background == nullptr)
    {
        problemLoading("'/Theme/Theme1/background.png'");
    }
    else {
        this->addChild(background, 0);
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    }

    // ��ӵ�ͼ
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

    // ��ӹ���ľ��
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


    // ��Ӳ˵�ͼƬ
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

    /*---------------money��ʾ---------------*/

    //��Ǯת��Ϊ�ַ�������32������ʾ
    auto Money_Label = Label::createWithTTF(std::to_string(money), "/fonts/Marker Felt.ttf", 28);

    Money_Label->setName("MoneyLabel");
    //����ê��
    Money_Label->setAnchorPoint(Vec2(0, 0.5));

    Money_Label->setPosition(Vec2(origin.x + visibleSize.width * 0.11,origin.y + visibleSize.height * 0.95));
    this->addChild(Money_Label);


    /*---------------������ʾ---------------*/

    //���������ʾ
    auto Wave_Board = Sprite::create("/Theme/Theme1/Wave_Board.png");
    Wave_Board->setPosition(Vec2(origin.x + visibleSize.width * 0.43,origin.y + visibleSize.height * 0.95));
    this->addChild(Wave_Board);

    //��ǰ������ʾ
    auto Wave_Label = Label::createWithTTF(std::to_string(wave / 10 % 10) + "    " + std::to_string(wave % 10), "/fonts/Marker Felt.ttf", 28);
    Wave_Label->setName("WavesLabel");
    Wave_Label->setColor(Color3B::YELLOW);
    Wave_Label->setPosition(Vec2(origin.x + visibleSize.width * 0.43,origin.y + visibleSize.height * 0.94));
    this->addChild(Wave_Label);

    //�ܲ�����ʾ
    auto TotalWave_Label = Label::createWithTTF("/ " + std::to_string(Total_Wave_Number) + "Waves", "/fonts/Marker Felt.ttf", 28);
    TotalWave_Label->setPosition(Vec2(origin.x + visibleSize.width * 0.55,origin.y + visibleSize.height * 0.94));
    this->addChild(TotalWave_Label);

    /*-------------���ٿ�����ʾ-------------*/
 
    //�������鼰��Ӧ�Ĳ˵���
    auto Normal_Speed_Item = Sprite::create("/Theme/Theme1/NormalSpeed.png");
    auto speed_up_off = MenuItemSprite::create(Normal_Speed_Item, Normal_Speed_Item);

    auto Double_Speed_Item = Sprite::create("/Theme/Theme1/DoubleSpeed.png");
    auto speed_up_on = MenuItemSprite::create(Double_Speed_Item, Double_Speed_Item);

    //�������ٿ��ص��л��˵���
    auto SpeedItemtoggle = MenuItemToggle::createWithCallback([&](Ref* psender) {
        //���˵��������л����ٵ�ģʽ
        if (Acceleration_Switch == 0) {
            Acceleration_Switch = 1;
        }
        else {
            Acceleration_Switch = 0;
        }
        }, speed_up_off, speed_up_on, nullptr);
    //���˵������˵��У��������ʺϵ�λ��
    auto menu = Menu::create(SpeedItemtoggle,nullptr);
    SpeedItemtoggle->setPosition(Vec2(origin.x + visibleSize.width * 0.72, origin.y + visibleSize.height * 0.94));

    //���ò˵������˵����볡����
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);  

    
    /*-------------��ͣ������ʾ-------------*/

    //��������ͣ�С�ͼ��
    auto Pause_Sprite = Sprite::create("/Theme/Theme1/paused.png");
    if (Pause_Sprite == nullptr)
    {
        problemLoading("'/Theme/Theme1/paused.png'");
    }
    else
    {
        Pause_Sprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.95));
        this->addChild(Pause_Sprite);  
        //��ʼΪ���ɼ�
        Pause_Sprite->setVisible(false);
        Pause_Sprite->setScale(1.2);
    }


    //�������鼰��Ӧ�Ĳ˵���
    auto Pause_off_Item = Sprite::create("/Theme/Theme1/PauseOff.png");
    auto Pause_off = MenuItemSprite::create(Pause_off_Item, Pause_off_Item);
    auto Pause_on_Item = Sprite::create("/Theme/Theme1/PauseOn.png");
    auto Pause_on = MenuItemSprite::create(Pause_on_Item, Pause_on_Item);

    //������ͣ���ص��л��˵���
    auto PauseItemtoggle = MenuItemToggle::createWithCallback([=](Ref* psender) {
        //������Ч
        if (Pause_Switch == 0) {
            Pause_Switch = 1;
            //����ͣ�С��ɼ�
            Pause_Sprite->setVisible(true);
            //������ʾ�ر�
            Wave_Board->setVisible(false);
            Wave_Label->setVisible(false);
            TotalWave_Label->setVisible(false);
        }
        else {
            Pause_Switch = 0;
            //����ͣ�С����ɼ�
            Pause_Sprite->setVisible(false);
            //������ʾ����
            Wave_Board->setVisible(true);
            Wave_Label->setVisible(true);
            TotalWave_Label->setVisible(true);
        }
        }, Pause_off, Pause_on, nullptr);

    //���˵�������ں���λ�ã�����˵���
    PauseItemtoggle->setPosition(Vec2(origin.x + visibleSize.width * 0.83,origin.y + visibleSize.height * 0.94));
    menu->addChild(PauseItemtoggle);

    /*-------------ѡ�����ʾ-------------*/

    //auto MenuItem = Button::create("/GameScene/touming-hd.pvr_28.PNG", "/GameScene/touming-hd.pvr_26.PNG");



    //���������ʾ����
    Sprite* grid[7][12];
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 12; j++) {
            //�����Ӽ��볡����
            grid[i][j] = Sprite::create("Grid.png");
            grid[i][j]->setPosition(Vec2(40 + 80 * j, 40 + (6 - i)*80));
            this->addChild(grid[i][j], 2);

            //���ñ�ǩֵ
            grid[i][j]->setTag(i * 100 + j);  

            //��ʼΪ���ɼ�
            grid[i][j]->setVisible(false); 
          
        }
    }

    //������ʾ����,��ά�ֱ�Ϊ7�У�12�У�2���������Ŀɹ���Ͳ��ɹ���ͼƬ
    Sprite* Tower[7][12][2][2];
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 12; j++) {

            //ͼ���ʼ��Ϊ���ɼ�
            /*-------------------------ƿ������------------------------*/
            //���ɹ���ͼ��
            Tower[i][j][0][0] = Sprite::create("Theme/Theme1/TBottle0.png");
            Tower[i][j][0][0]->setPosition(Vec2(grid[i][j]->getPosition().x - Tower[i][j][0][0]->getContentSize().width / 2,
                grid[i][j]->getPosition().y + Tower[i][j][0][0]->getContentSize().height));
            this->addChild(Tower[i][j][0][0],2);
            Tower[i][j][0][0]->setVisible(false);
            Tower[i][j][0][0]->setTag(100*i+j+1000);

            //�ɹ���ͼ��
            Tower[i][j][0][1] = Sprite::create("Theme/Theme1/TBottle1.png");
            Tower[i][j][0][1]->setPosition(Vec2(grid[i][j]->getPosition().x - Tower[i][j][0][1]->getContentSize().width / 2,
                grid[i][j]->getPosition().y + Tower[i][j][0][1]->getContentSize().height));
            this->addChild(Tower[i][j][0][1],2);
            Tower[i][j][0][1]->setVisible(false);
            Tower[i][j][0][1]->setTag(100 * i + j +2000);

            /*-------------------------�������------------------------*/
            //���ɹ���ͼ��
            Tower[i][j][1][0] = Sprite::create("Theme/Theme1/TShit0.png");
            Tower[i][j][1][0]->setPosition(Vec2(grid[i][j]->getPosition().x + Tower[i][j][1][0]->getContentSize().width / 2,
                grid[i][j]->getPosition().y + Tower[i][j][1][0]->getContentSize().height));
            this->addChild(Tower[i][j][1][0],2);
            Tower[i][j][1][0]->setVisible(false);
            Tower[i][j][1][0]->setTag(100 * i + j+3000);

            //�ɹ���ͼ��
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

    //0.2��ˢ��һ�ν�Ǯ
    schedule(CC_SCHEDULE_SELECTOR(Scene1::updateMoney), 0.2f);

    //10��ˢ�²���
    schedule(CC_SCHEDULE_SELECTOR(Scene1::updateWave), 3.0f);

    //ÿ1�����һֻ���� 
    schedule(CC_SCHEDULE_SELECTOR(Scene1::updateMonster), 1.0f);
    
    //�����ŵĹ���
    schedule(CC_SCHEDULE_SELECTOR(Scene1::AliveMonster), 0.2f);

    //����Ƿ��й��ﵽ���ܲ����Ե��ܲ�
    schedule(CC_SCHEDULE_SELECTOR(Scene1::If_Attack_Carrot), 0.2f);

   


    
    return true;
}

/*ʵʱ���½�Ǯ*/
void Scene1::updateMoney(float dt)
{
    //���ݵ�ǰ��money����label
    auto node = getChildByName("MoneyLabel");

    Label* Money_Label = static_cast<Label*>(node);

    Money_Label ->setString(std::to_string(money));

}

/*ʵʱ���²���*/
void Scene1::updateWave(float dt)
{
    
    //������һ�����Ҹ�����ʾ
    wave++;
    if (wave <= Total_Wave_Number) {
        auto node = getChildByName("WavesLabel");

        Label* Wave_Label = static_cast<Label*>(node);

        Wave_Label->setString(std::to_string(wave / 10 % 10) + "    " + std::to_string(wave % 10));

    }
    else { //��������������²�����ǩ
        //��Ϸ���������ܲ�����Ѫ��������Ϸ����
        //��ת

    }
    //�����е����һ��ʱ��ֹͣ����
    if (wave == Total_Wave_Number+1) {
        unschedule(CC_SCHEDULE_SELECTOR(Scene1::updateWave)); 
    }

}

/*���һ��ʱ����������*/
void Scene1::updateMonster(float dt)
{
  
    //����һ�����﹤�������ڲ�������
    MonsterFactory p;

    //ͨ������λ�ñ���Ĺ������ͣ�������Ӧ���͵Ĺ���
    type_monster = Monster_Wave[wave - 1][Monster_Order];
    Sprite* sp = p.Produce_Monster(Monster_Wave[wave - 1][Monster_Order]);
    FlyMonster* Monster = dynamic_cast<FlyMonster*>(sp);

    
    this->addChild(Monster);

    //���������vector������
    m.push_back(Monster);
  
    //��ǰ��ֻ���ڵ�ǰ�������
    Monster_Order = (Monster_Order + 1) % Monster_Number;

    //�����е����һ�������һֻ�����ʱ��,ֹͣ����
    if (wave == Total_Wave_Number&& Monster_Order== Monster_Number-1) {
        unschedule(CC_SCHEDULE_SELECTOR(Scene1::updateMonster));
    }

}

//����Ƿ��й��ﵽ���յ㣬�Ե��ܲ�
void Scene1::If_Attack_Carrot(float dt)
{

    int count = 0;
    Node* n = this->getChildByTag(-10);
    Carrot* carrot = static_cast<Carrot*>(n);
   
    for (int i = 0; i < m.size(); i++) 
        if (m[i]->getHp() > 0) { //����        
            int x = m[i]->getPosition().x;
            int y = m[i]->getPosition().y;

            if (x >= 10 * 80 && x <= 10 * 80 + 80 && y >= 5 * 80 && y <= 5 * 80 + 80) //������յ�
                count++;

        }
    //
    int f=carrot->SetHp(count);
    if (f) {  //����ܲ�Ѫ��Ϊ0����ת
        goto_LevelSelection();
    }
        
}

/*��ת���ؿ�ѡ�����*/
void  Scene1::goto_LevelSelection()
{
    //����ð��ģʽѡ�س���
    auto LevelSelection = LevelSelectionScene::createScene();

    //�������л�����
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, LevelSelection));
}

//ʵʱ���¹����Ƿ�����
void Scene1::AliveMonster(float dt)
{
    for (int i = 0; i < m.size(); i++)  
        if (m[i]->getHp() <= 0 && m[i]->survival==1) {    //��������Ѫ��С�ڵ���0��������״̬���0
            money = money + m[i]->getValue();   //��Ǯ
            m[i]->survival = 0;                 //���״̬���0
        }
    
}

/*����¼�*/
void Scene1::gch_onMouseDown(Event* event)
{

    //��ȡ�¼�
    EventMouse* e = (EventMouse*)event;

    //��ȡ���λ��
    int x = e->getCursorX();
    int y = e->getCursorY();

    //�����λ���ڲ˵���
    if (y >= 560)
        return;

    //��ǰ������ĸ���λ��
    Position p = transition(x, y);

    //ͨ����ǩ����ȡ��ǰ�ĸ��� 
    Node* n = this->getChildByTag(p.i * 100 + p.j);
    Sprite* Grid_Selcted = static_cast<Sprite*>(n);
    //���ʷ
    if (grid_is_visible == 0 &&range_is_visible==0 && Map1[p.i][p.j]/100 == Shit) {
    
        //ͨ��tag��ȡ�������������
        Node* node = this->getChildByTag(p.i * 100 + p.j + 5000);
        TowerShit* Tower = static_cast<TowerShit*>(node);
        Tower->Show_RangeAndGrade(this,money);
                  
        range_is_visible = 1;
        TowerType = Shit; //��ǰ��ʾ��Χ������Ϊ���
        gchx = p.i;
        gchy = p.j;   //���浱ǰ����λ��
        return;
    } 
    //���ƿ��
    else if (grid_is_visible == 0 && range_is_visible == 0 && Map1[p.i][p.j] / 100 == Bottle) {
        //ƿ����������

        //ͨ��tag��ȡ�������������
        Node* node = this->getChildByTag(p.i * 100 + p.j + 11000);
        TowerBottle* Tower = static_cast<TowerBottle*>(node);
        Tower->Show_RangeAndGrade(this, money);

        range_is_visible = 1;
        TowerType = Bottle; //��ǰ��ʾ��Χ������Ϊ���
        gchx = p.i;
        gchy = p.j;   //���浱ǰ����λ��
        return;
    }

    //�����·
    else if (grid_is_visible == 0 && range_is_visible == 0 && Map1[p.i][p.j] / 100 == LOAD) {
        //�йִ�֣�û����ʾ��ɫ                                                                                                                  
        return;
    }
    //����ϰ���
    else if (grid_is_visible == 0 && range_is_visible == 0 && Map1[p.i][p.j] / 100 == BLOCK) {
        //���ȹ����ϰ���
        return;
    }
    //���λ��Ϊ���ҳ����޹���ѡ��
    else if (grid_is_visible == 0 && range_is_visible == 0 && Map1[p.i][p.j]/100 == EMPTY)
    {
        Grid_Selcted->setVisible(true);
        grid_is_visible = 1;

        gchx = p.i;
        gchy = p.j;
        //�������Ӳ���ʾ
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 12; j++) {
                if (i * 100 + j != p.i * 100 + p.j) {

                    //ͨ����ǩ����ȡ��λ�õĸ���
                    Node* n = this->getChildByTag(i * 100 + j);
                    Sprite* Grid_Selcted1 = static_cast<Sprite*>(n);

                    //����ʾ
                    Grid_Selcted1->setVisible(false);
                }
            }
        }
        //��ʾ�������
        auto Tower1 = Sprite::create();
        auto Tower2 = Sprite::create();

        //Ǯ������ʾ��ɫ���棬Ǯ����ʾ��ɫ����
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

    //�����й������
    else if (grid_is_visible == 1) {
        //��ʾ���ӵ�ʱ�����������Ҫ�ж��Ƿ���������ȡ����ʾ
        grid_is_visible = 0;
        Sprite* Grid_Selected;
        Sprite* Tower1;
        Sprite* Tower2;

        int i1, j1;
        int x1;
        int y1;  //���浱ǰ��ʾ�ĸ��ӵ�λ��

        //��ȡ��ǰ��ʾ�ĸ��ӵ�λ��
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 12; j++) {
                //ͨ����ǩ����ȡ��λ�õĸ���
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
        //��ȡ��ǰ��ʾ�Ĺ�������λ��
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

        //������λ���ڵ�һ������ͼ����
        if (x >= Tower1->getPosition().x - Tower1->getContentSize().width / 2 &&
            x <= Tower1->getPosition().x + Tower1->getContentSize().width / 2 &&
            y >= Tower1->getPosition().y - Tower1->getContentSize().height / 2 &&
            y <= Tower1->getPosition().y + Tower1->getContentSize().height / 2) {
            if (money >= 100) {//��Ǯ��������

                log("build_tower(position, tower_available[0])");

                //��Ǯ
                money = money - 100;

                //���Ӳ��ɼ�
                Grid_Selcted->setVisible(false);


                //��ͼ�ϸõ�Ϊ����
                //Map1[p.i][p.j] = Bottle1;
                Map1[gchx][gchy] = Bottle1;
                gchx = -1;
                gchy = -1;

                //����������
                auto Bottle_Tower = TowerBottle::createSprite();

                //���ø����ı�ǩ
                Bottle_Tower->setTag(100 * i1 + j1 + 11000);
                //����ƿ������
             
                Bottle_Tower->setPosition(Vec2(x1, y1));
                //Bottle_Tower->setTag(x1 * 1000 + y1 * 10);
                this->addChild(Bottle_Tower);

            }
        }
        else if (//������λ���ڵڶ�������ͼ����
            x >= Tower2->getPosition().x - Tower2->getContentSize().width / 2 &&
            x <= Tower2->getPosition().x + Tower2->getContentSize().width / 2 &&
            y >= Tower2->getPosition().y - Tower2->getContentSize().height / 2 &&
            y <= Tower2->getPosition().y + Tower2->getContentSize().height / 2) {
            if (money >= 120) {//��Ǯ��������
                // build_tower(position, tower_available[1]);
                log("build_tower(position, tower_available[1])");

                //��Ǯ
                money = money - 120;

                //���Ӳ��ɼ�
                Grid_Selcted->setVisible(false);

                //��ͼ�ϸõ�Ϊ�������
                Map1[gchx][gchy] = Shit1;

                //����������
                auto Shit_Tower = TowerShit::createSprite();

                //���ø����ı�ǩ
                Shit_Tower->setTag(100*i1+j1+5000);

                //auto Shit_Tower = Sprite::create("Theme/Shit/SmallShit.png");
                Shit_Tower->setPosition(Vec2(x1, y1));
                //Shit_Tower->setTag(x1 * 10000 + y1 * 100);
                this->addChild(Shit_Tower);

             
            }

        }

        //�����ɼ�
        Grid_Selected->setVisible(false);
        Tower1->setVisible(false);
        Tower2->setVisible(false);
    }
    //�����й�����Χ��ʾ����������
    else if (range_is_visible == 1) {

        int f = 1;  //�ж��Ƿ�����
        if (TowerType == Shit) {
            Node* node = this->getChildByTag(gchx * 100 + gchy + 5000);
            TowerShit* Tower = static_cast<TowerShit*>(node);

            //�����µ�λ��������λ��
            if ((x >= gchy * 80 && x <= gchy * 80 + 80 && y >= (6 - gchx) * 80 + 80 && y <= (6 - gchx) * 80 + 160)) {
                if (money >= Tower->upgradecost[Tower->level]) { //Ǯ��
                    //������������������
                    Tower->Upgrade(this);
                    //Tower->attack(this, Tower->getPosition(), Vec2(100, 100));
                    //��Ǯ
                    money = money - Tower->upgradecost[Tower->level];
                }

            }//�����µ�λ���ڳ���λ��
            else if ((x >= gchy * 80 && x <= gchy * 80 + 80 && y >= (6 - gchx) * 80 - 80 && y <= (6 - gchx) * 80)) {
                //��Ǯ
                money = money + Tower->value[Tower->level];
                //ɾ��������
                //Node* node = static_cast<Node*>(Tower);
                Tower->stopschedule();
                Tower->Hide_RangeAndGrade(this);  //ȡ����ʾ��ΧҪ��ɾ��֮ǰ
                Tower->removeFromParent();
                f = 0;
                //Tower->setVisible(false);
                //delete Tower;
                Map1[gchx][gchy] = EMPTY;
            }
            if (f)
                Tower->Hide_RangeAndGrade(this);

            //�����ɺ�Χ���ɼ�
            range_is_visible = 0;
        }
        if (TowerType == Bottle) {
            Node* node = this->getChildByTag(gchx * 100 + gchy + 11000);
            TowerBottle* Tower = static_cast<TowerBottle*>(node);

            //�����µ�λ��������λ��
            if ((x >= gchy * 80 && x <= gchy * 80 + 80 && y >= (6 - gchx) * 80 + 80 && y <= (6 - gchx) * 80 + 160)) {
                if (money >= Tower->upgradecost[Tower->level]) { //Ǯ��
                    //������������������
                    Tower->Upgrade(this);
                    //Tower->attack(this, Tower->getPosition(), Vec2(100, 100));
                    //��Ǯ
                    money = money - Tower->upgradecost[Tower->level];
                }

            }//�����µ�λ���ڳ���λ��
            else if ((x >= gchy * 80 && x <= gchy * 80 + 80 && y >= (6 - gchx) * 80 - 80 && y <= (6 - gchx) * 80)) {
                //��Ǯ
                money = money + Tower->value[Tower->level];
                //ɾ��������
                //Node* node = static_cast<Node*>(Tower);
                Tower->stopschedule();
                Tower->Hide_RangeAndGrade(this);  //ȡ����ʾ��ΧҪ��ɾ��֮ǰ
                Tower->removeFromParent();
                f = 0;
                //Tower->setVisible(false);
                //delete Tower;
                Map1[gchx][gchy] = EMPTY;
            }
            if (f)
                Tower->Hide_RangeAndGrade(this);

            //�����ɺ�Χ���ɼ�
            range_is_visible = 0;
        }
    }
    else {
            auto lllzty = Sprite::create("grossini.png");
            lllzty->setPosition(Vec2(100, 100));
            this->addChild(lllzty, 3);
        }

    
}

/*�������ʾ���Ӻ͹�����������*/
void Scene1::onMouseDown(Event* event)
{
    //��ȡ�¼�
    EventMouse* e = (EventMouse*)event;
    
    //��ȡ���λ��
    int x = e->getCursorX();
    int y = e->getCursorY();
    
    if (y < 560) {   //�����λ�ò��ڲ˵���

        //��ǰ������ĸ���λ��
        Position p = transition(x, y);

        //ͨ����ǩ����ȡ��ǰ�ĸ��� 
        Node* n = this->getChildByTag(p.i * 100 + p.j);
        Sprite* Grid_Selcted = static_cast<Sprite*>(n);

        //δ��ʾ���ӵ�ʱ�����������Ҫ��ʾ���Ӻ͹������
        if (grid_is_visible == 0) {

            //��λ�ò��ǿɷ��õĵ�
            if (Map1[p.i][p.j] / 100 != EMPTY) {
                return;
            }
                
             
            Grid_Selcted->setVisible(true);
            grid_is_visible = 1;

            //�������Ӳ���ʾ
            for (int i = 0; i < 7; i++)
                for (int j = 0; j < 12; j++)
                    if (i * 100 + j != p.i * 100 + p.j) {

                        //ͨ����ǩ����ȡ��λ�õĸ���
                        Node* n = this->getChildByTag(i * 100 + j);
                        Sprite* Grid_Selcted1 = static_cast<Sprite*>(n);

                        //����ʾ
                        Grid_Selcted1->setVisible(false);
                    }


            //��ʾ�������
            auto Tower1 = Sprite::create();
            auto Tower2 = Sprite::create();

            //Ǯ������ʾ��ɫ���棬Ǯ����ʾ��ɫ����
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
        else { //��ʾ���ӵ�ʱ�����������Ҫ�ж��Ƿ���������ȡ����ʾ
            grid_is_visible = 0;
            Sprite* Grid_Selected;
            Sprite* Tower1;
            Sprite* Tower2;

            int i1;
            int j1;

            int x1;
            int y1;  //���浱ǰ��ʾ�ĸ��ӵ�λ��

            //��ȡ��ǰ��ʾ�ĸ��ӵ�λ��
            for (int i = 0; i < 7; i++)
                for (int j = 0; j < 12; j++) {
                    //ͨ����ǩ����ȡ��λ�õĸ���
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

            //��ȡ��ǰ��ʾ�Ĺ�������λ��
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

            //������λ���ڵ�һ������ͼ����
            if (x >= Tower1->getPosition().x - Tower1->getContentSize().width / 2 &&
                x <= Tower1->getPosition().x + Tower1->getContentSize().width / 2 &&
                y >= Tower1->getPosition().y - Tower1->getContentSize().height / 2 &&
                y <= Tower1->getPosition().y + Tower1->getContentSize().height / 2) {
                if (money >= 100) {//��Ǯ��������

                    log("build_tower(position, tower_available[0])");

                    //��Ǯ
                    money = money - 100;

                    //���Ӳ��ɼ�
                    Grid_Selcted->setVisible(false);


                    //��ͼ�ϸõ�Ϊ����
                    Map1[p.i][p.j] = Bottle1;
                    //����ƿ������
                    auto Bottle_Tower = Sprite::create("Theme/Bottle/SmallBottle.png");
                    Bottle_Tower->setPosition(Vec2(x1, y1));
                    //Bottle_Tower->setTag(x1 * 1000 + y1 * 10);
                    this->addChild(Bottle_Tower);

                }
            }
            else if (//������λ���ڵڶ�������ͼ����
                x >= Tower2->getPosition().x - Tower2->getContentSize().width / 2 &&
                x <= Tower2->getPosition().x + Tower2->getContentSize().width / 2 &&
                y >= Tower2->getPosition().y - Tower2->getContentSize().height / 2 &&
                y <= Tower2->getPosition().y + Tower2->getContentSize().height / 2) {
                if (money >= 120) {//��Ǯ��������
                    // build_tower(position, tower_available[1]);
                    log("build_tower(position, tower_available[1])");

                    //��Ǯ
                    money = money - 120;

                    //���Ӳ��ɼ�
                    Grid_Selcted->setVisible(false);

                    //��ͼ�ϸõ�Ϊ����
                    Map1[p.i][p.j] = Shit1;

                    //����������
                    auto Shit_Tower = TowerShit::createSprite();
                    Shit_Tower->setTag(i1*100+j1+5000);

                    //auto Shit_Tower = Sprite::create("Theme/Shit/SmallShit.png");
                    Shit_Tower->setPosition(Vec2(x1, y1));
                    //Shit_Tower->setTag(x1 * 10000 + y1 * 100);
                    this->addChild(Shit_Tower);
                }

            }

            //�����ɼ�
            Grid_Selected->setVisible(false);
            Tower1->setVisible(false);
            Tower2->setVisible(false);
        }
    }



}

/*��Ϸ��ʼʱ����ʱ*/
void Scene1::Game_Start()
{
    //��ȡ��Ļ��С
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //��ͣ��Ϸ��ѭ��
    Director::getInstance()->pause();

    //��������ʱ�������ڵĲ�
    auto CountDown_layer = Layer::create();
    CountDown_layer->setPosition(Vec2::ZERO);
    this->addChild(CountDown_layer);

    //����ʱ�ı���
    auto CountDownBackground = Sprite::create("/Theme/Theme1/CountDownBackground.png");
    CountDownBackground->setPosition(Vec2(origin.x + visibleSize.width / 2,origin.y + visibleSize.height / 2));
    CountDown_layer->addChild(CountDownBackground);
    //����󵭳�
    CountDownBackground->runAction(Sequence::create(DelayTime::create(3), FadeOut::create(0.1), nullptr));

    //����ʱȦ
    auto Circle = Sprite::create("/Theme/Theme1/CountDownCircle.png");
    Circle->setPosition(Vec2(origin.x + visibleSize.width /2, origin.y + visibleSize.height / 2));
    CountDown_layer->addChild(Circle);
    //��ת360���ظ����֣�����
    Circle->runAction(Sequence::create(Repeat::create(RotateBy::create(1, -360), 3), FadeOut::create(0.1), nullptr));

    //����ʱ������3
    auto number3 = Sprite::create("/Theme/Theme1/Number3.png");
    number3->setPosition(Vec2(origin.x + visibleSize.width * 0.51,origin.y + visibleSize.height / 2));
    CountDown_layer->addChild(number3);

    //���ֵ���ʱ�Ķ���
    Vector<SpriteFrame*> frame;
    frame.pushBack(SpriteFrame::create("/Theme/Theme1/Number3.png", Rect(0, 0, 95, 114)));
    frame.pushBack(SpriteFrame::create("/Theme/Theme1/Number2.png", Rect(0, 0, 95, 114)));
    frame.pushBack(SpriteFrame::create("/Theme/Theme1/Number1.png", Rect(0, 0, 95, 114)));
    number3->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 1)), FadeOut::create(0.2), nullptr));
      
    //����ʱ��ʱ�����п��ø����˸
    Sprite* grid[7][12];
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 12; j++) {
            grid[i][j] = Sprite::create("StartGrid.png");
            if (Map1[i][j] == 0) {
                //����͸����
                //grid[i][j]->setOpacity(100);
                //��������˸2��
                //grid[i][j]->runAction(Blink::create(3, 2));
            }
        }
    }
    //������ɾ������ʱ���ڵĲ�
    CountDown_layer->runAction(Sequence::create(DelayTime::create(3.1), FadeOut::create(0.1), nullptr));
    
    //�ָ���Ϸ��ѭ��
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
