//
// Created by x3052 on 2025/4/4.
//

#ifndef CONTINUEBUTTON_H
#define CONTINUEBUTTON_H
#include "Button.h"

class ContinueButton : public Button {
public:
    ContinueButton()
        : Button("../Resources/Image/game_sources/pause-continue.png", 0, 125, 100, 380) {
        SetZIndex(5);
    }
    ~ContinueButton() = default;
};


#endif //CONTINUEBUTTON_H