//
// Created by x3052 on 2025/5/16.
//

#ifndef RESULTNUMBER_H
#define RESULTNUMBER_H

#include "Util/Image.hpp"
#include "Util/GameObject.hpp"
#include "Number.h"

class ResultInteger: public Util::GameObject {
public:
    ResultInteger(int, int);
    ~ResultInteger() = default;

    void Show(int);

private:
    std::vector<int> _number = std::vector<int>(3, 0);
    std::vector<std::shared_ptr<Number>> _numberborad  = std::vector<std::shared_ptr<Number>>();
    int _x, _y;
};

#endif //RESULTNUMBER_H
