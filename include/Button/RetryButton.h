//
// Created by x3052 on 2025/4/4.
//

#ifndef REPLAYBUTTON_H
#define REPLAYBUTTON_H
#include "Button.h"

class RetryButton : public Button {
public:
    RetryButton(int x, int y)
    : Button("../Resources/Image/game_sources/pause-retry.png", x, y, 100, 380) {
        SetZIndex(5);
    }
    ~RetryButton() = default;
};

#endif //REPLAYBUTTON_H
