#include "GameController.h"
#include "LevelConfigLoder.h"
#include "cocos2d.h"
#include "PlayFieldContoller.h"
#include "StackController.h"
#include "PlayGameScene.h"
#include "CardModel.h"
#include "StackModel.h"
#include "PlayFieldModel.h"
#include "UndoModel.h"
#include "SelectLevelScene.h"


/**	@brief 布置场景，开始游戏
 * @param levelId 关卡ID
 */
void GameController::startGame(LevelId levelId)
{
    
    // 加载配置
    LevelConfig levelConfig = LevelConfigLoder::loadLevelConfig(levelId);
    PlayFieldController::init(levelConfig);
    StackController::init(levelConfig);

    // 创建场景
    // 添加卡片
    auto scene = PlayGameScene::createScene();
    CCLOG("%d", levelConfig.PlayFieldCards.size());
    for(int i = 0; i < levelConfig.PlayFieldCards.size(); ++i)
    {
        CardModel* cardModel = nullptr;
        for(int j = 0;j < levelConfig.PlayFieldCards[i].size();++j)
        {
            cardModel = PlayFieldModel::getCardModel(i,j);
            auto position = cocos2d::Vec2(cardModel->getPosition().x, cardModel->getPosition().y + 500);
            cardModel->setPosition(position);
            cardModel->mySetPosition(position);
            scene->addChild(cardModel);
        }
        if(cardModel!=nullptr)
        cardModel->setTouchEnabled(true);
    }

    for (int i = 0; i < levelConfig.StackCards.size(); ++i)
    {
        auto cardModel = StackModel::getCardModel(i);
        auto position = cocos2d::Vec2(cocos2d::Vec2(cardModel->getPosition().x + i * 65 + 150, cardModel->getPosition().y + 250));
        cardModel->setPosition(position);
        cardModel->mySetPosition(position);;
        scene->addChild(cardModel);
    }

    auto action = cocos2d::MoveTo::create(0.2f, cocos2d::Vec2(700, 250));
    StackModel::getCardModel(StackModel::size() - 1)->runAction(action);
    StackModel::getCardModel(StackModel::size() - 2)->setTouchEnabled(true);
    UndoModel::currentCard = StackModel::getCardModel(StackModel::size() - 1);

    //auto action = cocos2d::MoveTo::create(0.2f, cocos2d::Vec2(600, 250));
    //auto move = cocos2d::EaseIn::create(action->clone(),1);
    //StackModel::getCardModel(StackModel::size() - 1)->runAction(move);
    // run
    cocos2d::Label* labelBack = cocos2d::Label::createWithTTF("Back", "fonts/Marker Felt.ttf", 32);
    labelBack->setPosition(cocos2d::Vec2(1000,250));
    //// 绑定事件
    auto labelListener = cocos2d::EventListenerTouchOneByOne::create();
    labelListener->setSwallowTouches(true);
    labelListener->onTouchBegan = [](cocos2d::Touch* touch, cocos2d::Event* event) {
        return UndoModel::Back(touch,event);
    };

    auto playListener = cocos2d::EventListenerTouchOneByOne::create();
    playListener->setSwallowTouches(true);
    playListener->onTouchBegan = [](cocos2d::Touch* touch, cocos2d::Event* event) {
        return PlayFieldController::handleCardClick(touch, event);
    };
    //// 注册监听器
    cocos2d::EventDispatcher* eventDispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
    eventDispatcher->addEventListenerWithSceneGraphPriority(labelListener->clone(), labelBack);
    scene->addChild(labelBack);

    for (int i = 0; i < PlayFieldModel::heapSize(); ++i)
    {
        for (int j = 0; j < PlayFieldModel::size(i); ++j)
        {
            auto cardModel = PlayFieldModel::getCardModel(i, j);
            eventDispatcher->addEventListenerWithSceneGraphPriority(playListener->clone(), cardModel);
        }
    }

    auto stackListener = cocos2d::EventListenerTouchOneByOne::create();
    stackListener->setSwallowTouches(true);
    stackListener->onTouchBegan = [](cocos2d::Touch* touch, cocos2d::Event* event) {
        return StackController::handleCardClick(touch, event);
    };
    //// 注册监听器
    for (int i = 0; i < StackModel::size(); ++i)
    {
        auto cardModel = StackModel::getCardModel(i);
        eventDispatcher->addEventListenerWithSceneGraphPriority(stackListener->clone(), cardModel);
    }

    //// 切换场景
    cocos2d::Director::getInstance()->replaceScene(scene);
    CCLOG("stackResidual %d", stackResidual);
}


/**	@brief 返回菜单
 */
void GameController::returnToMenu()
{
    StackModel::clear();
    PlayFieldModel::clear();
    auto Menu = SelectLevelScene::create();
    cocos2d::Director::getInstance()->replaceScene(Menu);
}





