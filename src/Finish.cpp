//
// Created by tfboy on 2025/5/9.
//
#include "Finish.h"

#include "Util/Image.hpp"

Finish::Finish() {
    m_Drawable=std::make_shared<Util::Image>((RESOURCE_DIR "/Image/game_sources/end_page.png"));
    m_Transform.scale = {0.7, 0.7};
    m_ZIndex=2;
}
