//
// Created by x3052 on 2025/4/15.
//

#ifndef PLAYBUTTON_H
#define PLAYBUTTON_H
#include "Button.h"

class PlayButton : public Button {
public:
    PlayButton()
    : Button("../Resources/Image/main_page/play.png", 200, 75, 100, 380) {
        SetZIndex(0);
        m_Transform.scale={0.6,0.6};
    }
    ~PlayButton() = default;
};

#endif //PLAYBUTTON_H
