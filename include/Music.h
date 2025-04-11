//
// Created by tfboy on 2025/4/11.
//

#ifndef MUSIC_H
#define MUSIC_H
#include "Util/BGM.hpp"

class Music : public Util::BGM{
    public:
    enum class SongName {
        Haruhikage_CRYCHIC,
    };
    void PickMusic(SongName name);

    std::shared_ptr<Util::BGM> song;
};

#endif //MUSIC_H
