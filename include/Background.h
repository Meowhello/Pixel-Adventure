//
// Created by tfboy on 2025/3/28.
//

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class Background : public Util::GameObject {
public:
    Background(std::string);
    ~Background() = default;
};

#endif //BACKGROUND_H
