//
// Created by tfboy on 2025/3/28.
//

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class Background : public Util::GameObject {
public:
    enum class level {
        level_1,
        pause,
    };

    Background(level change);

};

#endif //BACKGROUND_H
