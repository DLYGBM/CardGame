#include "PlayFieldModel.h"

/**	@brief 向指定堆中添加卡牌模型
 * @param heap 指定堆的索引
 * @param cardModel 要添加的卡牌模型指针
 */
void PlayFieldModel::push_back(int heap,CardModel* cardModel)
{
	PlayFieldCardsModel[heap].push_back(cardModel);
}
/**
 * @brief 获取指定堆的大小
 * @param heap 指定堆的索引
 */
int PlayFieldModel::size(int heap)
{
	return PlayFieldCardsModel[heap].size();
}
/**
 * @brief 获取堆的数量
 */
int PlayFieldModel::heapSize()
{
	return PlayFieldCardsModel.size();
}
	
/**	@brief 获取指定堆中指定索引的卡牌模型
 * @param heap 指定堆的索引
 * @param index 指定卡牌模型的索引
 */
CardModel* PlayFieldModel::getCardModel(int heap,int index)
{
	return PlayFieldCardsModel[heap][index];
}

/**	@brief 获取指定堆中剩余卡牌数
 * @param heap 指定堆的索引
 */
int PlayFieldModel::getResidual(int heap)
{
	return playFieldResidual[heap];
}
/**	@brief 增加指定堆中剩余卡牌数
 * @param heap 指定堆的索引
 */
void PlayFieldModel::residualAdd(int heap)
{
	++playFieldResidual[heap];
}
/**	@brief 减少指定堆中剩余卡牌数
 * @param heap 指定堆的索引
 */
void PlayFieldModel::residualMinus(int heap)
{
	--playFieldResidual[heap];
}
/**	@brief 调整堆的数量
 * @param heap 新的堆的数量
 */
void PlayFieldModel::resizeHeap(int heap)
{
	PlayFieldCardsModel.resize(heap);
}
/**	@brief 调整剩余卡牌数数组的大小
 * @param size 新的数组大小
 */
void PlayFieldModel::resizeResidual(int size)
{
	playFieldResidual.resize(size);
}
/**	@brief 清空所有堆和剩余卡牌数数组
 *
 *	@details 清空PlayFieldCardsModel和playFieldResidual，重置为初始状态
 */
void PlayFieldModel::clear()
{
	PlayFieldCardsModel.clear();
	playFieldResidual.clear();
}

