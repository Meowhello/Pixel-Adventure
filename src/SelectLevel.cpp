//
// Created by x3052 on 2025/4/16.
//
#include "SelectLevel.h"

#include <iostream>

#include "Util/Input.hpp"
SelectLevel::SelectLevel() {
    AddChild(_background);
    _configs = {
        {"Haruhikage", "../Resources/Songs/2070468 CRYCHIC - Haruhikage (TV Size)/audio.mp3", "../Resources/music/normal-hitclap.wav", "../Resources/Songs/2070468 CRYCHIC - Haruhikage (TV Size)/1.png", "../Resources/Songs/2070468 CRYCHIC - Haruhikage (TV Size)/CRYCHIC - Haruhikage (TV Size) (lkx_Shore) [Normal].osu", "../Resources/Image/select_level/easy_open.png"},
        {"Georgette Me, Georgette You", "../Resources/Songs/2308600 Ave Mujica - Georgette Me, Georgette You (TV Size)/audio.mp3", "../Resources/music/normal-hitclap.wav", "../Resources/Songs/2308600 Ave Mujica - Georgette Me, Georgette You (TV Size)/BG.PNG", "../Resources/Songs/2308600 Ave Mujica - Georgette Me, Georgette You (TV Size)/Ave Mujica - Georgette Me, Georgette You (TV Size) (Plus4j) [GfTNT's Hard].osu", "../Resources/Image/select_level/easy_open.png"},
        {"Miracle Sugite Yabai (feat shully)", "../Resources/Songs/682290 Hige Driver - Miracle Sugite Yabai (feat shully)/audio.mp3", "../Resources/music/normal-hitclap.wav", "../Resources/Songs/682290 Hige Driver - Miracle Sugite Yabai (feat shully)/BG.jpg", "../Resources/Songs/682290 Hige Driver - Miracle Sugite Yabai (feat shully)/Hige Driver - Miracle Sugite Yabai (feat. shully) (Milan-) [Normal].osu", "../Resources/Image/select_level/easy_open.png"},
        {"Hanaarashi", "../Resources/Songs/751771 Cranky - Hanaarashi/audio.mp3", "../Resources/music/normal-hitclap.wav", "../Resources/Songs/751771 Cranky - Hanaarashi/BG.PNG", "../Resources/Songs/751771 Cranky - Hanaarashi/Cranky - Hanaarashi (Mirash) [Normal].osu", "../Resources/Image/select_level/easy_open.png"},
        {"Bwa!","../Resources/Songs/767346 Thaehan - Bwa !/audio.mp3","../Resources/music/normal-hitclap.wav","../Resources/Songs/767346 Thaehan - Bwa !/BG.png","../Resources/Songs/767346 Thaehan - Bwa !/Thaehan - Bwa ! (Deif) [Salad].osu","../Resources/Image/select_level/easy_open.png"},
        {"LP","../Resources/Songs/789374 Pulse - LP/audio.mp3","../Resources/music/normal-hitclap.wav","../Resources/Songs/789374 Pulse - LP/BG.png","../Resources/Songs/789374 Pulse - LP/Pulse - LP (pishifat) [Mao's Normal].osu","../Resources/Image/select_level/easy_open.png"},
        {"Aurora","../Resources/Songs/848003 Culprate - Aurora/audio.mp3","../Resources/music/normal-hitclap.wav","../Resources/Songs/848003 Culprate - Aurora/BG.jpg","../Resources/Songs/848003 Culprate - Aurora/Culprate - Aurora (BOUYAAA) [pishi's Normal].osu","../Resources/Image/select_level/easy_open.png"},
        {"DAI_TAN SENSATION","../Resources/Songs/848090 Trial & Error - DAI_TAN SENSATION/audio.mp3","../Resources/music/normal-hitclap.wav","../Resources/Songs/848090 Trial & Error - DAI_TAN SENSATION/BG.jpg","../Resources/Songs/848090 Trial & Error - DAI_TAN SENSATION/Trial & Error - DAITAN SENSATION(Gero) [Easy].osu","../Resources/Image/select_level/easy_open.png"},
        {"My life is for you","../Resources/Songs/891417 HyuN feat Yu-A - My life is for you/audio.mp3","../Resources/music/normal-hitclap.wav","../Resources/Songs/891417 HyuN feat Yu-A - My life is for you/BG.jpg","../Resources/Songs/891417 HyuN feat Yu-A - My life is for you/HyuN feat. Yu-A - My life is for you (NeilPerry) [Chaoz's Normal].osu","../Resources/Image/select_level/easy_open.png"},
        {"Module_410","../Resources/Songs/957808 Fractal Dreamers - Module_410/audio.mp3","../Resources/music/normal-hitclap.wav","../Resources/Songs/957808 Fractal Dreamers - Module_410/BG.jpg","../Resources/Songs/957808 Fractal Dreamers - Module_410/Fractal Dreamers - Module_410 (MBomb) [Cup].osu","../Resources/Image/select_level/easy_open.png"},
        {"Passage D","../Resources/Songs/966225 The Flashbulb - Passage D/audio.mp3","../Resources/music/normal-hitclap.wav","../Resources/Songs/966225 The Flashbulb - Passage D/BG.jpg","../Resources/Songs/966225 The Flashbulb - Passage D/The Flashbulb - Passage D (fieryrage) [Easy].osu","../Resources/Image/select_level/easy_open.png"},
        {"Challenger","../Resources/Songs/966240 Creo - Challenger/audio.mp3","../Resources/music/normal-hitclap.wav","../Resources/Songs/966240 Creo - Challenger/BG.png","../Resources/Songs/966240 Creo - Challenger/Creo - Challenger (Rocma) [Salad].osu","../Resources/Image/select_level/easy_open.png"},
        {"Runengon","../Resources/Songs/971561 antiPLUR - Runengon/audio.mp3","../Resources/music/normal-hitclap.wav","../Resources/Songs/971561 antiPLUR - Runengon/BG.jpg","../Resources/Songs/971561 antiPLUR - Runengon/antiPLUR - Runengon (Raveille) [Normal].osu","../Resources/Image/select_level/easy_open.png"},
        {"Reaction feat Slyleaf","../Resources/Songs/994104 James Landino - Reaction feat Slyleaf/audio.mp3","../Resources/music/normal-hitclap.wav","../Resources/Songs/994104 James Landino - Reaction feat Slyleaf/BG.jpg","../Resources/Songs/994104 James Landino - Reaction feat Slyleaf/James Landino - Reaction feat. Slyleaf (AncuL) [Normal].osu","../Resources/Image/select_level/easy_open.png"},

    };
    for (int i = 0; i < _configs.size(); ++i) {
        auto btn = std::make_shared<LevelButton>(_configs[i].btnPath, 400 + i * 10, i * -100);
        _buttons.push_back(btn);
        AddChild(btn);
    }
}

std::shared_ptr<Level> SelectLevel::Update()
{
    float dt = 0.05;
    if (Util::Input::IfScroll())
    {
        float scrollY = Util::Input::GetScrollDistance().y;
        for (auto &btn : _buttons)
            scrollY > 0 ? btn->MoveDown() : btn->MoveUp();
    }

    glm::vec2 mousePos = Util::Input::GetCursorPosition();
    if (Util::Input::IsKeyPressed(Util::Keycode::MOUSE_LB))
    {
        for (int i = 0; i < _buttons.size(); ++i)
        {
            if (_buttons[i]->IsButtonClick(mousePos))
            {
                _background->Change(_configs[i].bgPath);
                _targetIdx   = i;
                float centerY = 0.f;
                _remainDelta = centerY - _buttons[i]->getPosition().y;
                break;
            }
        }
    }

    if (std::abs(_remainDelta) > 0.5f)
    {
        float step = glm::sign(_remainDelta) * SCROLL_SPEED * dt;

        if (std::abs(step) > std::abs(_remainDelta))
            step = _remainDelta;

        for (auto &btn : _buttons)
            btn->Translate(step);

        _remainDelta -= step;
    }
    else
    {
        _remainDelta = 0.f;
        if (_targetIdx != -1 &&
            _buttons[_targetIdx]->IsButtonClick(mousePos))
        {
            auto &cfg = _configs[_targetIdx];
            return std::make_shared<Level>(cfg.name,
                                            cfg.bgmPath, cfg.sfxPath,
                                            cfg.bgPath, cfg.osuPath);
        }
    }

    return nullptr;
}
