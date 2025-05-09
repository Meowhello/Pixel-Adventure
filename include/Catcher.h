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
    ~Catcher() = default;

    // void show();
    void MoveLeft();
    void MoveRight();
    void ResetPos();

private:
    float moveSpeed;
    bool direction;
};

#endif //CATCHER_H
