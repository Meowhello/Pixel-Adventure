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
    void ChangeBlueBtn();
    void ChangeWhiteBtn();
    bool getIsCenter();

    void Translate(float delta);
private:
    std::shared_ptr<Core::Drawable> blueBtn = m_Drawable;
    std::shared_ptr<Core::Drawable> whiteBtn = std::make_shared<Util::Image>(whiteBtnPath);;
    bool isBtnWhite = false;
};

#endif //LEVELBUTTON_H

