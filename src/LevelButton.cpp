//
// Created by x3052 on 2025/4/16.
//
#include "Button/LevelButton.h"

#include <iostream>
#include <ostream>

LevelButton::LevelButton(std::string imagePath, int x, int y)
    : Button(imagePath , x, y, 100, 380) {
    SetZIndex(0);
}

void LevelButton::Translate(float deltaY)
{
    glm::vec2 pos  = getPosition();
    float      oldY = pos.y;

    pos.y += deltaY;

    constexpr float kSlope = 0.1f;
    float deltaX = std::abs(deltaY) * kSlope;

    if (deltaY > 0.f) {
        pos.x += (oldY < 0.f ? -deltaX :  deltaX);
    }
    else if (deltaY < 0.f) {                 // MoveDown
        pos.x += (oldY <= 0.f ?  deltaX : -deltaX);
    }

    setPosition(pos);
}

void LevelButton::CheckButtn() {
    if(m_Transform.translation.y == 0.0) {
        m_Drawable = whiteBtn;
        isBtnWhite = true;
    }
    else {
        m_Drawable = blueBtn;
        isBtnWhite = false;
    }
}


bool LevelButton::IsBtnWhite() {
    return isBtnWhite;
}

void LevelButton::MoveUp()   { Translate(+25.f); }
void LevelButton::MoveDown() { Translate(-25.f); }