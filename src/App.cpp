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

    _bgm = std::make_shared<Util::BGM>("../Resources/music/Haruhikage - CRYCHIC.mp3");
    _bgm->Play();
    _sfx = std::make_shared<Util::SFX>("../Resources/music/normal-hitclap.wav");

    m_Root.RemoveChild(m_Catcher);

    m_Catcher = (std::make_shared<Catcher>());
    m_Root.AddChild(m_Catcher);//人物加入m_Root一起畫出來
    m_Background = (std::make_shared<Background>(Background::level::level_1));
    m_Root.AddChild(m_Background);//畫背景


    //scoreboard test code
    m_Root.AddChild(_scoreboard);
    m_Root.AddChild(_combo);
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

    // m_Root.AddChild(m_Catcher); //人物加入m_Root一起畫出來
    // catcher.show();
    if(Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
        m_Catcher->moveLeft();
    }
    if(Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
        m_Catcher->moveRight();
    }

    // std::vector<std::shared_ptr<Fruit>> fruits; //存放很多水果
    // for (int i = 0; i < 10; i++) {
    static auto lastDrop = Util::Time::GetElapsedTimeMs();

    LOG_DEBUG("{}", Util::Time::GetElapsedTimeMs());
    if(Util::Time::GetElapsedTimeMs() - lastDrop > 1000) { //一秒一個水果
        lastDrop = Util::Time::GetElapsedTimeMs();
        auto rand_num = rand()%6; //隨機水果
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

    for (const auto &fruit : fruits) { //水果++
        m_Root.AddChild(fruit);
    }

    static auto combo=0;
    for (int i = 0; i < fruits.size(); i++) { //一起控制所有的水果
        auto position = fruits[i]->m_Transform.translation; //控制 x 和 y
        auto catcherpos=m_Catcher->m_Transform.translation; //人物
        position.y -= 10 ; // 水果下墜
        fruits[i]->m_Transform.translation.y = position.y;
        std::cout<<"combo: "<<combo<<std::endl;
        if(abs(position.x-catcherpos.x)<100 && position.y<=-130&& position.y>-220) { //判斷水果觸碰
            fruits[i]->SetVisible(false);
            fruits.erase(fruits.begin());
            _combo->AddCombo(1);
            _sfx->Play();
        }
        else if(position.y<-400) { //判斷水果落地
            fruits[i]->SetVisible(false);
            fruits.erase(fruits.begin());
            _combo->ResetCombo();
        }
    }

    //scoreboard test code
    _scoreboard->UpdateScoreboard();
    _scoreboard->Show();
    _scoreboard->AddScore(1);

    _combo->UpdateCombo();
    _combo->Show();

    //character control logic
    if(Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
        m_Catcher->moveLeft();
    }
    if(Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
        m_Catcher->moveRight();
    }

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
    glm::vec2 mouseposition = Util::Input::GetCursorPosition();
    _bgm->Pause();
    _scoreboard->SetVisible(false);
    SetPauseButton(true);
    if(Util::Input::IsKeyDown(Util::Keycode::ESCAPE) || _continueButton->IsButtonClick(mouseposition)) {
        SetPauseButton(false);
        _scoreboard->SetVisible(true);
        m_CurrentState = State::UPDATE;
    }

    if(_retryButton->IsButtonClick(mouseposition)) {
        SetPauseButton(false);
        _scoreboard->SetVisible(true);
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

void App::SetPauseButton(bool state) {
    _continueButton->SetVisible(state);
    _retryButton->SetVisible(state);
    _backButton->SetVisible(state);
}
