#ifndef __PLAYFIELD_MODEL_H__
#define __PLAYFIELD_MODEL_H__

#include "CardModel.h"
/**	
 * @brief 战场卡牌模型数组
 */
static std::vector<std::vector<CardModel*>> PlayFieldCardsModel;
/**
 * @brief 战场剩余卡牌数数组
 */
static std::vector<int> playFieldResidual;


/**	@class 战场卡牌模数组
 * @brief 管理数组
 */
class PlayFieldModel 
{
	
public:
	static void push_back(int heap,CardModel * cardModel);
	static int heapSize();
	static int size(int heap);
	static CardModel* getCardModel(int heap, int index);
	static int getResidual(int heap);
	static void residualAdd(int heap);
	static void residualMinus(int heap);
	static void resizeHeap(int heap);
	static void resizeResidual(int size);
	static void clear();
};

#endif
