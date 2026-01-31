#include "SelectLevelScene.h"
#include "ui/CocosGUI.h"
#include "LevelConfig.h"
#include "GameController.h"

USING_NS_CC;
using namespace cocos2d::ui;

constexpr int kLEVEL_NUM = 3;

Scene* SelectLevelScene::createScene()
{
    return SelectLevelScene::create();
}


static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SelectLevelScene.cpp\n");
}

bool  SelectLevelScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //std::vector<MenuItem*>MenuItems;
    //for (int i = 0; i < LEVEL_NUM; ++i)
    //{

    //}
    auto mn = Menu::create();
    for (int i = 0; i < kLEVEL_NUM; ++i)
    {
        auto title = StringUtils::format("Level %d", i+1);
        auto label = Label::createWithTTF(title, "fonts/Marker Felt.ttf", 32);
        auto lable = MenuItemLabel::create(label, CC_CALLBACK_1(SelectLevelScene::_onCardClickCallback, this));
        lable->setTag(i);
        mn->addChild(lable);
    }
    mn->alignItemsVerticallyWithPadding(20);
    
    //mn->setPosition(Vec2::ZERO);
    addChild(mn);
            

    return true;
}

void SelectLevelScene::_onCardClickCallback(cocos2d::Ref* pSender)
{
    CCLOG("Level selected");
    auto menuItem = (MenuItem*)pSender;
    LevelId levelId = (LevelId)menuItem->getTag();
    GameController::startGame(levelId);
}
 





