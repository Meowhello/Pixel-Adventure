//
// Created by x3052 on 2025/4/25.
//

#ifndef HP_H
#define HP_H
#include "Util/GameObject.hpp"
#include "OsuParser.h"
#include "Util/Image.hpp"

class HPBackground : public Util::GameObject {
public:
    HPBackground() {
        m_Drawable=std::make_shared<Util::Image>(RESOURCE_DIR "/Image/game_sources/scorebar-bg.png");
        m_Transform.translation={-300,340};
        m_ZIndex=1;
    }
    ~HPBackground() = default;
};

class HP : public Util::GameObject{
public:
    HP();
    ~HP() = default;
    void hpdrain(int level);
    void restart();
    float Gethp();

    float hp;

    // std::shared_ptr<OsuParser> _osuParser;

private:
    std::shared_ptr<HPBackground> _hpbg;
};

#endif //HP_H
