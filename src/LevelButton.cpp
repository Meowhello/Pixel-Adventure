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

void LevelButton::MoveUp() {
    auto pos = getPosition();
    int oldY = pos.y;

    pos.y += 25;
    if (oldY < 0) {
        pos.x -= 2.5;
    } else {
        pos.x += 2.5;
    }
    setPosition(pos);
}

void LevelButton::MoveDown() {
    auto pos = getPosition();

    int oldY = pos.y;
    pos.y -= 25;
    if (oldY <= 0) {
        pos.x += 2.5;
    } else {
        pos.x -= 2.5;
    }
    setPosition(pos);
}
