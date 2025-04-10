//
// Created by x3052 on 2025/3/28.
//

#include "Number.h"

Number::Number(){
    _numberImage = std::make_shared<Util::Image>("../Resources/Image/game_sources/default-0.png");
}

//show this number image
void Number::Show() {
    m_Drawable = _numberImage;
    m_Transform.translation = {_x, _y};
}

void Number::UpdateImage(int number) {
    _numberImage = std::make_shared<Util::Image>("../Resources/Image/game_sources/default-" + std::to_string(number) + ".png");
}

void Number::SetPosition(int x, int y) {
    _x = x, _y = y;
}
