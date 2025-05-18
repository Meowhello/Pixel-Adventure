//
// Created by tfboy on 2025/5/9.
//
#include "Finish.h"

#include <iostream>

#include "Util/Image.hpp"
#include "Util/Input.hpp"

Finish::Finish(std::string path) {
    _scoreboard     = std::make_shared<Scoreboard>(-180, 180);
    _catchFruit     = std::make_shared<ResultInteger>(-360, 20);
    _unCatchFruit   = std::make_shared<ResultInteger>(-110, 20);
    _combo          = std::make_shared<ResultInteger>(-500, -180);
    _accuracy       = std::make_shared<ResultFloat>(-110, -180);
    _endPage        = std::make_shared<EndPage>();
    _retryButton    = std::make_shared<RetryButton>(430, -190);
    _backButton     = std::make_shared<BackButton>(430, -300);
    _ranking        = std::make_shared<Ranking>();

    AddChild(_scoreboard);
    AddChild(_catchFruit);
    AddChild(_unCatchFruit);
    AddChild(_combo);
    AddChild(_accuracy);
    AddChild(_endPage);
    AddChild(_retryButton);
    AddChild(_backButton);
    AddChild(_ranking);
    m_Drawable = std::make_shared<Util::Image>(path);
    m_Transform.scale = {0.6666667, 0.6666667};
    m_ZIndex=-5;
}

void Finish::SetResult(ResultData data) {
    _scoreboard->SetScore(data.score);
    _scoreboard->Show();
    _catchFruit->Show(data.catchFruits);
    _unCatchFruit->Show(data.unCatchFruits);
    _combo->Show(data.combo);
    _accuracy->Show(data.accuracy);
    _ranking->SetRanking(data.accuracy);
}

int Finish::IsButtonClick() {
    glm::vec2 mouseposition = Util::Input::GetCursorPosition();

    if(_retryButton->IsButtonClick(mouseposition)) {
        return 1;
    }

    if(_backButton->IsButtonClick(mouseposition)) {
        return 2;
    }

    return 0;
}

