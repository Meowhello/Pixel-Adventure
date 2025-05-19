#include "App.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <typeinfo>

#include "AudioUtil.h"
#include "Util/Time.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");
    _mainMenu = std::make_shared<MainMenu>();
    _selectLevel = std::make_shared<SelectLevel>();
    m_CurrentState = State::MENU;

    m_Root.AddChild(_mainMenu);
}

void App::MenuUpdate() {
    int signal = _mainMenu->Update();
    static auto lastime=Util::Time::GetElapsedTimeMs();
    if(Util::Time::GetElapsedTimeMs()-lastime>1000) {
        m_Root.RemoveChild(_mainMenu);
        lastime=Util::Time::GetElapsedTimeMs();
        _mainMenu = std::make_shared<MainMenu>();
        m_Root.AddChild(_mainMenu);
    }

    if( signal == 1) {
        m_Root.RemoveChild(_mainMenu);
        m_Root.AddChild(_selectLevel);
        m_CurrentState = State::SELECT_LEVEL;
    }

    if (Util::Input::IfExit() || signal == 2) {
        m_CurrentState = State::END;
    }
    m_Root.Update();
}

void App::SelectLevelUpdate() {
    _level = _selectLevel->Updtate();

    if(_level) {
        m_Root.RemoveChild(_selectLevel);
        m_CurrentState = State::GAME_INITIAL;
    }

    if (Util::Input::IsKeyDown(Util::Keycode::ESCAPE)) {
        m_Root.RemoveChild(_selectLevel);
        m_Root.AddChild(_mainMenu);
        m_CurrentState = State::MENU;
    }

    if (Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    m_Root.Update();
}


void App::GameInitial() {
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

    if(_level->Gethp()<=0) {
        m_CurrentState = State::GAME_OVER;
    }

    if(Util::Time::GetElapsedTimeMs() > _level->GetStartTime()+30) {
        if(BgmHasFinished()) {
            m_CurrentState = State::FINISH;
            m_Root.RemoveChild(_level);
            _finish = std::make_shared<Finish>(_level->GetBgPaht());
            m_Root.AddChild(_finish);
        }
    }

    m_Root.Update();
}

void App::GameOver() {
    int signal = _level->GameOver();

    if( signal == 1) {
        m_Root.RemoveChild(_level);
        _level->ClearState();
        m_CurrentState = State::GAME_INITIAL;
    }

    if(Util::Input::IsKeyDown(Util::Keycode::ESCAPE) || signal == 2) {
        m_Root.RemoveChild(_level);
        m_Root.AddChild(_selectLevel);
        m_CurrentState = State::SELECT_LEVEL;
    }

    if (Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    m_Root.Update();
}

void App::GameFinish() {
    Finish::ResultData result_data = _level->Finish();
    _finish->SetResult(result_data);
    int signal = _finish->IsButtonClick();


    if (Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }

    if(signal == 1) {
        m_Root.RemoveChild(_finish);
        m_Root.RemoveChild(_level);
        _level->ClearState();
        m_CurrentState = State::GAME_INITIAL;
    }

    if(Util::Input::IsKeyDown(Util::Keycode::ESCAPE) ||  signal == 2) {
        m_Root.RemoveChild(_finish);
        m_Root.RemoveChild(_level);
        m_Root.AddChild(_selectLevel);
        m_CurrentState = State::SELECT_LEVEL;
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
        m_Root.RemoveChild(_level);
        _level->ClearState();
        m_CurrentState = State::GAME_INITIAL;
    }

    if(signal == 3) {
        m_Root.RemoveChild(_level);
        m_Root.AddChild(_selectLevel);
        m_CurrentState = State::SELECT_LEVEL;
    }

    if (Util::Input::IfExit()) {
        m_CurrentState = State::END;
        }
    m_Root.Update();
}


void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}