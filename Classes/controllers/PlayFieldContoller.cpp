#include "PlayFieldContoller.h"
#include "ui/CocosGUI.h"
#include "LevelConfig.h"
#include "GameController.h"
#include "PlayFieldModel.h"
#include "UndoModel.h"


/**	@brief 判断是否胜利
 * @return 是否胜利
 */
bool isSucsess()
{
    for (int i = 0; i < PlayFieldModel::heapSize(); ++i)
    {
        if (PlayFieldModel::getResidual(i) != 0)
        {
            return false;
        }
    }
    return true;
}

/**	@brief 处理牌点击事件
 * @param touch 触摸对象
 * @param event 事件对象
 * @return 是否处理该点击事件
 */
bool PlayFieldController::handleCardClick(cocos2d::Touch* touch, cocos2d::Event* event)
{
    CardModel* cardModel = static_cast <CardModel*>(event->getCurrentTarget());
    cocos2d::Vec2 lovationInNode = cardModel->convertToNodeSpace(touch->getLocation());
    cocos2d::Size size = cardModel->getContentSize();
    cocos2d::Rect rect = cocos2d::Rect(0, 0, size.width, size.height);
    if (rect.containsPoint(lovationInNode))
    {
        if (cardModel->isTouchEnabled())
        {
            int cha = UndoModel::currentCard->getFace() - cardModel->getFace();
            if (cha == 1 || cha == -1)
            {   
                // 入栈
                UndoModel::currentCard->fadeOutAll();
                UndoModel::push(UndoModel::currentCard);

                // 切换currentCard
                auto action = cocos2d::MoveTo::create(0.2f, cocos2d::Vec2(700, 250));
                cardModel->runAction(action);
                cardModel->setTouchEnabled(false);
                int idx = cardModel->id.num;
                if (idx > 0)
                {
                    PlayFieldModel::getCardModel(cardModel->id.heap, idx - 1)->setTouchEnabled(true);
                }
                UndoModel::currentCard = cardModel;
                PlayFieldModel::residualMinus(cardModel->id.heap);

                if(isSucsess())
                {
                    GameController::returnToMenu();
                    CCLOG("WIN");
                }
            }

            CCLOG("ccc:%d", cardModel->getFace());
            return true;
        }


    }
    return false;
}




/**	@brief 初始化战场卡牌
 * @param levelConfig 关卡配置
 */
void PlayFieldController::init(LevelConfig levelConfig)
{
    // 初始化PlayFieldCardsModel
    CCLOG("levelConfig.hare.size:%d", levelConfig.PlayFieldCards.size());
    PlayFieldModel::resizeHeap(levelConfig.PlayFieldCards.size());
    PlayFieldModel::resizeResidual(levelConfig.PlayFieldCards.size());
    for(int i = 0; i < levelConfig.PlayFieldCards.size(); ++i)
    {
        for (int j = 0; j < levelConfig.PlayFieldCards[i].size(); ++j)
        {
            Card card = levelConfig.PlayFieldCards[i][j];
            CardModel* cardModel = CardModel::create(card);
            CCLOG("suits:%d face:%d x:%.1f y:%.1f", card.suit, card.face, cardModel->getPositionX(), cardModel->getPositionY());
            PlayFieldModel::residualAdd(i);
            PlayFieldModel::push_back(i, cardModel);
            CCLOG("");
        }
    }
    CCLOG("PlayFieldCardsModel.hare.size:%d", PlayFieldModel::heapSize());
}

