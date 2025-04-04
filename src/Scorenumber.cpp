//
// Created by x3052 on 2025/3/28.
//

#include "Scorenumber.h"

Scorenumber::Scorenumber(){
    _scoreImage = std::make_shared<Util::Image>("../Resources/Image/game_sources/default-0.png");
}

//show this number image
void Scorenumber::Show() {
    m_Drawable = _scoreImage;
    m_Transform.translation = {_x, _y};
}

void Scorenumber::UpdateImage(int number) {
    _scoreImage = std::make_shared<Util::Image>("../Resources/Image/game_sources/default-" + std::to_string(number) + ".png");
}

void Scorenumber::SetPosition(int x, int y) {
    _x = x, _y = y;
}
