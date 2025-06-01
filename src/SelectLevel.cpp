//
// Created by x3052 on 2025/4/16.
//
#include "SelectLevel.h"

#include <iostream>
#include <cstdlib>

#include "Util/Input.hpp"
SelectLevel::SelectLevel() {
    std::string randomNumber = std::to_string(rand() % 2 + 1);
    AddChild(_background);
    _configs = {
        {"Mayoiuta", "../Resources/Songs/2064958 MyGO!!!!! - Mayoiuta/audio.mp3", "../Resources/music/normal-hitclap.wav", "../Resources/Songs/2064958 MyGO!!!!! - Mayoiuta/BG.jpg", "../Resources/Songs/2064958 MyGO!!!!! - Mayoiuta/MyGO!!!!! - Mayoiuta (Gust) [Surou's Normal].osu", "../Resources/Image/select_level/easy_open.png"},
        {"2Utakotoba", "../Resources/Songs/2084617 MyGO!!!!! - Utakotoba/audio.mp3", "../Resources/music/normal-hitclap.wav", "../Resources/Songs/2084617 MyGO!!!!! - Utakotoba/BG.jpg", "../Resources/Songs/2084617 MyGO!!!!! - Utakotoba/MyGO!!!!! - Utakotoba (Gust) [Patchouli-R's Normal].osu", "../Resources/Image/select_level/easy_open.png"},
        {"Silhouette Dance", "../Resources/Songs/2066973 MyGO!!!!! - Silhouette Dance/audio.mp3", "../Resources/music/normal-hitclap.wav", "../Resources/Songs/2066973 MyGO!!!!! - Silhouette Dance/BG.jpg", "../Resources/Songs/2066973 MyGO!!!!! - Silhouette Dance/MyGO!!!!! - Silhouette Dance (kiddly) [Hatsune Miku's Normal].osu", "../Resources/Image/select_level/easy_open.png"},

        {"Haruhikage", "../Resources/Songs/2070468 CRYCHIC - Haruhikage (TV Size)/audio.mp3", "../Resources/music/normal-hitclap.wav", "../Resources/Songs/2070468 CRYCHIC - Haruhikage (TV Size)/"+ randomNumber +".png", "../Resources/Songs/2070468 CRYCHIC - Haruhikage (TV Size)/CRYCHIC - Haruhikage (TV Size) (lkx_Shore) [Normal].osu", "../Resources/Songs/2070468 CRYCHIC - Haruhikage (TV Size)/btn_blue.png"},
        {"KiLLKiSS", "../Resources/Songs/2298154 Ave Mujica - KiLLKiSS (TV Size)/audio.mp3", "../Resources/music/normal-hitclap.wav", "../Resources/Songs/2298154 Ave Mujica - KiLLKiSS (TV Size)/BG.jpg", "../Resources/Songs/2298154 Ave Mujica - KiLLKiSS (TV Size)/Ave Mujica - KiLLKiSS (TV Size) (Plus4j) [Normal].osu", "../Resources/Image/select_level/easy_open.png"},
        {"Black Birthday", "../Resources/Songs/2287975 Ave Mujica - Black Birthday/audio.mp3", "../Resources/music/normal-hitclap.wav", "../Resources/Songs/2287975 Ave Mujica - Black Birthday/BG.jpg", "../Resources/Songs/2287975 Ave Mujica - Black Birthday/Ave Mujica - Black Birthday (Plus4j) [Garden's Hard].osu", "../Resources/Image/select_level/easy_open.png"},
        {"Symbol III _ Water", "../Resources/Songs/2259244 Ave Mujica - Symbol III _ Water/audio.mp3", "../Resources/music/normal-hitclap.wav", "../Resources/Songs/2259244 Ave Mujica - Symbol III _ Water/BG.jpg", "../Resources/Songs/2259244 Ave Mujica - Symbol III _ Water/Ave Mujica - Symbol III  Water (Plus4j) [frozz's Hard].osu", "../Resources/Image/select_level/easy_open.png"},
        {"Georgette Me, Georgette You", "../Resources/Songs/2308600 Ave Mujica - Georgette Me, Georgette You (TV Size)/audio.mp3", "../Resources/music/normal-hitclap.wav", "../Resources/Songs/2308600 Ave Mujica - Georgette Me, Georgette You (TV Size)/BG.PNG", "../Resources/Songs/2308600 Ave Mujica - Georgette Me, Georgette You (TV Size)/Ave Mujica - Georgette Me, Georgette You (TV Size) (Plus4j) [GfTNT's Hard].osu", "../Resources/Songs/2308600 Ave Mujica - Georgette Me, Georgette You (TV Size)/btn_blue.png"},

        {"Wrong World", "../Resources/Songs/2178995 TOGENASHI TOGEARI - Wrong World (TV Size)/audio.mp3", "../Resources/music/normal-hitclap.wav", "../Resources/Songs/2178995 TOGENASHI TOGEARI - Wrong World (TV Size)/BG.jpg", "../Resources/Songs/2178995 TOGENASHI TOGEARI - Wrong World (TV Size)/TOGENASHI TOGEARI - Wrong World (TV Size) (Plus4j) [Hard].osu", "../Resources/Image/select_level/easy_open.png"},
        {"VOID", "../Resources/Songs/2172979 TOGENASHI TOGEARI - VOID (TV Size)/audio.mp3", "../Resources/music/normal-hitclap.wav", "../Resources/Songs/2172979 TOGENASHI TOGEARI - VOID (TV Size)/BG.jpg", "../Resources/Songs/2172979 TOGENASHI TOGEARI - VOID (TV Size)/TOGENASHI TOGEARI - VOID (TV Size) (KeyWee) [Hard].osu", "../Resources/Image/select_level/easy_open.png"},
        {"Voiceless Fish", "../Resources/Songs/2175464 Shin-Kawasaki (Kari) - Voiceless Fish (TV Size)/audio.mp3", "../Resources/music/normal-hitclap.wav", "../Resources/Songs/2175464 Shin-Kawasaki (Kari) - Voiceless Fish (TV Size)/BG.jpg", "../Resources/Songs/2175464 Shin-Kawasaki (Kari) - Voiceless Fish (TV Size)/Shin-Kawasaki (Kari) - Voiceless Fish (TV Size) (_Karaage) [Normal].osu", "../Resources/Image/select_level/easy_open.png"},
        {"Emptiness and Catharsis", "../Resources/Songs/2197908 TOGENASHI TOGEARI - Emptiness and Catharsis/audio.mp3", "../Resources/music/normal-hitclap.wav", "../Resources/Songs/2197908 TOGENASHI TOGEARI - Emptiness and Catharsis/BG.jpg", "../Resources/Songs/2197908 TOGENASHI TOGEARI - Emptiness and Catharsis/TOGENASHI TOGEARI - Emptiness and Catharsis (_Karaage) [Normal].osu", "../Resources/Image/select_level/easy_open.png"},
        {"I'm Nobody", "../Resources/Songs/2377570 TOGENASHI TOGEARI - I'm Nobody (TV Size)/audio.mp3", "../Resources/music/normal-hitclap.wav", "../Resources/Songs/2377570 TOGENASHI TOGEARI - I'm Nobody (TV Size)/BG.png", "../Resources/Songs/2377570 TOGENASHI TOGEARI - I'm Nobody (TV Size)/TOGENASHI TOGEARI - I'm Nobody (TV Size) (Barmy) [Liyuu_0109's Hard].osu", "../Resources/Image/select_level/easy_open.png"},

        {"Seiza ni Naretara", "../Resources/Songs/1909824 kessoku band - Seiza ni Naretara/audio.mp3", "../Resources/music/normal-hitclap.wav", "../Resources/Songs/1909824 kessoku band - Seiza ni Naretara/BG.jpg", "../Resources/Songs/1909824 kessoku band - Seiza ni Naretara/kessoku band - Seiza ni Naretara (Amateurre) [AmaNoodl's Hard].osu", "../Resources/Image/select_level/easy_open.png"},
        {"Guitar to Kodoku to Aoi Hoshi", "../Resources/Songs/1880007 kessoku band - Guitar to Kodoku to Aoi Hoshi/audio.mp3", "../Resources/music/normal-hitclap.wav", "../Resources/Songs/1880007 kessoku band - Guitar to Kodoku to Aoi Hoshi/BG.jpg", "../Resources/Songs/1880007 kessoku band - Guitar to Kodoku to Aoi Hoshi/kessoku band - Guitar to Kodoku to Aoi Hoshi (ponbot) [Normal].osu", "../Resources/Image/select_level/easy_open.png"},
        {"Seishun Complex", "../Resources/Songs/1863866 kessoku band - Seishun Complex/audio.mp3", "../Resources/music/normal-hitclap.wav", "../Resources/Songs/1863866 kessoku band - Seishun Complex/BG.jpg", "../Resources/Songs/1863866 kessoku band - Seishun Complex/Kessoku Band - Seishun Complex (_kotachi_) [Crysisters' Normal].osu", "../Resources/Image/select_level/easy_open.png"},
        {"Ano Band", "../Resources/Songs/1905695 kessoku band - Ano Band (TV Size)/audio.mp3", "../Resources/music/normal-hitclap.wav", "../Resources/Songs/1905695 kessoku band - Ano Band (TV Size)/BG.jpg", "../Resources/Songs/1905695 kessoku band - Ano Band (TV Size)/kessoku band - Ano Band (TV Size) (Mahiru Shiina) [Floth's Normal Band].osu", "../Resources/Image/select_level/easy_open.png"},
        {"Wasurete Yaranai", "../Resources/Songs/1909993 kessoku band - Wasurete Yaranai/audio.mp3", "../Resources/music/normal-hitclap.wav", "../Resources/Songs/1909993 kessoku band - Wasurete Yaranai/BG" + randomNumber +".jpg", "../Resources/Songs/1909993 kessoku band - Wasurete Yaranai/kessoku band - Wasurete Yaranai (Matsuyuki Ame) [Normal].osu", "../Resources/Image/select_level/easy_open.png"},

        {"Miracle Sugite Yabai (feat shully)", "../Resources/Songs/682290 Hige Driver - Miracle Sugite Yabai (feat shully)/audio.mp3", "../Resources/music/normal-hitclap.wav", "../Resources/Songs/682290 Hige Driver - Miracle Sugite Yabai (feat shully)/BG.jpg", "../Resources/Songs/682290 Hige Driver - Miracle Sugite Yabai (feat shully)/Hige Driver - Miracle Sugite Yabai (feat. shully) (Milan-) [Normal].osu", "../Resources/Songs/682290 Hige Driver - Miracle Sugite Yabai (feat shully)/btn_blue.png"},
        {"Hanaarashi", "../Resources/Songs/751771 Cranky - Hanaarashi/audio.mp3", "../Resources/music/normal-hitclap.wav", "../Resources/Songs/751771 Cranky - Hanaarashi/BG.PNG", "../Resources/Songs/751771 Cranky - Hanaarashi/Cranky - Hanaarashi (Mirash) [Normal].osu", "../Resources/Songs/751771 Cranky - Hanaarashi/btn_blue.png"},
        {"Bwa!","../Resources/Songs/767346 Thaehan - Bwa !/audio.mp3","../Resources/music/normal-hitclap.wav","../Resources/Songs/767346 Thaehan - Bwa !/BG.png","../Resources/Songs/767346 Thaehan - Bwa !/Thaehan - Bwa ! (Deif) [Salad].osu","../Resources/Songs/767346 Thaehan - Bwa !/btn_blue.png"},
        {"LP","../Resources/Songs/789374 Pulse - LP/audio.mp3","../Resources/music/normal-hitclap.wav","../Resources/Songs/789374 Pulse - LP/BG.png","../Resources/Songs/789374 Pulse - LP/Pulse - LP (pishifat) [Mao's Normal].osu","../Resources/Songs/789374 Pulse - LP/btn_blue.png"},
        {"Aurora","../Resources/Songs/848003 Culprate - Aurora/audio.mp3","../Resources/music/normal-hitclap.wav","../Resources/Songs/848003 Culprate - Aurora/BG.jpg","../Resources/Songs/848003 Culprate - Aurora/Culprate - Aurora (BOUYAAA) [pishi's Normal].osu","../Resources/Songs/848003 Culprate - Aurora/btn_blue.png"},
        {"DAI_TAN SENSATION","../Resources/Songs/848090 Trial & Error - DAI_TAN SENSATION/audio.mp3","../Resources/music/normal-hitclap.wav","../Resources/Songs/848090 Trial & Error - DAI_TAN SENSATION/BG.jpg","../Resources/Songs/848090 Trial & Error - DAI_TAN SENSATION/Trial & Error - DAITAN SENSATION(Gero) [Easy].osu","../Resources/Songs/848090 Trial & Error - DAI_TAN SENSATION/btn_blue.png"},
        {"My life is for you","../Resources/Songs/891417 HyuN feat Yu-A - My life is for you/audio.mp3","../Resources/music/normal-hitclap.wav","../Resources/Songs/891417 HyuN feat Yu-A - My life is for you/BG.jpg","../Resources/Songs/891417 HyuN feat Yu-A - My life is for you/HyuN feat. Yu-A - My life is for you (NeilPerry) [Chaoz's Normal].osu","../Resources/Songs/891417 HyuN feat Yu-A - My life is for you/btn_blue.png"},
        {"Module_410","../Resources/Songs/957808 Fractal Dreamers - Module_410/audio.mp3","../Resources/music/normal-hitclap.wav","../Resources/Songs/957808 Fractal Dreamers - Module_410/BG.jpg","../Resources/Songs/957808 Fractal Dreamers - Module_410/Fractal Dreamers - Module_410 (MBomb) [Cup].osu","../Resources/Songs/957808 Fractal Dreamers - Module_410/btn_blue.png"},
        {"Passage D","../Resources/Songs/966225 The Flashbulb - Passage D/audio.mp3","../Resources/music/normal-hitclap.wav","../Resources/Songs/966225 The Flashbulb - Passage D/BG.jpg","../Resources/Songs/966225 The Flashbulb - Passage D/The Flashbulb - Passage D (fieryrage) [Easy].osu","../Resources/Songs/966225 The Flashbulb - Passage D/btn_blue.png"},
        {"Challenger","../Resources/Songs/966240 Creo - Challenger/audio.mp3","../Resources/music/normal-hitclap.wav","../Resources/Songs/966240 Creo - Challenger/BG.png","../Resources/Songs/966240 Creo - Challenger/Creo - Challenger (Rocma) [Salad].osu","../Resources/Songs/966240 Creo - Challenger/btn_blue.png"},
        {"Runengon","../Resources/Songs/971561 antiPLUR - Runengon/audio.mp3","../Resources/music/normal-hitclap.wav","../Resources/Songs/971561 antiPLUR - Runengon/BG.jpg","../Resources/Songs/971561 antiPLUR - Runengon/antiPLUR - Runengon (Raveille) [Normal].osu","../Resources/Songs/971561 antiPLUR - Runengon/btn_blue.png"},
        {"Reaction feat Slyleaf","../Resources/Songs/994104 James Landino - Reaction feat Slyleaf/audio.mp3","../Resources/music/normal-hitclap.wav","../Resources/Songs/994104 James Landino - Reaction feat Slyleaf/BG.jpg","../Resources/Songs/994104 James Landino - Reaction feat Slyleaf/James Landino - Reaction feat. Slyleaf (AncuL) [Normal].osu","../Resources/Songs/994104 James Landino - Reaction feat Slyleaf/btn_blue.png"},

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
