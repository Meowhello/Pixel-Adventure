//
// Created by x3052 on 2025/4/25.
//
#include "HP.h";
#include "Util/Image.hpp"

HP::HP() {
    m_Drawable=std::make_shared<Util::Image>(RESOURCE_DIR "/Image/game_sources/blood.png");
    //m_Transform.scale={0.8,0.8};
    m_Transform.translation={-300,350};
    m_ZIndex=2;
}
