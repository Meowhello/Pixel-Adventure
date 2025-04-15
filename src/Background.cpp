//
// Created by tfboy on 2025/3/28.
//
#include "Background.h"

#include "MainMenu.h"

Background::Background(level change=level::level_1) {
    std::string filepath;
    switch (change) {
        case level::MainMenu:
            filepath = (RESOURCE_DIR "/Image/main_page/main_background.png");
            break;
        case level::level_1:
            filepath = (RESOURCE_DIR "/Image/game_sources/background.jpg");
            break;
        case level::pause:
            filepath = (RESOURCE_DIR "/Image/game_sources/pause_background.png");
            break;
    }
    m_Drawable = std::make_shared<Util::Image>(filepath);
    m_ZIndex = -10;
}
