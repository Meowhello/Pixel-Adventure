//
// Created by tfboy on 2025/3/28.
//
#include "Background.h"

#include "MainMenu.h"

Background::Background(std::string bgPath) {
    m_Drawable = std::make_shared<Util::Image>(bgPath);
    m_ZIndex = -10;
}
