//
// Created by x3052 on 2025/5/19.
//

#ifndef AUDIOUTIL_H
#define AUDIOUTIL_H
#include <SDL_mixer.h>

inline bool BgmIsPlaying()   { return Mix_PlayingMusic() != 0; }
inline bool BgmHasPaused()   { return Mix_PausedMusic()  != 0; }
inline bool BgmHasFinished() {
    return Mix_PlayingMusic() == 0 && Mix_PausedMusic() == 0;
}


#endif //AUDIOUTIL_H
