#include "UndoModel.h"
#include "ui/CocosGUI.h"
#include "CardModel.h"
#include "StackModel.h"
#include "PlayFieldModel.h"
#include "LevelConfig.h"

/**
 * @brief 当前比较的卡牌模型指针
 */
CardModel* UndoModel::currentCard = nullptr;

int UndoModel::size()
{
    return UndoStack.size();
}

/**
 * @brief 将卡牌模型指针压入撤销栈
 */
 void UndoModel::push(CardModel* cardModel)
{
    UndoStack.push(cardModel);
}
CardModel* UndoModel::pop()
{
    if (UndoStack.empty())
    {
        CCLOG("UndoStack is empty");
        return nullptr;
        
    }
    CardModel* cardModel = UndoStack.top();
    UndoStack.pop();
    return cardModel;
}
/**
 * @brief 处理撤销操作的触摸事件
 * @param touch 触摸对象
 * @param event 触摸事件
 */
bool UndoModel::Back(cocos2d::Touch* touch, cocos2d::Event* event)
{
    // 将触摸点转换为标签本地坐标
    auto label = dynamic_cast<cocos2d::Label*>(event->getCurrentTarget());
    cocos2d::Vec2 locationInNode = label->convertToNodeSpace(touch->getLocation());
    cocos2d::Size size = label->getContentSize();
    cocos2d::Rect rect = cocos2d::Rect(0, 0, size.width, size.height);
    
     
    if (rect.containsPoint(locationInNode)) 
    {
        CardModel* card = pop();
        
        if (card != nullptr)
        {
            if (UndoModel::currentCard->id.area == STACK)
            {
                CCLOG("Back");
                CCLOG("%d", StackModel::getResidual()); 
                CCLOG("%d", card->getFace());
                
                int idx = UndoModel::currentCard->id.num;
                auto move = cocos2d::MoveTo::create(0.2f, UndoModel::currentCard->myGetPosition());
                UndoModel::currentCard->runAction(move);
                UndoModel::currentCard->setTouchEnabled(true);
                if (idx > 0)
                {
                    StackModel::getCardModel(idx - 1)->setTouchEnabled(false);
                }
                
                StackModel::residualAdd();

                card->fadeInAll();
                UndoModel::currentCard = card;
                
            }
            else
            {
                int idx = UndoModel::currentCard->id.num;
                auto move = cocos2d::MoveTo::create(0.2f, UndoModel::currentCard->myGetPosition());
                UndoModel::currentCard->runAction(move);
                UndoModel::currentCard->setTouchEnabled(true);
                if (idx > 0)
                {
                    PlayFieldModel::getCardModel(UndoModel::currentCard->id.heap, idx - 1)->setTouchEnabled(false);
                }
                PlayFieldModel::residualAdd(UndoModel::currentCard->id.heap);
                card->fadeInAll();
                UndoModel::currentCard = card;

            }
        }
        else
        {
            CCLOG("Back null");
        }
        return true;  // 处理这个触摸
       
    }
    return false;  // 不处理
}
