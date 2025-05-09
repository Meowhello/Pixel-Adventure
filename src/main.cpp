#include "App.hpp"

#include "Core/Context.hpp"

int main(int, char**) {
    auto context = Core::Context::GetInstance();
    App app;

    while (!context->GetExit()) {
        switch (app.GetCurrentState()) {
            case App::State::START:
                app.Start();
                break;

            case App::State::MENU:
                app.MenuUpdate();
                break;

            case App::State::SELECT_LEVEL:
                app.SelectLevelUpdate();
            break;

            case App::State::GAME_INITIAL:
                app.GameInitial();
            break;

            case App::State::GAME_UPDATE:
                app.GameUpdate();
            break;

            case App::State::FINISH:
                app.GameFinish();
            break;

            case App::State::PAUSE:
                app.Pasue();
                break;

            case App::State::END:
                app.End();
                context->SetExit(true);
                break;
        }
        context->Update();
    }
    return 0;
}
