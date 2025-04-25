//
// Created by tfboy on 2025/3/21.
//

#ifndef CATCHER_H
#define CATCHER_H
#include "Core/Drawable.hpp"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class Catcher : public Util::GameObject{
public:
    Catcher();
    // ~Catcher();

    // void show();
    void moveLeft();
    void moveRight();

private:
    float moveSpeed;
    bool direction;
};

#endif //CATCHER_H
