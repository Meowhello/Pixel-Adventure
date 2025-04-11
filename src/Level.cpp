//
// Created by x3052 on 2025/4/11.
//
#include "Level.h"

#include <utility>

#include "Util/Input.hpp"
#include "Util/Time.hpp"

Level::Level(std::string name, Difficulty difficulty ,std::string bgmPath, std::string sfxPath, std::string backgroundPath): _name(std::move(name)), _difficulty(difficulty) {
    _bgm = std::make_shared<Util::BGM>(bgmPath);
    _bgm->Play();
    _sfx = std::make_shared<Util::SFX>(sfxPath);

    m_Catcher = (std::make_shared<Catcher>());
    AddChild(m_Catcher);
    m_Background = (std::make_shared<Background>(Background::level::level_1));
    AddChild(m_Background);

    AddChild(_scoreboard);
    _scoreboard->SetScore(0);
    AddChild(_combo);
    AddChild(_continueButton);
    _continueButton->SetVisible(false);
    AddChild(_retryButton);
    _retryButton->SetVisible(false);
    AddChild(_backButton);
    _backButton->SetVisible(false);
}

void Level::Update() {

    if(Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
        m_Catcher->moveLeft();
    }
    if(Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
        m_Catcher->moveRight();
    }

    static auto lastDrop = Util::Time::GetElapsedTimeMs();

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
        AddChild(fruit);
    }

    static auto combo=0;
    for (int i = 0; i < fruits.size(); i++) { //一起控制所有的水果
        auto position = fruits[i]->m_Transform.translation; //控制 x 和 y
        auto catcherpos=m_Catcher->m_Transform.translation; //人物
        position.y -= 10 ; // 水果下墜
        fruits[i]->m_Transform.translation.y = position.y;

        if(abs(position.x-catcherpos.x)<100 && position.y<=-130&& position.y>-220) { //判斷水果觸碰
            _scoreboard->AddScore(100);
            fruits[i]->SetVisible(false);
            RemoveChild(fruits.front());//拿掉最陣列最前面(首先掉下的)水果
            fruits.erase(fruits.begin());//拿掉最陣列最前面(首先掉下的)水果
            _combo->AddCombo(1);
            if(_combo->GetCombo()/5>=1) {
                _scoreboard->AddScore(53*(_combo->GetCombo()/5));
            }
            _sfx->Play();
        }
        else if(position.y<-400) { //判斷水果落地
            fruits[i]->SetVisible(false);
            RemoveChild(fruits.front());
            fruits.erase(fruits.begin());
            _combo->ResetCombo();
        }
    }

    _scoreboard->UpdateScoreboard();
    _scoreboard->Show();

    _combo->UpdateCombo();
    _combo->Show();
}

int Level::Pause() {
    glm::vec2 mouseposition = Util::Input::GetCursorPosition();
    _bgm->Pause();
    _scoreboard->SetVisible(false);
    SetPauseButton(true);
    if(Util::Input::IsKeyDown(Util::Keycode::ESCAPE) || _continueButton->IsButtonClick(mouseposition)) {
        SetPauseButton(false);
        _scoreboard->SetVisible(true);
        return 1;
    }

    if(_retryButton->IsButtonClick(mouseposition)) {
        SetPauseButton(false);
        _combo->ResetCombo();
        _scoreboard->ResetScore();
        _scoreboard->SetVisible(true);
        return 2;
    }

    if(_backButton->IsButtonClick(mouseposition)) {
        SetPauseButton(false);
        return 3;
    }

    return 0;
}

void Level::SetPauseButton(bool state) {
    _continueButton->SetVisible(state);
    _retryButton->SetVisible(state);
    _backButton->SetVisible(state);
}