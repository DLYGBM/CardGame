#ifndef __GAME_CONTROLLER_H__
#define __GAME_CONTROLLER_H__

#include "LevelConfigLoder.h"
#include "LevelConfig.h"

/**	@class 游戏控制器
 * @brief 管理游戏流程
 */
class GameController
{
public:
    static void startGame(LevelId levelId);
    static void returnToMenu();
};

#endif