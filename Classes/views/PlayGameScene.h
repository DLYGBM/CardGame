#ifndef __PLAYGAME_H__
#define __PLAYGAME_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

/** 
 * @class 游戏场景
 * @brief 负责添加卡牌
 */
class PlayGameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(PlayGameScene);

    void createMainCardArea();

    void createCardStackArea();

};








#endif // __PLAYGAME_H__
