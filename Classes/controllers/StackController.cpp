#include "StackController.h"
#include "ui/CocosGUI.h"
#include "LevelConfig.h"
#include "StackModel.h"
#include "UndoModel.h"



/**	@brief 处理牌点击事件
 * @param touch 触摸对象
 * @param event 事件对象
 * @return 是否处理该点击事件
 */
bool StackController::handleCardClick(cocos2d::Touch* touch, cocos2d::Event* event)
{
    CardModel* cardModel = static_cast <CardModel*>(event->getCurrentTarget());
    cocos2d::Vec2 lovationInNode = cardModel->convertToNodeSpace(touch->getLocation());
    cocos2d::Size size = cardModel->getContentSize();
    cocos2d::Rect rect = cocos2d::Rect(0, 0, size.width, size.height);
    if (rect.containsPoint(lovationInNode))
    {
        
        if (cardModel->isTouchEnabled())
        {
            // 入栈
            UndoModel::currentCard->fadeOutAll();
            UndoModel::push(UndoModel::currentCard);
            
            // 切换currentCard
            cardModel->setTouchEnabled(false);
            const int idx = cardModel->id.num ;
            if (idx > 0)
            {
                // 使能下一张牌
                StackModel::getCardModel(idx-1)->setTouchEnabled(true);
            }
           
            auto action = cocos2d::MoveTo::create(0.2f, cocos2d::Vec2(700, 250));
            cardModel->runAction(action);
            StackModel::residualMinus();
            UndoModel::currentCard = cardModel;
            CCLOG("ccc:%d size:%d", StackModel::getResidual(), UndoModel::size());
        }
        
        return true;
    }
    return false;

}


/**	@brief 初始化玩家卡牌数据模型
 * @param levelConfig 关卡配置数据
 */
void StackController::init(LevelConfig levelConfig)
{
    // 初始化PlayFieldCardsModel
    
    for (int i = 0; i < levelConfig.StackCards.size(); ++i)
    {
        
        Card card = levelConfig.StackCards[i];
        CardModel* cardModel = CardModel::create(card);
        CCLOG("face:%d face:%d x:%.1f y:%.1f", card.suit, card.face, cardModel->getPositionX(), cardModel->getPositionY());
        StackModel::push_back(cardModel);
        StackModel::residualAdd();
    }
    CCLOG("StackCardsModel.size:%d", StackCardsModel.size());
}