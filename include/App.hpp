#ifndef APP_HPP
#define APP_HPP

#include "BackButton.h"
#include "pch.hpp" // IWYU pragma: export
#include "Catcher.h"
#include "ContinueButton.h"
#include "Fruit.h"
#include "RetryButton.h"
#include "Scoreboard.h"
#include "Util/Renderer.hpp"
#include "Background.h"

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
        GAMESTART,
        PAUSE
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();
    void Update();
    void End(); // NOLINT(readability-convert-member-functions-to-static)
    void GameStart();
    void Pasue();
    void SetPauseButton(bool);

private:
    void ValidTask();
    // Catcher catcher;


    State m_CurrentState = State::START;
    Util::Renderer m_Root;
    std::shared_ptr<Fruit> m_Fruit;
    std::shared_ptr<Catcher> m_Catcher;
    std::vector<std::shared_ptr<Fruit>> fruits; //存放很多水果
    std::shared_ptr<Background> m_Background;

    std::shared_ptr<Scoreboard> _scoreboard = std::make_shared<Scoreboard>();
    std::shared_ptr<ContinueButton> _continueButton = std::make_shared<ContinueButton>();
    std::shared_ptr<RetryButton> _retryButton = std::make_shared<RetryButton>();
    std::shared_ptr<BackButton> _backButton = std::make_shared<BackButton>();
};

#endif
