#include "App.hpp"

#include "Core/Context.hpp"

int main(int, char**) {
    auto context = Core::Context::GetInstance();
    App app;
    // std::vector<std::shared_ptr<Fruit>> fruits;
    //
    // fruits.emplace_back(std::make_shared<Fruit>());
    //
    // for (const auto &fruit : fruits) {
    //     auto position = fruit->m_Transform.translation;
    // }
    while (!context->GetExit()) {
        switch (app.GetCurrentState()) {
            case App::State::START:
                app.Start();
                break;

            case App::State::UPDATE:
                app.Update();
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
