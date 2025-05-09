//
// Created by x3052 on 2025/4/16.
//
#include "SelectLevel.h"

#include <iostream>

#include "Util/Input.hpp"
SelectLevel::SelectLevel() {
    AddChild(_background);
    // 只把配置 push 进来
    _configs = {
        {"Haruhikage", Level::Difficulty::Normal, "../Resources/Songs/2070468 CRYCHIC - Haruhikage (TV Size)/audio.mp3", "../Resources/music/normal-hitclap.wav", "../Resources/Songs/2070468 CRYCHIC - Haruhikage (TV Size)/1.png", "../Resources/Songs/2070468 CRYCHIC - Haruhikage (TV Size)/CRYCHIC - Haruhikage (TV Size) (lkx_Shore) [Normal].osu", "../Resources/Image/select_level/easy_open.png"},
        {"Georgette Me, Georgette You", Level::Difficulty::Normal, "../Resources/Songs/2308600 Ave Mujica - Georgette Me, Georgette You (TV Size)/audio.mp3", "../Resources/music/normal-hitclap.wav", "../Resources/Songs/2308600 Ave Mujica - Georgette Me, Georgette You (TV Size)/BG.PNG", "../Resources/Songs/2308600 Ave Mujica - Georgette Me, Georgette You (TV Size)/Ave Mujica - Georgette Me, Georgette You (TV Size) (Plus4j) [GfTNT's Hard].osu", "../Resources/Image/select_level/easy_open.png"},
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
