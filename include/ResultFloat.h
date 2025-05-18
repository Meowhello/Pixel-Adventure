//
// Created by x3052 on 2025/5/16.
//

#ifndef RESULTFLOAT_H
#define RESULTFLOAT_H

#include "Util/Image.hpp"
#include "Util/GameObject.hpp"
#include "Number.h"

class Dot: public Util::GameObject {
public:
    Dot(int x, int y) {
        m_Drawable = std::make_shared<Util::Image>("../Resources/Image/game_sources/score-dot.png");
        m_Transform.translation = {x, y};
    };
    ~Dot() = default;
};

class ResultFloat: public Util::GameObject {
public:
    ResultFloat(int, int);
    ~ResultFloat() = default;

    void Show(float);

private:
    std::vector<int> _number = std::vector<int>(5, 0);
    std::vector<std::shared_ptr<Number>> _numberborad  = std::vector<std::shared_ptr<Number>>();
    std::shared_ptr<Dot> _dot;
    int _x, _y;
};



#endif //RESULTFLOAT_H
