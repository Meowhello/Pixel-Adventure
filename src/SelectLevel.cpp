//
// Created by x3052 on 2025/4/16.
//
#include "SelectLevel.h"

#include <iostream>

#include "Util/Input.hpp"

// SelectLevel::SelectLevel() {
//     AddChild(_background);
//     for(int i = 0; i<30;i++) {
//         auto levelButton = std::make_shared<LevelButton>("../Resources/Image/select_level/easy_open.png", 400 + i * 10, i * -100);
//         _levelButtonVector.push_back(levelButton);
//         AddChild(levelButton);
//     }
//     auto level = std::make_shared<Level>("Haruhikage", Level::Difficulty::Easy,
//                                         "../Resources/music/Haruhikage_CRYCHIC.mp3",
//                                         "../Resources/music/normal-hitclap.wav",
//                                         "",
//                                         "../Resources/music/CRYCHIC - Haruhikage (TV Size) (lkx_Shore) [Normal].osu");
//     for(int i = 0; i<30;i++) {
//         _levelVector.push_back(level);
//     }
// }

SelectLevel::SelectLevel() {
    // 只把配置 push 进来
    _configs = {
        {"Haruhikage", Level::Difficulty::Normal, "../Resources/music/Haruhikage_CRYCHIC.mp3", "../Resources/music/normal-hitclap.wav", "", "../Resources/music/CRYCHIC - Haruhikage (TV Size) (lkx_Shore) [Normal].osu", "../Resources/Image/select_level/easy_open.png"},
        // … 其他项…
    };
    for (int i = 0; i < _configs.size(); ++i) {
        auto btn = std::make_shared<LevelButton>(_configs[i].btnPath, 400 + i * 10, i * -100);
        _buttons.push_back(btn);
        AddChild(btn);
    }
}

std::shared_ptr<Level> SelectLevel::Updtate() {
    for(int i = 0; i < _buttons.size(); i++) {
        if(Util::Input::IfScroll()) {
            float scrollY = Util::Input::GetScrollDistance().y;
            if (scrollY > 0) {
                _buttons[i]->MoveDown();
            } else if (scrollY < 0) {
                _buttons[i]->MoveUp();
            }
        }

        glm::vec2 mouseposition = Util::Input::GetCursorPosition();
        if(_buttons[i]->IsButtonClick(mouseposition)) {
            auto &cfg = _configs[i];
            return std::make_shared<Level>(
                cfg.name, cfg.diff,
                cfg.bgmPath, cfg.sfxPath,
                cfg.bgPath, cfg.osuPath);
        }
    }

    return nullptr;
}
