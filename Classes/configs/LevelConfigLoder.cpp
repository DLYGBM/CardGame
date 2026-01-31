#include "LevelConfigLoder.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

using namespace rapidjson;


/**	@brief 从文件加载JSON内容
 * @param filePath 文件路径
 * @param jsonContent JSON内容（输出参数）
 * @return 是否加载成功
 */
bool LoadJsonFromFile(const std::string& filePath, std::string& jsonContent)
{
    if(!cocos2d::FileUtils::getInstance()->isFileExist(filePath)) 
    {
        CCLOG("File does not exist: %s", filePath.c_str());
        return false;
    }

    jsonContent = cocos2d::FileUtils::getInstance()->getStringFromFile(filePath);
    return !jsonContent.empty();
}

/**	@brief 从JSON内容加载关卡配置
 * @param jsonContent JSON内容
 * @param levelConfig 关卡配置（输出参数）
 * @param levelID 关卡ID
 * @return 是否加载成功
 */
bool LoadLevelFromJson(const std::string& jsonContent, LevelConfig& levelConfig, LevelId levelID)
{
    rapidjson::Document document;
    document.Parse(jsonContent.c_str());
    
    if (document.HasParseError()) 
    {
        CCLOG("JSON parse error: %s", document.GetParseError());
        return false;
    }

    // 清空之前的配置
    levelConfig.PlayFieldCards.clear();
    levelConfig.StackCards.clear();

    //解析关卡配置
    CCLOG("111111111111111111111111111111111111111111111");
    if(document.HasMember("level") && document["level"].IsArray())
    {
        // 解析指定关卡配置
        const Value& leveldArray = document["level"];
        CCLOG("%d", leveldArray.Size());
        
        // 解析Playfield
        const Value& playfieldArray = leveldArray[levelID]["Playfield"];
        levelConfig.PlayFieldCards.resize(playfieldArray.Size());
        for(SizeType i = 0; i < playfieldArray.Size(); ++i)
        {
            const Value& rowArray = playfieldArray[i];
            for(SizeType j = 0; j < rowArray.Size(); ++j)
            {
                const Value& cardValue = rowArray[j];
                Card card;
                // 解析CardFace
                if (cardValue.HasMember("CardFace") && cardValue["CardFace"].IsInt()) 
                {
                    card.face = static_cast<CardFaceType>(cardValue["CardFace"].GetInt());
                } 
                else 
                {
                    card.face = CFT_NONE;
                }
                
                // 解析CardSuit
                if (cardValue.HasMember("CardSuit") && cardValue["CardSuit"].IsInt()) 
                {
                    card.suit = static_cast<CardSuitType>(cardValue["CardSuit"].GetInt());
                } 
                else 
                {
                    card.suit = CST_NONE;
                }
                
                // 解析Position
                if (cardValue.HasMember("Position") && cardValue["Position"].IsObject()) 
                {
                    const Value& positionValue = cardValue["Position"];
                    if (positionValue.HasMember("x") && positionValue["x"].IsNumber()) 
                    {
                        card.position.x = positionValue["x"].GetFloat();
                        CCLOG(" Card x: %.1f", card.position.x);
                    } 
                    else 
                    {
                        card.position.x = 0.0f;
                    }
                    if (positionValue.HasMember("y") && positionValue["y"].IsNumber()) 
                    {
                        card.position.y = positionValue["y"].GetFloat();
                    } 
                    else 
                    {
                        card.position.y = 0.0f;
                    }
                }
                card.area = CardArea::PLAYFIELD;
                card.heap = i;
                card.num = j;
                CCLOG("//////////////////////////////////////");
                levelConfig.PlayFieldCards[i].push_back(card);
                CCLOG("//////////////////////////////////////");
            } 
        }

        CCLOG("%d", levelConfig.PlayFieldCards.size());
        CCLOG("//////////////////////////////////////");
        // 解析Stack
        const Value& stackArray = leveldArray[levelID]["Stack"];
        for(SizeType i = 0; i < stackArray.Size(); ++i)
        {
            const Value& cardValue = stackArray[i];
            Card card;
            
            // 解析CardFace
            if (cardValue.HasMember("CardFace") && cardValue["CardFace"].IsInt()) 
            {
                card.face = static_cast<CardFaceType>(cardValue["CardFace"].GetInt());
            } 
            else 
            {
                card.face = CFT_NONE;
            }
            
            // 解析CardSuit
            if (cardValue.HasMember("CardSuit") && cardValue["CardSuit"].IsInt()) 
            {
                card.suit = static_cast<CardSuitType>(cardValue["CardSuit"].GetInt());
            } 
            else 
            {
                card.suit = CST_NONE;
            }
            
            // 解析Position
            if (cardValue.HasMember("Position") && cardValue["Position"].IsObject()) 
            {
                const Value& positionValue = cardValue["Position"];
                if (positionValue.HasMember("x") && positionValue["x"].IsNumber()) 
                {
                    card.position.x = positionValue["x"].GetFloat();
                } 
                else 
                {
                    card.position.x = 0.0f;
                }
                if (positionValue.HasMember("y") && positionValue["y"].IsNumber()) 
                {
                    card.position.y = positionValue["y"].GetFloat();
                } 
                else 
                {
                    card.position.y = 0.0f;
                }
            }
            card.area = CardArea::STACK;
            card.num = i;
            card.heap = 1;
            levelConfig.StackCards.push_back(card);
        }
    }
    CCLOG("%d", levelConfig.StackCards.size());
    return true;
}

/**	@brief 从文件创建关卡配置
 * @param levelID 关卡ID
 * @return 关卡配置
 */
LevelConfig CreateLevelFromFile(LevelId levelID)
{
    std::string jsonContent;
    std::string filePath;
    filePath = cocos2d::FileUtils::getInstance()->fullPathForFilename("level.json");

    // 从文件加载JSON内容
    if (!LoadJsonFromFile(filePath, jsonContent))
    {
        CCLOG("cocos2d: fullPathForFilename: No file found at configs/level.json. Possible missing file.Failed to load JSON file: %s", filePath.c_str());
    }
    
    CCLOG("jsonContent: %s", jsonContent.c_str());
    LevelConfig levelConfig;
    // 解析JSON内容
    if (LoadLevelFromJson(jsonContent, levelConfig, levelID))
    {
        CCLOG("Successfully parsed game config");
        // 打印解析结果 
        CCLOG("%s:%d parse game config Ok",__FILE__,__LINE__);
        //printLevelConfig(levelConfig);
        return levelConfig;
    }
    else
    {
        CCLOG("%s:%d Failed to parse game config",__FILE__,__LINE__);
    }

}



 /**	@brief 加载关卡配置
  * @param levelId 关卡ID
  * @return 关卡配置
 */
LevelConfig LevelConfigLoder::loadLevelConfig(LevelId levelId)
{     
    return CreateLevelFromFile(levelId);
}




