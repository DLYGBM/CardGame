#include "PlayGameScene.h"

USING_NS_CC;
using namespace cocos2d::ui;

Scene* PlayGameScene::createScene()
{
    return PlayGameScene::create();
}

bool PlayGameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    CCLOG("visibleSize.width = %f, visibleSize.height = %f", visibleSize.width, visibleSize.height);

    // 创建主牌区
    createMainCardArea();
    // 创建卡堆区
    createCardStackArea();

    //auto a = Sprite::create("/res/res/card_general.png");
    //a->setPosition(Vec2(540, 1040));
    //addChild(a);


    return true;
}


void PlayGameScene::createMainCardArea()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    // 主牌区尺寸：1080*1500
    auto mainArea = Sprite::create("PlayBack.png");
    //mainArea->setContentSize(Size(visibleSize.width, visibleSize.height*(1500/2080)));
    mainArea->setPosition(Vec2(540,1100 ));

    this->addChild(mainArea);
}

void PlayGameScene::createCardStackArea()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    // 主牌区尺寸：1080*1500
    auto stackArea = Sprite::create("StackBack.png");
    //stackArea->setContentSize(Size(1080, 1500));
    stackArea->setPosition(Vec2(540,200));

    this->addChild(stackArea);
}