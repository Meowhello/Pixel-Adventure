#ifndef APP_HPP
#define APP_HPP

#include "Util/Renderer.hpp"
#include "Level.h"
#include "LevelManager.h"
#include "MainMenu.h"

class App {
public:
    enum class State {
        START,
        MENU_UPDATE,
        GAME_UPDATE,
        PAUSE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();
    void MenuUpdate();
    void End(); // NOLINT(readability-convert-member-functions-to-static)
    void GameUpdate();
    void Pasue();

private:
    void ValidTask();

    State m_CurrentState = State::START;
    Util::Renderer m_Root;
    std::shared_ptr<Level> _level;
    std::shared_ptr<LevelManager> _levelManager;
    std::shared_ptr<Level> _currentLevel;

    std::shared_ptr<MainMenu> _mainMenu;
};

#endif
