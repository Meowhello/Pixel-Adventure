//
// Created by x3052 on 2025/4/15.
//

#ifndef MAINMENU_H
#define MAINMENU_H
#include <future>

#include "Background.h"
#include "Button/ExitButton.h"
#include "Button/PlayButton.h"
#include "Util/GameObject.hpp"

class MainMenu : public Util::GameObject{
public:
    MainMenu();
    ~MainMenu() = default;

    int Update();
private:
    std::shared_ptr<PlayButton> _playButton = std::make_shared<PlayButton>();
    std::shared_ptr<ExitButton> _exitButton = std::make_shared<ExitButton>();
    std::shared_ptr<Background> _background = std::make_shared<Background>(Background::level::MainMenu);
};

#endif //MAINMENU_H
