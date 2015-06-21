//
//  StartScene.cpp
//  mcdrunning
//
//  Created by chenbingfeng on 15/5/31.
//
//

#include "StartScene.h"
#include "Common.h"
#include "SimpleAudioEngine.h"
#include "RoleSelectScene.h"
#include "GameScene.h"
#include "ServerConn.h"
#include "GameState.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
    auto scene = Scene::create();

    auto layer = StartScene::create();

    scene->addChild(layer);

    return scene;
}

bool StartScene::init()
{
    if (!McdLayer::init()){
        return false;
    }

    Size windowsSize = Director::getInstance()->getVisibleSize();
    auto center =Vec2{windowsSize.width, windowsSize.height} * 0.5f;

    // white bg
    auto bg = Sprite::create(config::start_bg);
    mcd::scale2size(bg, windowsSize);
    bg->setPosition(center);
    this->addChild(bg, 0);

    // bgm
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(config::bgm_default.c_str(), true);

    // buttons
    withInOut(decorateButton(config::start_btn_coin, BTN_COIN));
    withInOut(decorateButton(config::start_btn_head, BTN_HEAD));
    withInOut(decorateButton(config::start_btn_role, BTN_ROLE));
    withInOut(decorateButton(config::start_btn_asset, BTN_ASSET));
    withInOut(decorateButton(config::start_btn_drink, BTN_DRINK));
    withInOut(decorateButton(config::start_btn_setting, BTN_SETTING));
    withInOut(decorateButton(config::start_btn_rank, BTN_RANK));
    withInOut(decorateButton(config::start_btn_play, BTN_PLAY));

    // img
    withInOut(decorateImg(config::start_role, config::start_img_role));

    turnIn();
    return true;
}

void StartScene::onButtonClick(int tag)
{

    switch (tag) {
        case BTN_ROLE:
            turnOut();
            scheduleOnce([](float){Director::getInstance()->replaceScene(RoleSelectScene::createScene());}, config::default_turn_out_time, "ds");
            break;

        case BTN_PLAY:
            turnOut();
            scheduleOnce([](float){Director::getInstance()->replaceScene(GameScene::create());}, config::default_turn_out_time, "ds2");
            break;

        case BTN_COIN:{
            auto cb = [](int errCode){};
            GameState::g()->newAccount(cb);
            }
            break;

        case BTN_DRINK:
            tr::test();
            break;

        default:
            break;
    }
}

// http game server