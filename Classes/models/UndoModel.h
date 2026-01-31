#ifndef UNDO_MODEL_H
#define UNDO_MODEL_H
#include "CardModel.h"

#include <stack> 


/** 
 * @brief 撤销栈
 */
static std::stack<CardModel*> UndoStack;


/** 
 * @class 撤销模型
 * @brief 弹栈撤销
 */


class UndoModel
{
public:
    static CardModel* currentCard;
    static void push(CardModel* cardModel);
    static CardModel* pop();
    static bool Back(cocos2d::Touch* touch, cocos2d::Event* event);
    static int size();
};



#endif
