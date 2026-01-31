#include "CardModel.h"
#include "ui/CocosGUI.h"


/**	@brief 设置卡牌ID
 *
 *	@param card 卡牌信息
 */
void CardModel::setCarID(Card card)
{
    id.num = card.num;
    id.area = card.area;
    id.heap = card.heap;
}

float CardModel::getPositionX()const
{
    return _position.x;
}

float CardModel::getPositionY()const
{
    return _position.y;
}

CardModel* CardModel::create(Card card)
{
    CardModel* cardSprite = new (std::nothrow) CardModel();
    if (cardSprite && cardSprite->init(card))
    {
        cardSprite->autorelease();
        return cardSprite;
    }
    CC_SAFE_DELETE(cardSprite);
    return nullptr;
}
/**	@brief 设置卡牌原始位置
 *
 *	@param position 位置
 */
void CardModel::mySetPosition(cocos2d::Vec2 position)
{
    _position = position;
}

cocos2d::Vec2 CardModel::myGetPosition()const
{
    return _position;
}

CardModel::CardModel():
    _suit(CST_NONE),
    _face(CFT_NONE),
    _touchEnabled(false)
{
    
}

CardModel::~CardModel()
{

}
/**	@brief 对卡牌及其子精灵执行淡出效果
 *
 */
void CardModel::fadeOutAll()
{
    // 对自身执行淡出
    auto fadeOut = cocos2d::FadeOut::create(0.2f);
    this->runAction(fadeOut);

    // 对所有子精灵执行淡出
    for(auto child : getChildren()) 
    {
        child->runAction(fadeOut->clone());
    }
}

/**	@brief 对卡牌及其子精灵执行淡入效果
 *
 */
void CardModel::fadeInAll()
{
    auto fadeIn = cocos2d::FadeIn::create(0.2f);
    this->runAction(fadeIn);
    for(auto child : getChildren()) 
    {
        child->runAction(fadeIn->clone());
    }
}


/**	@brief 设置卡牌花色精灵
 *
 *	@param card 卡牌信息
 */
void CardModel::setSuiteSprite(Card card)
{
    cocos2d::Sprite* suiteSprite = nullptr;

    switch (card.suit)
    {
    case CST_CLUBS:
        suiteSprite = cocos2d::Sprite::create("res/res/suits/club.png");
        break;
    case CST_DIAMONDS:
        suiteSprite = cocos2d::Sprite::create("res/res/suits/diamond.png");
        break;
    case CST_HEARTS:
        suiteSprite = cocos2d::Sprite::create("res/res/suits/heart.png");
        break;
    case CST_SPADES:
        suiteSprite = cocos2d::Sprite::create("res/res/suits/spade.png");
        break;
    default:
        break;
    }
    cocos2d::Size cardSize = getContentSize();
    cocos2d::Size suiteSize = suiteSprite->getContentSize();
    suiteSprite->setPosition(cocos2d::Vec2(cardSize.width / 2 + (cardSize.width - suiteSize.width) / 2 - 20, cardSize.height / 2 + (cardSize.height - suiteSize.height) / 2 - 20));
    addChild(suiteSprite);
}

/**	@brief 给卡牌添加子精灵
 *
 *	@param card 卡牌信息
 */
void CardModel::setNumSprite( Card card)
{
    std::vector<std::string> NumText = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
    // 红色
    
    cocos2d::Size cardSize = getContentSize();
    if (card.suit == CST_DIAMONDS || card.suit == CST_HEARTS)
    {
        // 创建小数字
        std::string smallRedNumPath = cocos2d::StringUtils::format("res/res/number/small_red_%s.png", NumText[card.face].c_str());
        cocos2d::Sprite* smallRedNumSprite = cocos2d::Sprite::create(smallRedNumPath);
        cocos2d::Size smallRedNumSize = smallRedNumSprite->getContentSize();
        smallRedNumSprite->setPosition(cocos2d::Vec2(cardSize.width / 2 - (cardSize.width - smallRedNumSize.width) / 2 + 20, cardSize.height / 2 + (cardSize.height - smallRedNumSize.height) / 2 - 20));
        addChild(smallRedNumSprite);
        // 创建大数字
        std::string bigRedNumPath = cocos2d::StringUtils::format("res/res/number/big_red_%s.png", NumText[card.face].c_str());
        cocos2d::Sprite* bigRedNumSprite = cocos2d::Sprite::create(bigRedNumPath);
        bigRedNumSprite->setPosition(cocos2d::Vec2(cardSize.width / 2, cardSize.height / 2 - 50));
        addChild(bigRedNumSprite);
    }
    else
    {
        std::string smallBlackNumPath = cocos2d::StringUtils::format("res/res/number/small_black_%s.png", NumText[card.face].c_str());
        cocos2d::Sprite* smallBlackNumSprite = cocos2d::Sprite::create(smallBlackNumPath);
        cocos2d::Size smallNumSize = smallBlackNumSprite->getContentSize();
        smallBlackNumSprite->setPosition(cocos2d::Vec2(cardSize.width / 2 - (cardSize.width - smallNumSize.width) / 2 + 20, cardSize.height / 2 + (cardSize.height - smallNumSize.height) / 2 - 20));
        addChild(smallBlackNumSprite);

        std::string bigBlackNumPath = cocos2d::StringUtils::format("res/res/number/big_black_%s.png", NumText[card.face].c_str());
        cocos2d::Sprite* bigBlackNumSprite = cocos2d::Sprite::create(bigBlackNumPath);
        bigBlackNumSprite->setPosition(cocos2d::Vec2(cardSize.width / 2, cardSize.height / 2 - 50));
        addChild(bigBlackNumSprite);
    }
}




/**	@brief 初始化卡牌精灵
 *
 *	@param card 卡牌信息
 *	@return 是否初始化成功
 */
bool CardModel::init(Card card)
{
    if (!Sprite::initWithFile("res/res/card_general.png"))
    {
        return false;
    }
    _suit = card.suit;
    _face = card.face;
    _position = card.position;
    setCarID(card);
    setPosition(cocos2d::Vec2(card.position.x , card.position.y ));
    // 创建花色和点数
    // 创建花色
    setNumSprite(card);
    setSuiteSprite(card);
    

    return true;
}





/**	@brief 获取卡牌花色
 *
 *	@return 卡牌花色
 */
CardSuitType CardModel::getSuit() const
{
    return _suit;
}

/**	@brief 获取卡牌点数
 *
 *	@return 卡牌点数
 */
CardFaceType CardModel::getFace() const
{
   
    return _face;
}

/**	@brief 设置卡牌是否可触摸
 *
 *	@param enabled 是否可触摸
 */
void CardModel::setTouchEnabled(bool enabled)
{
    _touchEnabled = enabled;
}

/**	@brief 获取卡牌是否可触摸
 *
 *	@return 是否可触摸
 */
bool CardModel::isTouchEnabled() const
{
    return _touchEnabled;
}






