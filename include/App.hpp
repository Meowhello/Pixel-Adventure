#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export
#include "Catcher.h"
#include "Fruit.h"
#include "Scoreboard.h"
#include "Scorenumber.h"
#include "Util/Renderer.hpp"


class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();
    Catcher catcher;

    State m_CurrentState = State::START;
    Util::Renderer m_Root;
    std::shared_ptr<Fruit> m_Fruit;
    std::vector<std::shared_ptr<Fruit>> fruits; //存放很多水果

    std::shared_ptr<Scoreboard> scoreboard = std::make_shared<Scoreboard>();
};

#endif
