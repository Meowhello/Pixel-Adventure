//
// Created by x3052 on 2025/4/15.
//
#include "MainMenu.h"

#include "Util/Input.hpp"

MainMenu::MainMenu() {
    AddChild(_playButton);
    AddChild(_exitButton);
    AddChild(_background);
    m_Drawable = std::make_shared<Util::Image>((RESOURCE_DIR "/Image/main_page/cd.png"));
    m_Transform.scale = {0.8, 0.8};
    m_ZIndex = 5;
}

int MainMenu::Update() {
    glm::vec2 mouseposition = Util::Input::GetCursorPosition();

    if(_playButton->IsButtonClick(mouseposition)) {
        return 1;
    }

    if(_exitButton->IsButtonClick(mouseposition)) {
        return 2;
    }

    return 0;
}

