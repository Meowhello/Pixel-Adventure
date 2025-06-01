//
// Created by x3052 on 2025/4/4.
//

#include "Button/Button.h"
#include "Util/Input.hpp"

Button::Button(std::string filepath, int x, int y, int height, int width) {
    m_Drawable = std::make_shared<Util::Image>(filepath);
    m_Transform.translation = {x, y};
    _size = {width, height};
}

glm::vec2 Button::getPosition() const {
    return m_Transform.translation;
}

glm::vec2 Button::getSize() const {
    return _size;
}

void Button::setPosition(const glm::vec2& pos) {
    m_Transform.translation = pos;
}

void Button::setSize(const glm::vec2& size) {
    _size = size;
}


bool Button::IsButtonClick(glm::vec2 position) {
    if (!Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) return false;

    auto pos = m_Transform.translation;
    auto size = _size;
    return position.x > pos.x - size.x / 2 &&
           position.x < pos.x + size.x / 2 &&
           position.y > pos.y - size.y / 2 &&
           position.y < pos.y + size.y / 2;
}

bool Button::IsOnButton(glm::vec2 position) {
    auto pos = m_Transform.translation;
    auto size = _size;
    return position.x > pos.x - size.x / 2 &&
           position.x < pos.x + size.x / 2 &&
           position.y > pos.y - size.y / 2 &&
           position.y < pos.y + size.y / 2;
}


