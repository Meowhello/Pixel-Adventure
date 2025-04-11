//
// Created by x3052 on 2025/4/11.
//

#ifndef LEVEL_H
#define LEVEL_H

#include "BackButton.h"
#include "pch.hpp" // IWYU pragma: export
#include "Catcher.h"
#include "ContinueButton.h"
#include "Fruit.h"
#include "RetryButton.h"
#include "Scoreboard.h"
#include "Util/Renderer.hpp"
#include "Background.h"
#include "Combo.h"
#include "Util/BGM.hpp"
#include "Util/SFX.hpp"

class Level: public Util::GameObject {
public:
    enum class Difficulty {
        Easy,
        Middle,
        Hard
    };
    Level(std::string, Difficulty, std::string, std::string, std::string);
    ~Level() = default;

    void Update();
    int Pause();
    void End();
private:
    void SetPauseButton(bool);
    std::string _name;
    Difficulty _difficulty;

    std::shared_ptr<Util::BGM> _bgm;
    std::shared_ptr<Util::SFX> _sfx;

    std::shared_ptr<Catcher> m_Catcher;
    std::shared_ptr<Fruit> m_Fruit;
    std::vector<std::shared_ptr<Fruit>> fruits;
    std::shared_ptr<Background> m_Background;

    std::shared_ptr<Scoreboard> _scoreboard = std::make_shared<Scoreboard>();
    std::shared_ptr<ContinueButton> _continueButton = std::make_shared<ContinueButton>();
    std::shared_ptr<RetryButton> _retryButton = std::make_shared<RetryButton>();
    std::shared_ptr<BackButton> _backButton = std::make_shared<BackButton>();
    std::shared_ptr<Combo> _combo = std::make_shared<Combo>();
};

#endif //LEVEL_H
