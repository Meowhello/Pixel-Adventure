#include "App.hpp"
#include <iostream>

#include "Catcher.h"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");
    m_CurrentState = State::UPDATE;
}

void App::Update() {
    
    //TODO: do your things here and delete this line <3
    catcher.show();

    if(Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
        catcher.moveLeft();
    }
    if(Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
        catcher.moveRight();
    }

    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
