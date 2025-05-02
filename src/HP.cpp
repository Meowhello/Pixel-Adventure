//
// Created by x3052 on 2025/4/25.
//
#include "HP.h"
#include "Util/Image.hpp"

HP::HP() {
    m_Drawable=std::make_shared<Util::Image>(RESOURCE_DIR "/Image/game_sources/blood.png");
    m_Transform.translation={-300,350};
    m_ZIndex=2;
}

void HP::hpdrain(int level) {
    if (m_Transform.scale.x<0) {
        m_Transform.scale.x=0;
        m_Transform.translation.x=-500;
    }
    else {
        float diff;
        switch (level) { //比例（縮短且留在原位）：每縮0.1倍，x 要-32
            case 0:
                diff=0.05;
            break;
            case 1:
                diff=0.1;
            break;
            case 2:
                diff=0.15;
            break;
            case 3:
            case 4:
            case 5:
                diff=level/10;
            break;
            case 6:
            case 7:
                diff=level/9;
            break;
            case 8:
            case 9:
            case 10:
                diff=level/8;
        }
        m_Transform.translation.x-=32*diff;
        m_Transform.scale.x-=0.1*diff;
    }
}

void HP::restart() {
    m_Transform.scale={1,1};
    m_Transform.translation={-300,350};
}

int HP::Gethp() {
    return m_Transform.scale.x;
}
