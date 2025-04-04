#include "App.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <typeinfo>
#include "Catcher.h"
#include "Util/Time.hpp"
#include "Fruit.h"
#include "Scoreboard.h"
#include "Scorenumber.h"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");
    // m_Fruit = std::make_shared<Fruit>(Fruit::FruitType::Apple);
    // m_Root.AddChild(m_Fruit);

    //scoreboard test code
    m_Root.AddChild(_scoreboard);
    m_Root.AddChild(_continueButton);
    _continueButton->SetVisible(false);
    m_Root.AddChild(_retryButton);
    _retryButton->SetVisible(false);
    m_Root.AddChild(_backButton);
    _backButton->SetVisible(false);


    m_CurrentState = State::UPDATE;
}

void App::Update() {
    
    //TODO: do your things here and delete this line <3

    // std::vector<std::shared_ptr<Fruit>> fruits; //存放很多水果
    // for (int i = 0; i < 10; i++) {
    static auto lastDrop = Util::Time::GetElapsedTimeMs();
    //LOG_DEBUG("{}", Util::Time::GetElapsedTimeMs());
    if(Util::Time::GetElapsedTimeMs() - lastDrop > 1000) {
        lastDrop = Util::Time::GetElapsedTimeMs();
        auto rand_num = rand()%6;
        switch (rand_num) {
            case 0:
                fruits.push_back(std::make_shared<Fruit>(Fruit::FruitType::Apple));
            break;
            case 1:
                fruits.push_back(std::make_shared<Fruit>(Fruit::FruitType::Bananas));
            break;
            case 2:
                fruits.push_back(std::make_shared<Fruit>(Fruit::FruitType::Drop));
            break;
            case 3:
                fruits.push_back(std::make_shared<Fruit>(Fruit::FruitType::Grapes));
            break;
            case 4:
                fruits.push_back(std::make_shared<Fruit>(Fruit::FruitType::Orange));
            break;
            case 5:
                fruits.push_back(std::make_shared<Fruit>(Fruit::FruitType::Pear));
            break;
        }
    }

    for (const auto &fruit : fruits) {
        m_Root.AddChild(fruit);
    }

    for (int i = 0; i < fruits.size(); i++) { //一起控制所有的水果
        auto position = fruits[i]->m_Transform.translation; //控制 x 和 y
        // std::cout <<"("<<position.x << "," << position.y <<")"<< std::endl;
        position.y -= 10 ;
        fruits[i]->m_Transform.translation.y = position.y;
        if(position.y<-200) {
            fruits[i]->SetVisible(false);
            fruits.erase(fruits.begin());
        }
    }

    //scoreboard test code
    _scoreboard->UpdateScoreboard();
    _scoreboard->Show();
    _scoreboard->AddScore(1);

    //character control logic
    catcher.show();
    if(Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
        catcher.moveLeft();
    }
    if(Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
        catcher.moveRight();
    }

    if(Util::Input::IsKeyDown(Util::Keycode::ESCAPE)) {
        m_CurrentState = State::PAUSE;
    }

    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */
    if (//Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
    m_Root.Update();
}

void App::Pasue() {
    glm::vec2 mouseposition = Util::Input::GetCursorPosition();
    bool isMouseInContinueBottom = false;
    _scoreboard->SetVisible(false);
    _continueButton->SetVisible(true);
    _retryButton->SetVisible(true);
    _backButton->SetVisible(true);
    if(Util::Input::IsKeyDown(Util::Keycode::ESCAPE)) {
        _continueButton->SetVisible(false);
        _retryButton->SetVisible(false);
        _backButton->SetVisible(false);
        _scoreboard->SetVisible(true);
        m_CurrentState = State::UPDATE;
    }

    if (Util::Input::IfExit()) {
        m_CurrentState = State::END;
        }
    m_Root.Update();
}


void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
