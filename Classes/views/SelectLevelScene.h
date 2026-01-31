#ifndef __SELECT_LEVEL_SCENE_H__
#define __SELECT_LEVEL_SCENE_H__

#include "cocos2d.h"
#include "LevelConfig.h"

/**
 * @class 菜单场景
 * @brief 选择关卡菜单场景
 * 
 */

class SelectLevelScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();


    CREATE_FUNC(SelectLevelScene);


private:
    void _onCardClickCallback(cocos2d::Ref* pSender);

};








#endif // 
