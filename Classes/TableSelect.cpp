
#include "TableSelect.h"
#include "SettingDialog.h"
#include "TLMienNam.h"
#include "MButton.hpp"
#include "MText.hpp"
#include "M9Path.hpp"
#include "MLabel.hpp"
#include "GameConfig.h"

#define BTN_BACK 1
#define BTN_PLAYNOW 2
#define BTN_CREATE 3
#define BTN_GOTO 4
#define BTN_REFRESH 5
#define BTN_PHONGVIP 6
#define BTN_PHONGFREE 7

Scene* TableSelect::createScene()

{
    
    auto scene = Scene::create();
    
    auto layer = TableSelect::create();
    
    // scene_layer
    
    scene->addChild(layer);
    
    
    
    return scene;
    
}

bool TableSelect::init()

{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    
    //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
    
    auto keyboardListener = cocos2d::EventListenerKeyboard::create();
    
    keyboardListener->onKeyReleased = CC_CALLBACK_2(TableSelect::onKeyReleased, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
    

    auto background_screen = MSprite::create("bgr_select_table.jpg",visibleSize);
    background_screen->setPosition(Vec2(origin.x,origin.y));
    this->addChild(background_screen);
    
    
    this->initTable(visibleSize, origin);
    
    this->initMenu(visibleSize, origin);
    
    return true;
    
}

void TableSelect::initMenu(Size visibleSize,Vec2 origin){
    auto btn_back = MButton::create(btn_back_,BTN_BACK);
    btn_back->setPosition(Vec2(origin.x+10,origin.y+visibleSize.height-btn_back->getHeight()-10));
    btn_back->addTouchEventListener(CC_CALLBACK_2(TableSelect::menuCallBack, this));
    
    auto txt_game_name = MLabel::create("TL Miền Nam",35);
    txt_game_name->setPosition(Vec2(btn_back->getPosition().x+btn_back->getWidth()+10,
                                     btn_back->getPosition().y));
    
    auto btn_play_now = MButton::create("ic_button_second.png","Chơi ngay",30,Color3B(151,28,28),BTN_PLAYNOW);
    btn_play_now->setPosition(Vec2(origin.x+visibleSize.width-btn_play_now->getWidth()-10,
                                   origin.y+visibleSize.height-btn_play_now->getHeight()-10));
    btn_play_now->addTouchEventListener(CC_CALLBACK_2(TableSelect::menuCallBack, this));
    
    auto btn_create_table = MButton::create(btn_button_,"Tạo bàn",30,BTN_CREATE);
    btn_create_table->setPosition(Vec2(btn_play_now->getPosition().x-btn_create_table->getWidth()-10,
                                       btn_play_now->getPosition().y));
    btn_create_table->addTouchEventListener(CC_CALLBACK_2(TableSelect::menuCallBack, this));
    
    auto btn_goto_table = MButton::create(btn_button_,"Đến bàn",30,BTN_GOTO);
    btn_goto_table->setPosition(Vec2(btn_create_table->getPosition().x-btn_goto_table->getWidth()-10,
                                     btn_create_table->getPosition().y));
    btn_goto_table->addTouchEventListener(CC_CALLBACK_2(TableSelect::menuCallBack, this));
    
    auto btn_refresh = MButton::create("ic_button_refresh.png",BTN_REFRESH);
    btn_refresh->setPosition(Vec2(btn_goto_table->getPosition().x-btn_refresh->getWidth()-10,
                                  btn_goto_table->getPosition().y));
    btn_refresh->addTouchEventListener(CC_CALLBACK_2(TableSelect::menuCallBack, this));
    
    //==bottom bar under
    
    auto bar = MSprite::create("bgr_bottom_bar.png",Size(visibleSize.width,visibleSize.height*0.125f));
    bar->setPosition(origin.x,origin.y);
    
    btn_phong = MSprite::createExtendsUp("bgr_table_selected.png",Size(visibleSize.width*0.4f,visibleSize.height*0.125f));
    btn_phong->setPosition(Vec2(origin.x+visibleSize.width*0.2f,origin.y));
    
//    auto btn_phong_vip = MSprite::createExtends("null_bkg.png","Phòng Vip",Size(visibleSize.width*0.4f,visibleSize.height*0.125f));
//    btn_phong_vip->setPosition(Vec2(origin.x+visibleSize.width*0.2f,origin.y));
//    btn_phong_vip->setTag(BTN_PHONGVIP);
    
    auto btn_phong_vip = MButton::create("null_bkg.png","Phòng Vip",30,BTN_PHONGVIP);
    btn_phong_vip->setPosition(Vec2(origin.x+visibleSize.width*0.4f-btn_phong_vip->getWidth()/2,
                                    origin.y+visibleSize.height*0.125f*0.5f-btn_phong_vip->getHeight()/2));
    btn_phong_vip->addTouchEventListener(CC_CALLBACK_2(TableSelect::phongCallBack, this));
    
    
    auto btn_phong_free = MButton::create("null_bkg.png","Phòng Free",30,BTN_PHONGFREE);
    btn_phong_free->setPosition(Vec2(origin.x+visibleSize.width*0.8f-btn_phong_free->getWidth()/2,
                                     origin.y+visibleSize.height*0.125f*0.5f-btn_phong_free->getHeight()/2));
    btn_phong_free->addTouchEventListener(CC_CALLBACK_2(TableSelect::phongCallBack, this));
    
    this->addChild(btn_back);
    this->addChild(txt_game_name);
    this->addChild(btn_play_now);
    this->addChild(btn_create_table);
    this->addChild(btn_goto_table);
    this->addChild(btn_refresh);
    
    this->addChild(bar);
    this->addChild(btn_phong);
    this->addChild(btn_phong_vip);
    this->addChild(btn_phong_free);
}

void TableSelect::initTable(Size visibleSize,Vec2 origin){
    //layout left
    auto backgroundLeft = M9Path::create("tab_one.9.png",Size(visibleSize.width*0.2f,visibleSize.height*0.75f));
    backgroundLeft->setPosition(origin.x,origin.y+ visibleSize.height/2-backgroundLeft->getContentSize().height/2);
    this->addChild(backgroundLeft);
    
    auto hoatdong = MLabel::create("Hoạt động",32);
    hoatdong->setPosition(Vec2(origin.x+backgroundLeft->getContentSize().width/2-hoatdong->getContentSize().width/2,
                                backgroundLeft->getPosition().y+backgroundLeft->getContentSize().height
                                -1.8f*hoatdong->getContentSize().height));
    this->addChild(hoatdong);
    
    Layout* layoutLeft = Layout::create();
    layoutLeft->setContentSize(Size(backgroundLeft->getWidth()-30,backgroundLeft->getHeight()*5/6));
    layoutLeft->setPosition(Vec2(origin.x+15,origin.y+visibleSize.height*0.125f));
    this->addChild(layoutLeft);
    
    auto lv1 = ListView::create();
    //auto testxxx = MText::create("This is a notification xxxxxx!",15);
    //lv1->setItemModel(testxxx);
    for(int i=0;i<20;i++){
        auto testxxx = MText::create("This is a notification xxxxxx!,nothing.don't look at me!please!",15);
        testxxx->ignoreContentAdaptWithSize(false);
        testxxx->setContentSize(Size(layoutLeft->getContentSize().width,testxxx->getHeight()*2));
        lv1->pushBackCustomItem(testxxx);
    }
    
    lv1->setItemsMargin(10);
    //lv1->setBounceEnabled(true);
    lv1->setGravity(ListView::Gravity::LEFT);
    lv1->setContentSize(layoutLeft->getContentSize());
    //lv1->setPosition(layoutLeft->getPosition());
    lv1->setScrollBarEnabled(false);
    layoutLeft->addChild(lv1);
    
    //==========================Layout Right
    
    
    auto backgroundRight = M9Path::create("tab_two.9.png",Size(visibleSize.width*0.8f,visibleSize.height*0.75f));
    backgroundRight->setPosition(origin.x+visibleSize.width*0.2f,
                                 origin.y+visibleSize.height/2-backgroundRight->getHeight()/2);
    this->addChild(backgroundRight);
    
    auto ban_so = MLabel::create("Bàn số ▿",32);
    ban_so->setPosition(Vec2(origin.x-ban_so->getWidth()/2 + visibleSize.width*0.32f,
                              hoatdong->getPosition().y));
    this->addChild(ban_so);
    
    auto tien_cuoc = MLabel::create("Tiền cược ▿",32);
    tien_cuoc->setPosition(Vec2(origin.x-tien_cuoc->getWidth()/2 + visibleSize.width*0.55f,
                                 hoatdong->getPosition().y));
    this->addChild(tien_cuoc);
    
    auto trang_thai = MLabel::create("Trạng thái ▿",32);
    trang_thai->setPosition(Vec2(origin.x-trang_thai->getWidth()/2 + visibleSize.width*0.76f,
                                  hoatdong->getPosition().y));
    this->addChild(trang_thai);
    
    auto khoa = MLabel::create("Khóa ▿",32);
    khoa->setPosition(Vec2(origin.x-khoa->getWidth()/2 + visibleSize.width*0.945f,
                            hoatdong->getPosition().y));
    this->addChild(khoa);
    
    
    Layout* layoutRight = Layout::create();
    layoutRight->setContentSize(Size(backgroundRight->getWidth()-30,backgroundRight->getHeight()*5/6));
    layoutRight->setPosition(Vec2(origin.x+15+backgroundLeft->getWidth(),origin.y+visibleSize.height*0.125f));
    this->addChild(layoutRight);
    
    auto lvRight = ListView::create();
    //auto model = Button::create();
    //lvRight->setItemModel(model);
    
    for (int i=0; i<20; i++)
    {
        auto bkg_item = Sprite::create("bgr_list_item.png");
        auto number_table = MLabel::create("6",30);
        auto money = MLabel::create("1000 xu",30);
        auto status = MLabel::create("xxx",30);
        
        auto lock = Sprite::create("ic_lock.png");
        auto custom_item = Layout::create();
        
        custom_item->setContentSize(Size(layoutRight->getContentSize().width,lock->getContentSize().height*2));
        
        bkg_item->setScale(layoutRight->getContentSize().width/bkg_item->getContentSize().width,
                           lock->getContentSize().height*2/bkg_item->getContentSize().height);
        bkg_item->setPosition(layoutRight->getContentSize().width/2,custom_item->getContentSize().height/2);
        
        number_table->setPosition(Vec2(number_table->getContentSize().width/2+backgroundRight->getContentSize().width/8,
                                       custom_item->getContentSize().height / 2.0f-number_table->getContentSize().height/2));
        money->setPosition(Vec2(money->getContentSize().width/2+backgroundRight->getContentSize().width*2.5f/8,
                                custom_item->getContentSize().height / 2.0f-money->getContentSize().height/2));
        status->setPosition(Vec2(status->getContentSize().width/2+backgroundRight->getContentSize().width*5/8,
                                 custom_item->getContentSize().height / 2.0f-status->getContentSize().height/2));
        lock->setPosition(Vec2(lock->getContentSize().width/2+backgroundRight->getContentSize().width*7/8,
                               custom_item->getContentSize().height / 2.0f));
        
        custom_item->addChild(bkg_item);
        custom_item->addChild(number_table);
        custom_item->addChild(money);
        custom_item->addChild(status);
        custom_item->addChild(lock);
        lvRight->pushBackCustomItem(custom_item);
    }
    lvRight->setItemsMargin(15);
    lvRight->setBounceEnabled(true);
    lvRight->setGravity(ListView::Gravity::LEFT);
    lvRight->setContentSize(layoutRight->getContentSize());
    layoutRight->addChild(lvRight);
    
    //======
    
    

}

void TableSelect::tableCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
    if(type == Widget::TouchEventType::ENDED){
        //xxxxx
    }
}

void TableSelect::menuCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
    if(type == Widget::TouchEventType::ENDED){
        MButton *button = (MButton*) sender;
        int tag = button->getTag();
        switch (tag) {
            case BTN_BACK:
                CCLOG("%s","Button Back");
                {
                    auto select = ShowGame::createScene();
                    Director::getInstance()->replaceScene(TransitionCrossFade::create(0.15f, select));
                }
                break;
            case BTN_CREATE:
                CCLOG("%s","Button create");
                break;
            case BTN_GOTO:
                CCLOG("%s","Button GoTo");
                break;
            case BTN_PLAYNOW:
                CCLOG("%s","Button Play Now");
                {
                    auto select = TLMienNam::createScene();
                    Director::getInstance()->replaceScene(TransitionCrossFade::create(0.15f, select));
                }
                break;
            case BTN_REFRESH:
                CCLOG("%s","Button Refresh");
                break;
            default:
                break;
        }
    }

}

void TableSelect::phongCallBack(cocos2d::Ref *sender, Widget::TouchEventType type){
    if(type == Widget::TouchEventType::ENDED){
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        MButton *button = (MButton*) sender;
        int tag = button->getTag();
        switch (tag) {
            case BTN_PHONGVIP:
                CCLOG("%s","Phong Vip");
                btn_phong->runAction(MoveTo::create(0.1f, Vec2(origin.x+visibleSize.width*0.2f,origin.y)));
                break;
            case BTN_PHONGFREE:
                CCLOG("%s","Phong Free");
                btn_phong->runAction(MoveTo::create(0.1f, Vec2(origin.x+visibleSize.width*0.6f,origin.y)));
                break;
            default:
                break;
        }
    }
}




