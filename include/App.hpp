#ifndef APP_HPP
#define APP_HPP

#include "Util/Renderer.hpp"
#include "Level.h"
#include "MainMenu.h"
#include "SelectLevel.h"

class App {
public:
    enum class State {
        START,
        MENU,
        SELECT_LEVEL,
        GAME_INITIAL,
        GAME_UPDATE,
        FINISH,
        PAUSE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();
    void MenuUpdate();
    void SelectLevelUpdate();
    void GameInitial();
    void GameUpdate();
    void Pasue();
    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();

    State m_CurrentState = State::START;
    Util::Renderer m_Root;
    std::shared_ptr<Level> _level;
    std::shared_ptr<Level> _currentLevel;

    std::shared_ptr<MainMenu> _mainMenu;
    std::shared_ptr<SelectLevel> _selectLevel;
};

#endif
