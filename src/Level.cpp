//
// Created by x3052 on 2025/4/11.
//
#include "Level.h"

#include <iostream>
#include <utility>

// #include "../PTSD/lib/googletest/googlemock/include/gmock/gmock-matchers.h"
#include "Util/Input.hpp"
#include "Util/Time.hpp"

Level::Level(std::string name, Difficulty difficulty,
            const std::string& bgmPath, const std::string& sfxPath,
            const std::string& backgroundPath, std::string  comfigPath)
    : _name(std::move(name)), _difficulty(difficulty),_comfigPath(std::move(comfigPath)) {
    _bgm             = std::make_shared<Util::BGM>(bgmPath);
    _sfx             = std::make_shared<Util::SFX>(sfxPath);
    _osuParser       = std::make_shared<OsuParser>();
    _catcher         = std::make_shared<Catcher>();
    _background      = std::make_shared<Background>(backgroundPath);
    _hp              = std::make_shared<HP>();
    _scoreboard      = std::make_shared<Scoreboard>();
    _combo           = std::make_shared<Combo>();
    _continueButton  = std::make_shared<ContinueButton>();
    _retryButton     = std::make_shared<RetryButton>();
    _backButton      = std::make_shared<BackButton>();
}

void Level::Initial() {
    _levelData.objects.clear();
    OsuParser::ParseFile(_comfigPath, _levelData);
    _approachMs = _levelData.approachMs;
    std::cout << "=== LevelData dump ===\n"
             << "object count: " << _levelData.objects.size() << "\n\n";

    // for (std::size_t i = 0; i <  _levelData.objects.size(); ++i) {
    //     const auto& o = _levelData.objects[i];
    //     std::cout << "#" << i
    //               << "  x=" << o.x
    //               << "  y=" << o.y
    //               << "  hitTime=" << o.hitTime << " ms\n";
    // }
    std::sort(_levelData.objects.begin(), _levelData.objects.end(),
              [](auto& a, auto& b){ return a.hitTime < b.hitTime; });

    int64_t now = Util::Time::GetElapsedTimeMs();
    _startTimeMs = now + _approachMs;

    _scaleX = 640.f / 512.f;  // → 若需要拉伸改這裡
    _scaleY = 288.f / 384.f;
    _hp->restart();

    _scoreboard->SetScore(0);
    _continueButton->SetVisible(false);
    _retryButton->SetVisible(false);
    _backButton->SetVisible(false);

    _background->m_Transform.scale = {0.6666667, 0.6666667};

    AddChild(_catcher);
    AddChild(_background);
    AddChild(_hp);
    AddChild(_scoreboard);
    AddChild(_combo);
    AddChild(_continueButton);
    AddChild(_retryButton);
    AddChild(_backButton);

}

void Level::Update() {
    if(!_isBgmPlay)
        if(Util::Time::GetElapsedTimeMs() >= _startTimeMs) {
            _bgm->Play();
            _isBgmPlay = true;
        }
    HandleInput();
    UpdateFruitSpawning();
    UpdateFruits();
    _scoreboard->UpdateScoreboard();
    _scoreboard->Show();
    _combo->UpdateCombo();
    _combo->Show();
}


int Level::Pause() {
    if (_pauseStartTimeMs == 0.0f) {
        _pauseStartTimeMs = Util::Time::GetElapsedTimeMs();
    }
    glm::vec2 mouseposition = Util::Input::GetCursorPosition();
    _bgm->Pause();
    SetPauseButton(true);
    if(Util::Input::IsKeyDown(Util::Keycode::ESCAPE) || _continueButton->IsButtonClick(mouseposition)) {
        SetPauseButton(false);
        _totalPauseTimeMs += Util::Time::GetElapsedTimeMs() - _pauseStartTimeMs;
        _pauseStartTimeMs = 0;
        return 1;
    }

    if(_retryButton->IsButtonClick(mouseposition)) {
        SetPauseButton(false);
        _combo->ResetCombo();
        _scoreboard->ResetScore();
        return 2;
    }

    if(_backButton->IsButtonClick(mouseposition)) {
        SetPauseButton(false);
        return 3;
    }

    return 0;
}

void Level::Finish() {
    _bgm->Pause();
    _combo->SetVisible(false);
    _scoreboard->SetVisible(false);
    _hp->SetVisible(false);
    _catcher->SetVisible(false);
    for (auto& fruit : fruits) {
        RemoveChild(fruit);
    }
    fruits.clear();
}


void Level::HandleInput() {
    if (Util::Input::IsKeyPressed(Util::Keycode::LEFT))
        _catcher->MoveLeft();
    if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT))
        _catcher->MoveRight();
}


void Level::UpdateFruitSpawning() {
    if (_nextIndex >= _levelData.objects.size()) return;

    int64_t now     = Util::Time::GetElapsedTimeMs();
    _runTimeMs      = now - _startTimeMs - _totalPauseTimeMs;

    while (_nextIndex < _levelData.objects.size() &&
           _runTimeMs >= _levelData.objects[_nextIndex].hitTime - _approachMs)
    {
        const auto& obj = _levelData.objects[_nextIndex];

        Fruit::FruitType fruitType;
        auto rand_num = rand()%5; //隨機水果
        switch (rand_num) {
            case 0:
                fruitType = Fruit::FruitType::Apple;
            break;
            case 1:
                fruitType = Fruit::FruitType::Bananas;
            break;
            case 2:
                fruitType = Fruit::FruitType::Pear;
            break;
            case 3:
                fruitType = Fruit::FruitType::Grapes;
            break;
            case 4:
                fruitType = Fruit::FruitType::Orange;
            break;
        }

        auto fruit = std::make_shared<Fruit>(fruitType);

        // 解析 X：-256 ~ +256
        int worldX = (obj.x - 256) * _scaleX;
        fruit->m_Transform.translation = { worldX, _spawnStartY };

        fruit->spawnTime = obj.hitTime - _approachMs;   // ★ 關鍵一行
        fruit->hitTime   = obj.hitTime;                 // (若之後要用到)

        fruits.push_back(fruit);
        AddChild(fruit);
        ++_nextIndex;
    }
}

void Level::UpdateFruits() {
            std::cout<<"HP:"<<_hp->Gethp()<<std::endl;

    auto now = Util::Time::GetElapsedTimeMs();
    for (auto it = fruits.begin(); it != fruits.end(); ) {

        auto& fruit = *it;

        float elapsed   = float(_runTimeMs - fruit->spawnTime);
        float duration  = float(fruit->hitTime - fruit->spawnTime);
        float progress  = elapsed / duration;

        float dropDist = _spawnStartY + 100.f;
        float y = _spawnStartY - dropDist * progress;

        fruit->m_Transform.translation.y = y;

        // 判定區間 (依你原本邏輯調整)
        auto pos     = fruit->m_Transform.translation;
        auto catcher = _catcher->m_Transform.translation;

        bool caught = std::abs(pos.x - catcher.x) < 100.f &&
                      std::abs(pos.y + 130.f)      < 30.f;

        if (caught) {
            _scoreboard->AddScore(100);
            fruit->SetVisible(false);
            RemoveChild(fruit);
            it = fruits.erase(it);
            _combo->AddCombo(1);
            _sfx->Play();
            std::cout<<"hitTime: "<<_runTimeMs<<"ms"<< std::endl;
            continue;
        }
        std::cout<<"level "<<_levelData.hpDrainRate<<std::endl;
        std::cout<<"hp "<<_hp->Gethp()<<std::endl;
        // 超出底線
        if (pos.y < -400.f) {
            fruit->SetVisible(false);
            RemoveChild(fruit);
            it = fruits.erase(it);
            _combo->ResetCombo();
            _hp->hpdrain(_levelData.hpDrainRate);
            continue;
        }

        ++it;
    }
}

float Level::Gethp() {
    return _hp->Gethp();
}


void Level::SetPauseButton(bool state) {
    _continueButton->SetVisible(state);
    _retryButton->SetVisible(state);
    _backButton->SetVisible(state);
}

void Level::ResumeBGM() {
    _bgm->Resume();
}

void Level::ClearState() {
    // Remove and clear all fruits
    for (auto& fruit : fruits) {
        RemoveChild(fruit);
    }
    fruits.clear();

    // Reset indices and timers
    _nextIndex = 0;
    _runTimeMs = 0;
    _pauseStartTimeMs = 0;
    _totalPauseTimeMs = 0;
    _isBgmPlay = false;

    // Reset UI and player state
    _scoreboard->ResetScore();
    _combo->ResetCombo();
    _catcher->ResetPos();

    // Stop BGM
    _bgm->Pause();
}