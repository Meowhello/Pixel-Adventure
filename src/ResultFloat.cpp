//
// Created by x3052 on 2025/5/16.
//
#include "ResultFloat.h"

ResultFloat::ResultFloat(int x, int y): _x(x), _y(y){
    for (int i = 0; i < 5; i++) {
        auto number = std::make_shared<Number>();
        if(i > 1)
            number->SetPosition(_x - 35 * (i + 1) - 20, _y);
        else if(i == 1)
            number->SetPosition(_x - 80, _y);
        else
            number->SetPosition(_x - 45, _y);
        _numberborad.push_back(number);
        AddChild(number);
    }
    _dot = std::make_shared<Dot>((_x - 105), _y);
    AddChild(_dot);
    m_Drawable = std::make_shared<Util::Image>("../Resources/Image/game_sources/%.png");
    m_Transform.translation = {_x, _y};
    m_Transform.scale = {0.325, 0.325};
}


void ResultFloat::Show(float number) {
    int value = static_cast<int>(number * 10000);
    for (int i = 0; i < 5; i++) {
        _number[i] = value%10;
        value /= 10;
    }
    for (int i = 0; i < 5; i++) {
        _numberborad[i]->UpdateImage(_number[i]);
    }

    for(int i = 0; i < 5; i++) {
        _numberborad[i]->Show();
    }

    if (_numberborad.empty())
        return;

    int highestIdx = -1;
    for (int i = static_cast<int>(_numberborad.size()) - 1; i > 0; --i)
    {
        if (!_numberborad[i]) continue;

        if (i > highestIdx)
        {
            if(_number[i] != 0) {
                if (highestIdx == -1)
                    highestIdx = i;
                _numberborad[i]->SetVisible(true);
            }
            else
                _numberborad[i]->SetVisible(false);
        }
    }
    _numberborad[0]->SetVisible(true);
}
