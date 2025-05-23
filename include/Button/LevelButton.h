//
// Created by x3052 on 2025/4/16.
//

#ifndef LEVELBUTTON_H
#define LEVELBUTTON_H
#include <string>

#include "Button.h"

class LevelButton : public Button {
public:
    LevelButton(std::string imagePath, int, int);
    ~LevelButton() = default;

    void MoveUp();
    void MoveDown();

    void Translate(float delta);
};

#endif //LEVELBUTTON_H

