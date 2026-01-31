#ifndef __STACK_CONTROLLER_H__
#define __STACK_CONTROLLER_H__

#include "LevelConfigLoder.h"
#include "cocos2d.h"
#include "PlayFieldContoller.h"
#include "PlayGameScene.h"
#include "CardModel.h"




/**	@class 玩家卡牌控制器
 * @brief 处理玩家卡牌点击事件
 */
class StackController
{
public:
	
	static void init(LevelConfig levelConfig);
	static bool handleCardClick(cocos2d::Touch* touch, cocos2d::Event* event);

};

#endif
