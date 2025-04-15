//
// Created by x3052 on 2025/4/4.
//

#include "Button/Button.h"
#include "Util/Input.hpp"

Button::Button(std::string filepath, int x, int y, int height, int width):_x(x), _y(y), _height(height), _width(width) {
    _buttonImage = std::make_shared<Util::Image>(filepath);
    m_Drawable = _buttonImage;
    m_Transform.translation = {_x, _y};
}

bool Button::IsButtonClick(glm::vec2 positon) {
    if (!Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB))
        return false;
    return positon.x > _x - (_width / 2) && positon.x < _x + (_width / 2) && positon.y > _y - (_height / 2) && positon.y < _y + (_height / 2);
}


