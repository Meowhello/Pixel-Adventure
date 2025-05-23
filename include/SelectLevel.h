//
// Created by x3052 on 2025/4/16.
//

#ifndef SELECTLEVEL_H
#define SELECTLEVEL_H
#include <memory>

#include "Button/LevelButton.h"
#include "Level.h"

class SelectLevel : public Util::GameObject {
public:
    SelectLevel();
    ~SelectLevel() = default;

    std::shared_ptr<Level> Update();
private:
    struct LevelConfig {
        std::string name;
        std::string bgmPath, sfxPath, bgPath, osuPath, btnPath;
    };
    std::vector<LevelConfig> _configs;
    std::vector<std::shared_ptr<LevelButton>> _buttons;
    std::shared_ptr<Background> _background = std::make_shared<Background>("../Resources/Image/main_page/main_background.png");

    int   _targetIdx   = -1;   // 被點擊、要捲到中央的按鈕索引
    float _remainDelta = 0.f;  // 還需要移動的距離 (px)
    const float SCROLL_SPEED = 800.f; // 速度 (px/sec) 可自行調
};

#endif //SELECTLEVEL_H
