//
// Created by x3052 on 2025/4/15.
//
#include "MainMenu.h"

#include "Util/Input.hpp"

MainMenu::MainMenu() {
    _background = std::make_shared<Background>(background());
    AddChild(_background);
    AddChild(_playButton);
    AddChild(_exitButton);

    m_Drawable = std::make_shared<Util::Image>((RESOURCE_DIR "/Image/main_page/cd.png"));
    m_Transform.scale = {0.8, 0.8};
    m_ZIndex = 5;
}

int MainMenu::Update() {

    glm::vec2 mouseposition = Util::Input::GetCursorPosition();

    if(_playButton->IsButtonClick(mouseposition)) {
        return 1;
    }

    if(_exitButton->IsButtonClick(mouseposition)) {
        return 2;
    }

    return 0;
}

std::string MainMenu::background() {
    std::string backgroundpic= "";

    auto randpic=rand()%(37); //max-min+1-min
    switch (randpic) {
        case 0:
            backgroundpic= "../Resources/Songs/682290 Hige Driver - Miracle Sugite Yabai (feat shully)/BG.jpg";
        break;
        case 1:
            backgroundpic="../Resources/Songs/751771 Cranky - Hanaarashi/BG.png";
        break;
        case 2:
            backgroundpic="../Resources/Songs/2308600 Ave Mujica - Georgette Me, Georgette You (TV Size)/BG.png";
        break;
        case 3:
            backgroundpic="../Resources/Songs/767346 Thaehan - Bwa !/BG.png";
        break;
        case 4:
            backgroundpic="../Resources/Songs/789374 Pulse - LP/BG.png";
        break;
        case 5:
            backgroundpic="../Resources/Songs/847323 Nakanojojo - Bittersweet (feat Kuishinboakachan aka Kiato)/BG.jpg";
        break;
        case 6:
            backgroundpic="../Resources/Songs/848003 Culprate - Aurora/BG.jpg";
        break;
        case 7:
            backgroundpic="../Resources/Songs/848090 Trial & Error - DAI_TAN SENSATION/BG.jpg";
        break;
        case 8:
            backgroundpic="../Resources/Songs/891417 HyuN feat Yu-A - My life is for you/BG.jpg";
        break;
        case 9:
            backgroundpic="../Resources/Songs/919704 S3RL - I Will Pick You Up (feat Tamika)/BG.jpg";
        break;
        case 10:
            backgroundpic="../Resources/Songs/957808 Fractal Dreamers - Module_410/BG.jpg";
        break;
        case 11:
            backgroundpic="../Resources/Songs/966225 The Flashbulb - Passage D/BG.jpg";
        break;
        case 12:
            backgroundpic="../Resources/Songs/966240 Creo - Challenger/BG.png";
        break;
        case 13:
            backgroundpic="../Resources/Songs/966407 LukHash - ROOM 12/BG.jpg";
        break;
        case 14:
            backgroundpic="../Resources/Songs/971561 antiPLUR - Runengon/BG.jpg";
        break;
        case 15:
            backgroundpic="../Resources/Songs/994104 James Landino - Reaction feat Slyleaf/BG.jpg";
        break;
        case 16:
            backgroundpic="../Resources/Songs/1015169 Thaehan - Insert Coin/alien-arcade-background-1670977.jpg";
        break;
        case 17:
            backgroundpic="../Resources/Songs/1388906 Raphlesia & BilliumMoto - My Love/final.jpg";
        break;
        case 18:
            backgroundpic="../Resources/Songs/2070468 CRYCHIC - Haruhikage (TV Size)/1.png";
        break;
        case 19:
            backgroundpic="../Resources/Songs/2070468 CRYCHIC - Haruhikage (TV Size)/2.png";
        break;
        case 20:
            backgroundpic="../Resources/Songs/2259244 Ave Mujica - Symbol III _ Water/BG.jpg";
        break;
        case 21:
            backgroundpic="../Resources/Songs/2298154 Ave Mujica - KiLLKiSS (TV Size)/BG.jpg";
        break;
        case 22:
            backgroundpic="../Resources/Songs/2287975 Ave Mujica - Black Birthday/BG.jpg";
        break;
        case 23:
            backgroundpic="../Resources/Songs/2178995 TOGENASHI TOGEARI - Wrong World (TV Size)/BG.jpg";
        break;
        case 24:
            backgroundpic="../Resources/Songs/2172979 TOGENASHI TOGEARI - VOID (TV Size)/BG.jpg";
        break;
        case 25:
            backgroundpic="../Resources/Songs/2175464 Shin-Kawasaki (Kari) - Voiceless Fish (TV Size)/BG.jpg";
        break;
        case 26:
            backgroundpic="../Resources/Songs/2377570 TOGENASHI TOGEARI - I'm Nobody (TV Size)/BG.jpg";
        break;
        case 27:
            backgroundpic="../Resources/Songs/1863866 kessoku band - Seishun Complex/BG.jpg";
        break;
        case 28:
            backgroundpic="../Resources/Songs/1880007 kessoku band - Guitar to Kodoku to Aoi Hoshi/BG.jpg";
        break;
        case 29:
            backgroundpic="../Resources/Songs/1909824 kessoku band - Seiza ni Naretara/BG.jpg";
        break;
        case 30:
            backgroundpic="../Resources/Songs/2197908 TOGENASHI TOGEARI - Emptiness and Catharsis/BG.jpg";
        break;
        case 31:
            backgroundpic="../Resources/Songs/2064958 MyGO!!!!! - Mayoiuta/BG.jpg";
        break;
        case 32:
            backgroundpic="../Resources/Songs/2084617 MyGO!!!!! - Utakotoba/BG.jpg";
        break;
        case 33:
            backgroundpic="../Resources/Songs/2066973 MyGO!!!!! - Silhouette Dance/BG.jpg";
        break;
        case 34:
            backgroundpic="../Resources/Songs/1905695 kessoku band - Ano Band (TV Size)/BG.jpg";
        break;
        case 35:
            backgroundpic="../Resources/Songs/1909993 kessoku band - Wasurete Yaranai/BG1.jpg";
        break;
        case 36:
            backgroundpic="../Resources/Songs/1909993 kessoku band - Wasurete Yaranai/BG2.jpg";
        break;


    }
        return backgroundpic;
    // m_Drawable = std::make_shared<Util::Image>(RESOURCE_DIR "/Songs/"+backgroundpic+"/BG.jpg");
    // std::string bg=RESOURCE_DIR "/Songs/"+backgroundpic+"/BG.jpg";

}

void MainMenu::ChangeBG() {
    _background->Change(background());
}

