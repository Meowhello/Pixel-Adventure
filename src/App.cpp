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
    _selectLevel = std::make_shared<SelectLevel>();


    m_CurrentState = State::MENU;
}

void App::MenuUpdate() {
    //TODO: do your things here and delete this line <3
    m_Root.AddChild(_mainMenu);
    int signal = _mainMenu->Update();

    if( signal == 1) {
        m_Root.RemoveChild(_mainMenu);
        //m_Root.AddChild(_selectLevel);
        m_CurrentState = State::GAME_INITIAL;
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

void App::SelectLevelUpdate() {
    _selectLevel->Updtate();

    if (Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    m_Root.Update();
    //m_CurrentState = State::GAME_INITIAL;
}


void App::GameInitial() {
    m_Root.RemoveChild(_level);
    _level = std::make_shared<Level>("Haruhikage", Level::Difficulty::Easy, "../Resources/music/Haruhikage_CRYCHIC.mp3", "../Resources/music/normal-hitclap.wav", "");
    _level->Initial();
    m_Root.AddChild(_level);
    m_CurrentState = State::GAME_UPDATE;
}


void App::GameUpdate() {

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
        _level->ResumeBGM();
        m_CurrentState = State::GAME_UPDATE;
    }

    if( signal == 2) {
        m_CurrentState = State::GAME_INITIAL;
    }

    if(signal == 3) {
        m_CurrentState = State::MENU;
    }

    if (Util::Input::IfExit()) {
        m_CurrentState = State::END;
        }
    m_Root.Update();
}


void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}