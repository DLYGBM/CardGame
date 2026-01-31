#ifndef __LEVEL_CONFIG_LODER_H__
#define __LEVEL_CONFIG_LODER_H__

#include "LevelConfig.h"

/**	@class 关卡配置加载器
 * @brief 加载关卡配置
 */
class LevelConfigLoder 
{
public: 
    static LevelConfig loadLevelConfig(LevelId levelId);
    //static LevelConfig CreateLevelFromFile();
    //static bool LoadJsonFromFile(const std::string& filePath, std::string& jsonContent);
    //static bool LoadLevelFromJson(const std::string& jsonContent, LevelConfig& levelConfig);
};



#endif