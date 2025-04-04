//
// Created by nkuht on 2025/4/5.
//
//
// Created by tfboy on 2025/3/28.
//
#include "Background.h"

Background::Background(level change=level::level_1) {
    std::string filepath;
    if(change==level::level_1) {
        filepath = (RESOURCE_DIR "/Image/game_sources/background.jpg");
    }
    else if(change==level::pause) {
        filepath = (RESOURCE_DIR "/Image/game_sources/pause_background.png");
    }
    m_Drawable = std::make_shared<Util::Image>(filepath);
    m_ZIndex = -10;
}
