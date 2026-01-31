#ifndef __LEVEL_CONFIG_H__
#define __LEVEL_CONFIG_H__
#include "ui/CocosGUI.h"



/** 
 * @brief 关卡ID
 */
enum LevelId
{
    LEVEL_1=0,
    LEVEL_2,
    LEVEL_3
};


/** 
 * @brief 牌花色类型
 */
enum CardSuitType
{
    CST_NONE = -1,
    CST_CLUBS,      // 梅花
    CST_DIAMONDS,   // 方块
    CST_HEARTS,     // 红桃
    CST_SPADES,     // 黑桃
    CST_NUM_CARD_SUIT_TYPES
};

/** 
 * @brief 牌面类型
 */
enum CardFaceType
{
    CFT_NONE = -1,
    CFT_ACE,
    CFT_TWO,
    CFT_THREE,
    CFT_FOUR,
    CFT_FIVE,
    CFT_SIX,
    CFT_SEVEN,
    CFT_EIGHT,
    CFT_NINE,
    CFT_TEN,
    CFT_JACK,
    CFT_QUEEN,
    CFT_KING,
    CFT_NUM_CARD_FACE_TYPES
};

/** 
 * @brief 牌区域
 */
enum CardArea
{
    STACK,
    PLAYFIELD
};

/** 
 * @brief 牌结构体
 */
typedef struct Card
{   
    int num;
    CardArea area;
    int heap;
    CardSuitType suit;
    CardFaceType face;
    cocos2d::Vec2 position;
} Card;


/** 
 * @brief 关卡配置结构体
 */
typedef struct LevelConfig
{
public:
    std::vector<std::vector<Card>> PlayFieldCards;
    std::vector<Card> StackCards;
}LevelConfig;



#endif // !
