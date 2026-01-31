#ifndef __STACK_MODEL_H__
#define __STACK_MODEL_H__

#include "CardModel.h"

/**	@brief 玩家卡牌模型数组
 *
 *	@details 用于存储玩家手牌、弃牌堆等卡牌的数组
 */
static std::vector<CardModel*> StackCardsModel;


/**
 * @brief 玩家卡牌模型数组中剩余卡牌数
 */
static int stackResidual = 0;

/**	@class 玩家卡牌模数组
 * @brief 管理数组
 */

class StackModel
{
private:
	
public:
	static void push_back(CardModel* cardModel);
	static int size();
	static CardModel* getCardModel(int index);
	static int getResidual();
	static void residualAdd();
	static void residualMinus();
	static void clear();
};

#endif
