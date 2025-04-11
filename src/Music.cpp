//
// Created by tfboy on 2025/4/11.
//
#include "Music.h"
#include <iostream>

void Music::PickMusic(SongName name) {
    std::string filepath;
    switch (name) {
        case SongName::Haruhikage_CRYCHIC:
            filepath = (RESOURCE_DIR "/music/Haruhikage_CRYCHIC");
        break;
    }
    song=std::make_shared<Util::BGM>(filepath);
    song->Play();
}
