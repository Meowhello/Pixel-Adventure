//
// Created by x3052 on 2025/4/16.
//
#include "SelectLevel.h"

#include <iostream>

#include "Util/Input.hpp"

SelectLevel::SelectLevel() {

    for(int i = 0; i<30;i++) {
        auto levelButton = std::make_shared<LevelButton>("../Resources/Image/select_level/test_button.png", 330 + i * 10, i * -100);
        _levelButtonVector.push_back(levelButton);
        AddChild(levelButton);
    }

}

int SelectLevel::Updtate() {
    for(auto levelButton: _levelButtonVector) {
        if(Util::Input::IfScroll()) {
            float scrollY = Util::Input::GetScrollDistance().y;
            if (scrollY > 0) {
                levelButton->MoveUp();
            } else if (scrollY < 0) {
                levelButton->MoveDown();
            }
        }
    }

    return 0;
}
