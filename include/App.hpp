#ifndef APP_HPP
#define APP_HPP

#include "Util/Renderer.hpp"
#include "Level.h"
#include "LevelManager.h"

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

private:
    void ValidTask();

    State m_CurrentState = State::START;
    Util::Renderer m_Root;
    std::shared_ptr<Level> _level;
    std::shared_ptr<LevelManager> _levelManager;
    std::shared_ptr<Level> _currentLevel;
};

#endif
