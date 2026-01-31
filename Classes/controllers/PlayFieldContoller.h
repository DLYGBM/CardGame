#ifndef __PLAYFIELD_CONTROLLER_H__
#define __PLAYFIELD_CONTROLLER_H__

#include "CardModel.h"
#include "LevelConfig.h"


/**	@class 战场卡牌控制器
 * @brief 处理战场卡牌点击事件
 */
class PlayFieldController
{


public:
    
    static void init(LevelConfig levelConfig);
    static bool handleCardClick(cocos2d::Touch* touch, cocos2d::Event* event);


};

#endif
