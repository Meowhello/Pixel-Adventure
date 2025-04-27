//
// Created by x3052 on 2025/4/25.
//

#ifndef OSUPARSER_H
#define OSUPARSER_H
#include <cstdint>
#include <string>
#include <vector>

struct HitObject {
    int x = 0;          //!< 0–512
    int y = 0;          //!< 0–384
    int64_t hitTime = 0;//!< 毫秒
};

/// 關卡原始資料，供 Level 使用
struct LevelData {
    std::vector<HitObject> objects;  //!< 已依 hitTime 升冪排序
    int approachMs = 1200;           //!< 水果提前出現時間（依 AR 計算）
};

class OsuParser {
public:
    /**
     * 讀取並解析 .osu
     * @param path  .osu 完整檔案路徑
     * @param out   解析完成的 LevelData
     * @return      true=成功, false=失敗(檔案不存在或格式錯誤)
     */
    static bool ParseFile(const std::string& path, LevelData& out);
};

#endif //OSUPARSER_H
