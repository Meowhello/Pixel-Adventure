#include "App.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <typeinfo>
#include "Util/Time.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");
    _mainMenu = std::make_shared<MainMenu>();

    _level = std::make_shared<Level>("Haruhikage", Level::Difficulty::Easy, "../Resources/music/Haruhikage_CRYCHIC.mp3", "../Resources/music/normal-hitclap.wav", "");

    m_CurrentState = State::MENU_UPDATE;
}

void App::MenuUpdate() {
    //TODO: do your things here and delete this line <3
    m_Root.AddChild(_mainMenu);
    int signal = _mainMenu->Update();

    if( signal == 1) {
        m_Root.RemoveChild(_mainMenu);
        m_CurrentState = State::GAME_UPDATE;
    }

    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */
    if (Util::Input::IfExit() || signal == 2) {
        m_CurrentState = State::END;
    }
    m_Root.Update();
}

void App::GameUpdate() {
    m_Root.RemoveChild(_level);
    m_Root.AddChild(_level);

    _level->Update();

    if(Util::Input::IsKeyDown(Util::Keycode::ESCAPE)) {
        m_CurrentState = State::PAUSE;
    }

    if (Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    m_Root.Update();
}


void App::Pasue() {
    int signal = _level->Pause();
    if(Util::Input::IsKeyDown(Util::Keycode::ESCAPE) || signal == 1) {
        m_CurrentState = State::MENU_UPDATE;
    }

    if( signal == 2) {
        m_CurrentState = State::START;
    }

    if (Util::Input::IfExit()) {
        m_CurrentState = State::END;
        }
    m_Root.Update();
}


void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}