//
// Created by x3052 on 2025/4/11.
//

#ifndef LEVEL_H
#define LEVEL_H

#include "pch.hpp" // IWYU pragma: export
#include "Catcher.h"
#include "Fruit.h"
#include "Scoreboard.h"
#include "Util/Renderer.hpp"
#include "Background.h"
#include "Combo.h"
#include "HP.h"
#include "Button/ContinueButton.h"
#include "Button/RetryButton.h"
#include "Button/BackButton.h"
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

    void Initial();
    void Update();
    int Pause();
    void End();
    void HandleInput();
    void UpdateFruitSpawning();
    void UpdateFruits();
    void ResumeBGM();
    void ClearState();
private:
    void SetPauseButton(bool);
    std::string _name;
    Difficulty _difficulty;

    std::shared_ptr<Util::BGM> _bgm;
    std::shared_ptr<Util::SFX> _sfx;

    std::shared_ptr<Catcher> m_Catcher;
    std::shared_ptr<HP> _hp;
    std::vector<std::shared_ptr<Fruit>> fruits;
    std::shared_ptr<Background> m_Background;
    std::shared_ptr<Scoreboard> _scoreboard;
    std::shared_ptr<Combo> _combo;
    std::shared_ptr<ContinueButton> _continueButton;
    std::shared_ptr<RetryButton> _retryButton;
    std::shared_ptr<BackButton> _backButton;
};

#endif //LEVEL_H
