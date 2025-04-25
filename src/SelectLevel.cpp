//
// Created by x3052 on 2025/4/16.
//
#include "SelectLevel.h"

#include <iostream>

#include "Util/Input.hpp"

SelectLevel::SelectLevel() {

    for(int i = 0; i<30;i++) {
        auto levelButton = std::make_shared<LevelButton>("../Resources/Image/select_level/easy_open.png", 400 + i * 10, i * -100);
        _levelButtonVector.push_back(levelButton);
        AddChild(levelButton);
    }
    auto level = std::make_shared<Level>("Haruhikage", Level::Difficulty::Easy, "../Resources/music/Haruhikage_CRYCHIC.mp3", "../Resources/music/normal-hitclap.wav", "");
    for(int i = 0; i<30;i++) {
        _levelVector.push_back(level);
    }
}

std::shared_ptr<Level> SelectLevel::Updtate() {
    for(int i = 0; i < _levelButtonVector.size(); i++) {
        if(Util::Input::IfScroll()) {
            float scrollY = Util::Input::GetScrollDistance().y;
            if (scrollY > 0) {
                _levelButtonVector[i]->MoveDown();
            } else if (scrollY < 0) {
                _levelButtonVector[i]->MoveUp();
            }
        }

        glm::vec2 mouseposition = Util::Input::GetCursorPosition();
        if(_levelButtonVector[i]->IsButtonClick(mouseposition)) {
            return _levelVector[i];
        }
    }

    return nullptr;
}
