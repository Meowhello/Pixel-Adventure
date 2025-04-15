//
// Created by x3052 on 2025/4/4.
//

#ifndef BUTTON_H
#define BUTTON_H

#include "Util/Image.hpp"
#include "Util/GameObject.hpp"

class Button : public Util::GameObject {
public:
    Button(std::string, int, int, int, int);
    ~Button() = default;
    bool IsButtonClick(glm::vec2 positon);
private:
    std::shared_ptr<Util::Image> _buttonImage;
    int _x, _y;
    int _height, _width;
};



#endif //BUTTON_H
