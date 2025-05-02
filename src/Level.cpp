//
// Created by x3052 on 2025/4/11.
//
#include "Level.h"

#include <iostream>
#include <utility>

#include "Util/Input.hpp"
#include "Util/Time.hpp"

Level::Level(std::string name, Difficulty difficulty ,std::string bgmPath, std::string sfxPath, std::string backgroundPath, std::string comfigPath): _name(std::move(name)), _difficulty(difficulty) {
    _bgm = std::make_shared<Util::BGM>(bgmPath);
    _sfx = std::make_shared<Util::SFX>(sfxPath);
    _osuParser = std::make_shared<OsuParser>();
    _catcher = std::make_shared<Catcher>();
    _background = std::make_shared<Background>(Background::level::level_1);
    _hp = std::make_shared<HP>();
    _scoreboard = std::make_shared<Scoreboard>();
    _combo = std::make_shared<Combo>();
    _continueButton = std::make_shared<ContinueButton>();
    _retryButton = std::make_shared<RetryButton>();
    _backButton = std::make_shared<BackButton>();
}

void Level::Initial() {
    auto music=Music::Haruhikage;
    switch (music) {
        case Music::Haruhikage:
            OsuParser::ParseFile("../Resources/music/CRYCHIC - Haruhikage (TV Size) (lkx_Shore) [Normal].osu", _levelData);
            music_time=115000;
        break;
    }

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

    // 計算真正開始的 timestamp
    int64_t now = Util::Time::GetElapsedTimeMs();
    _startTimeMs = now + _leadInMs;
    start_time=_startTimeMs;

    // 預載在準備時間內就要進場的水果
    //    也就是 spawnTime < 0 的那些
    for (; _nextIndex < _levelData.objects.size(); ++_nextIndex) {
        auto& o = _levelData.objects[_nextIndex];
        int64_t spawnTime = o.hitTime - _approachMs;
        if (spawnTime >= 0) break;  // 後面的都到準備時間後才處理
        // 立刻生成，但「spawnTime」仍保留負值
        auto fruit = std::make_shared<Fruit>(Fruit::FruitType::Apple);
        int worldX = o.x - 256;
        fruit->m_Transform.translation = { worldX, _spawnStartY };
        fruit->spawnTime = spawnTime;
        fruit->hitTime   = o.hitTime;
        fruits.push_back(fruit);
        AddChild(fruit);
    }

    // BGM、UI、加入 Catcher/背景等
    _started = false;
    // 假設 PTSD 設定：世界 X ∈ [-256,+256]、Y ∈ [-144,+144]
    _scaleX = 512.f / 512.f;  // → 若需要拉伸改這裡
    _scaleY = 288.f / 384.f;

    _bgm->Play();
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

int Level::GetMusicTime() {
    return music_time;
}
int Level::GetStartTime() {
    return start_time;
}


void Level::Update() {
    HandleInput();
    UpdateFruitSpawning();
    UpdateFruits();
    _scoreboard->UpdateScoreboard();
    _scoreboard->Show();
    _combo->UpdateCombo();
    _combo->Show();
}


int Level::Pause() {
    glm::vec2 mouseposition = Util::Input::GetCursorPosition();
    _bgm->Pause();
    SetPauseButton(true);
    if(Util::Input::IsKeyDown(Util::Keycode::ESCAPE) || _continueButton->IsButtonClick(mouseposition)) {
        SetPauseButton(false);
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

void Level::HandleInput() {
    if (Util::Input::IsKeyPressed(Util::Keycode::LEFT))
        _catcher->moveLeft();
    if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT))
        _catcher->moveRight();
}


void Level::UpdateFruitSpawning() {
    if (_nextIndex >= _levelData.objects.size()) return;

    int64_t now     = Util::Time::GetElapsedTimeMs();
    _runTimeMs      = now - _startTimeMs;

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

        // 下墜：線性位移 = 落下距離 / 提前量
        // float progress = float(now - fruit->spawnTime) / _approachMs;
        // if (progress < 0.f) progress = 0.f;
        // if (progress > 1.f) progress = 1.f;
        // fruit->m_Transform.translation.y = _spawnStartY - progress * (_spawnStartY + 130.f);

        fruit->m_Transform.translation.y -= 10;//= (_spawnStartY + 130.f) / _approachMs * (_runTimeMs / (fruit->hitTime - fruit->spawnTime));

        // 判定區間
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
            std::cout<<_runTimeMs<<"ms"<< std::endl;
            continue;
        }

        // 超出底線
        if (pos.y < -400.f) {
            fruit->SetVisible(false);
            RemoveChild(fruit);
            it = fruits.erase(it);
            _combo->ResetCombo();
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