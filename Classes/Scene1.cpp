#include "Scene1.h"
#include "ui/CocosGUI.h"
#include"FlyMonster.h"
#include "TowerShit.h"
USING_NS_CC;

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

    //��ȡ�ֱ��ʣ����ڴ�С��
    auto visibleSize = Director::getInstance()->getVisibleSize(); 
    //ԭ��λ��
    Vec2 origin = Director::getInstance()->getVisibleOrigin();



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



    Game_Start();

  

    auto mouseListener = EventListenerMouse::create();

    mouseListener->onMouseDown = CC_CALLBACK_1(Scene1::onMouseDown, this);


    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    
   



    auto flymonster = FlyMonster::createSprite();
    //shit->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 3 + origin.y));
    this->addChild(flymonster, 0);



    return true;
}

/*ʵʱ���½�Ǯ*/
void Scene1::update()
{
    //���ݵ�ǰ��money����label
    auto node = getChildByName("MoneyLabel");

    Label* Money_Label = static_cast<Label*>(node);

    Money_Label ->setString(std::to_string(money));

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

            //
            if (Map1[p.i][p.j] == 1)
                return;
             
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
                    Map1[p.i][p.j] = TOWER;

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
                    Map1[p.i][p.j] = TOWER;

                    //����������
                    auto Shit_Tower = TowerShit::createSprite();

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


    update();  //����money
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
                grid[i][j]->setOpacity(100);
                //��������˸2��
                grid[i][j]->runAction(Blink::create(3, 2));
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
