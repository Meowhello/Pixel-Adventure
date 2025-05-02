//
// Created by x3052 on 2025/4/11.
//
#include "Level.h"

#include <iostream>
#include <utility>

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
    _background      = std::make_shared<Background>(Background::level::level_1);
    _hp              = std::make_shared<HP>();
    _scoreboard      = std::make_shared<Scoreboard>();
    _combo           = std::make_shared<Combo>();
    _continueButton  = std::make_shared<ContinueButton>();
    _retryButton     = std::make_shared<RetryButton>();
    _backButton      = std::make_shared<BackButton>();
}

void Level::Initial() {
    OsuParser::ParseFile(_comfigPath, _levelData);
    _approachMs = _levelData.approachMs;
    // std::cout << "=== LevelData dump ===\n"
    //          << "object count: " << _levelData.objects.size() << "\n\n";
    //
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

    // 假設 PTSD 設定：世界 X ∈ [-256,+256]、Y ∈ [-144,+144]
    _scaleX = 512.f / 512.f;  // → 若需要拉伸改這裡
    _scaleY = 288.f / 384.f;
    _hp->restart();

    _scoreboard->SetScore(0);
    _continueButton->SetVisible(false);
    _retryButton->SetVisible(false);
    _backButton->SetVisible(false);

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
    _bgm->Resume();
    _combo->SetVisible(false);
    _scoreboard->SetVisible(false);
    _hp->SetVisible(false);
    _catcher->SetVisible(false);
    m_Drawable = std::make_shared<Util::Image>((RESOURCE_DIR "/Image/game_sources/end_page.png"));
}


void Level::HandleInput() {
    if (Util::Input::IsKeyPressed(Util::Keycode::LEFT))
        _catcher->moveLeft();
    if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT))
        _catcher->moveRight();
}


void Level::UpdateFruitSpawning() {
    if (_nextIndex >= _levelData.objects.size()) return;

    int64_t now     = Util::Time::GetElapsedTimeMs();
    _runTimeMs      = now - _startTimeMs - _totalPauseTimeMs;

    while (_nextIndex < _levelData.objects.size() &&
           _runTimeMs >= _levelData.objects[_nextIndex].hitTime - _approachMs)
    {
        const auto& obj = _levelData.objects[_nextIndex];

        auto fruit = std::make_shared<Fruit>(Fruit::FruitType::Apple);

        // 解析 X：-256 ~ +256
        int worldX = (obj.x - 256);
        fruit->m_Transform.translation = { worldX, _spawnStartY };

        fruit->spawnTime = obj.hitTime - _approachMs;   // ★ 關鍵一行
        fruit->hitTime   = obj.hitTime;                 // (若之後要用到)

        fruits.push_back(fruit);
        AddChild(fruit);
        ++_nextIndex;
    }
}

void Level::UpdateFruits() {

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

        // 超出底線
        if (pos.y < -400.f) {
            fruit->SetVisible(false);
            RemoveChild(fruit);
            it = fruits.erase(it);
            _combo->ResetCombo();
            _hp->hpdrain(10);
            continue;
        }

        ++it;
    }
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
    //_hp->Reset();

    // Stop BGM
    _bgm->Pause();
}

// void Level::Update() {
//
//     HandleInput();
//
//     static auto lastDrop = Util::Time::GetElapsedTimeMs();
//
//     if(Util::Time::GetElapsedTimeMs() - lastDrop > 1000) { //一秒一個水果
//         lastDrop = Util::Time::GetElapsedTimeMs();
//         auto rand_num = rand()%6; //隨機水果
//         switch (rand_num) {
//             case 0:
//                 fruits.push_back(std::make_shared<Fruit>(Fruit::FruitType::Apple));
//             break;
//             case 1:
//                 fruits.push_back(std::make_shared<Fruit>(Fruit::FruitType::Bananas));
//             break;
//             case 2:
//                 fruits.push_back(std::make_shared<Fruit>(Fruit::FruitType::Drop));
//             break;
//             case 3:
//                 fruits.push_back(std::make_shared<Fruit>(Fruit::FruitType::Grapes));
//             break;
//             case 4:
//                 fruits.push_back(std::make_shared<Fruit>(Fruit::FruitType::Orange));
//             break;
//             case 5:
//                 fruits.push_back(std::make_shared<Fruit>(Fruit::FruitType::Pear));
//             break;
//         }
//     }
//
//     for (const auto &fruit : fruits) { //水果++
//         AddChild(fruit);
//     }
//
//     static auto combo=0;
//     for (int i = 0; i < fruits.size(); i++) { //一起控制所有的水果
//         auto position = fruits[i]->m_Transform.translation; //控制 x 和 y
//         auto catcherpos=_catcher->m_Transform.translation; //人物
//         position.y -= 10 ; // 水果下墜
//         fruits[i]->m_Transform.translation.y = position.y;
//
//         if(abs(position.x-catcherpos.x)<100 && position.y<=-130&& position.y>-220) { //判斷水果觸碰
//             _scoreboard->AddScore(100);
//             fruits[i]->SetVisible(false);
//             RemoveChild(fruits.front());//拿掉最陣列最前面(首先掉下的)水果
//             fruits.erase(fruits.begin());//拿掉最陣列最前面(首先掉下的)水果
//             _combo->AddCombo(1);
//             if(_combo->GetCombo()/5>=1) {
//                 _scoreboard->AddScore(53*(_combo->GetCombo()/5));
//             }
//             _sfx->Play();
//         }
//         else if(position.y<-400) { //判斷水果落地
//             fruits[i]->SetVisible(false);
//             RemoveChild(fruits.front());
//             fruits.erase(fruits.begin());
//             _combo->ResetCombo();
//         }
//     }
//
//     _scoreboard->UpdateScoreboard();
//     _scoreboard->Show();
//
//     _combo->UpdateCombo();
//     _combo->Show();
// }