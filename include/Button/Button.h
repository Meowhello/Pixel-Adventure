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

    glm::vec2 getPosition() const;
    glm::vec2 getSize() const;
    void setPosition(const glm::vec2&);
    void setSize(const glm::vec2&);
    bool IsButtonClick(glm::vec2 positon);
    bool IsOnButton(glm::vec2 position);


protected:
    glm::vec2 _size;
    std::string whiteBtnPath;
};



#endif //BUTTON_H
