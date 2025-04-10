//
// Created by x3052 on 2025/3/28.
//

#ifndef SCOREBSOARD_H
#define SCOREBSOARD_H

#include "Util/Image.hpp"
#include "Util/GameObject.hpp"

class Number : public Util::GameObject  {
public:
    Number();
    ~Number() = default;

    void Show();
    void UpdateImage(int);
    void SetPosition(int, int);
private:
    std::shared_ptr<Util::Image> _numberImage;
    int _x, _y;
};


#endif //SCOREBSOARD_H
