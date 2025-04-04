//
// Created by x3052 on 2025/4/4.
//

#ifndef BACKBUTTON_H
#define BACKBUTTON_H
#include "Button.h"

class BackButton: public Button {
public:
    BackButton()
        : Button("../Resources/Image/game_sources/pause-back.png", 0, -125, 100, 380) {}
    ~BackButton() = default;
};

#endif //BACKBUTTON_H
