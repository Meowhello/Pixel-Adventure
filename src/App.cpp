#include "App.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <typeinfo>
#include "Catcher.h"
#include "Util/Time.hpp"
#include "Fruit.h"
#include "Scoreboard.h"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");

    m_Root.RemoveChild(_level);
    _level = std::make_shared<Level>("Haruhikage", Level::Difficulty::Easy, RESOURCE_DIR "music/Haruhikage - CRYCHIC.mp3", RESOURCE_DIR "music/normal-hitclap.wav", "");
    m_Root.AddChild(_level);

    m_CurrentState = State::UPDATE;
}

void App::Update() {
    
    //TODO: do your things here and delete this line <3

    _level->Update();

    if(Util::Input::IsKeyDown(Util::Keycode::ESCAPE)) {
        m_CurrentState = State::PAUSE;
    }

    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */
    if (Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    m_Root.Update();
}

void App::Pasue() {
    int signal = _level->Pause();
    if(Util::Input::IsKeyDown(Util::Keycode::ESCAPE) || signal == 1) {
        m_CurrentState = State::UPDATE;
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