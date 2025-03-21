//
// Created by tfboy on 2025/3/21.
//

#ifndef CATCHER_H
#define CATCHER_H
#include <string>
#include "Core/Drawable.hpp"
#include "Util/Image.hpp"

class Catcher {
public:
    Catcher();
    ~Catcher();

    void show();
    void moveLeft();
    void moveRight();
private:
    glm::vec3 position;
    Util::Image myImage;
    Core::Matrices matrices;
    float moveSpeed;
};

#endif //CATCHER_H
