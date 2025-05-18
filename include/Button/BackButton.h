//
// Created by x3052 on 2025/4/4.
//

#ifndef BACKBUTTON_H
#define BACKBUTTON_H
#include "Button.h"

class BackButton: public Button {
public:
    BackButton(int x, int y)
    : Button("../Resources/Image/game_sources/pause-back.png", x, y, 100, 380) {
        SetZIndex(5);
    }
    ~BackButton() = default;
};

#endif //BACKBUTTON_H
