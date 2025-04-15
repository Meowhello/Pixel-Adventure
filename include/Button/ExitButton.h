//
// Created by x3052 on 2025/4/15.
//

#ifndef EXITBUTTON_H
#define EXITBUTTON_H
#include "Button.h"

class ExitButton : public Button {
public:
    ExitButton()
    : Button("../Resources/Image/main_page/exit.png", 200, -75, 100, 380) {
        SetZIndex(0);
    }
    ~ExitButton() = default;
};

#endif //EXITBUTTON_H
