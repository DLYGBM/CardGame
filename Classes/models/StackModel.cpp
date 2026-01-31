#include "StackModel.h"


void StackModel::push_back(CardModel* cardModel)
{
	StackCardsModel.push_back(cardModel);
}
/**
 * @brief 获取玩家卡牌模型数组的大小
 */
int StackModel::size()
{
	return StackCardsModel.size();
}


/**	@brief 获取玩家卡牌模型数组中的指定卡牌模型
 *
 *	@details 根据传入的索引值返回玩家卡牌模型数组中对应的卡牌模型指针
 */
CardModel* StackModel::getCardModel(int index)
{
	return StackCardsModel[index];
}

/**	@brief 获取玩家卡牌模型数组中剩余卡牌数
 *
 *	@details 返回当前玩家卡牌模型数组中剩余卡牌数
 */
int StackModel::getResidual()
{
	return stackResidual;
}

/**	@brief 增加玩家卡牌模型数组中剩余卡牌数
 *
 *	@details 每当玩家获得一张卡牌时调用此函数，增加剩余卡牌数
 */
void StackModel::residualAdd()
{
	++stackResidual;
}


/**	@brief 减少玩家卡牌模型数组中剩余卡牌数
 *
 *	@details 每当玩家使用一张卡牌时调用此函数，减少剩余卡牌数
 */
void StackModel::residualMinus()
{
	--stackResidual;
}

void StackModel::clear()
{
	StackCardsModel.clear();
	stackResidual = 0;
}
