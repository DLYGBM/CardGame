#ifndef __CAR_H__
#define __CAR_H__

#include "cocos2d.h"
#include "LevelConfig.h"
#include "ui/CocosGUI.h"
#include "LevelConfig.h"





typedef struct CardID
{
    int num;
    CardArea area;
    int heap;
}CardID;


/**	@class 精灵卡牌模型
 * @brief 创建卡牌
 */

class CardModel : public cocos2d::Sprite
{
public:
    CardID id;
    void setCarID(Card card);
    static CardModel* create(Card card);
    CardModel();
    virtual ~CardModel();

    bool init(Card card);
    // 获取卡牌信息
    CardSuitType getSuit() const;
    CardFaceType getFace() const;
    float getPositionX() const;
    float getPositionY()const;
    // 设置卡牌是否可触摸
    void setTouchEnabled(bool enabled);
    bool isTouchEnabled() const;
    void setNumSprite(Card card);
    void setSuiteSprite(Card card);
    //cocos2d::MoveTo* move;
    void mySetPosition(cocos2d::Vec2 position);
    cocos2d::Vec2 myGetPosition()const;
    void fadeOutAll();
    void fadeInAll();
private:
    // 卡牌信息
    CardSuitType _suit;
    CardFaceType _face;
    cocos2d::Vec2 _position;
    bool _touchEnabled;
};

#endif
