//
// Created by x3052 on 2025/5/16.
//
#include "ResultInteger.h"

ResultInteger::ResultInteger(int x, int y): _x(x), _y(y){
    for (int i = 0; i < 3; i++) {
        auto number = std::make_shared<Number>();
        number->SetPosition(_x - 35 * (i + 1), _y);
        _numberborad.push_back(number);
        AddChild(number);
    }
    m_Drawable = std::make_shared<Util::Image>("../Resources/Image/game_sources/x.png");
    m_Transform.translation = {_x, _y};
    m_Transform.scale = {0.325, 0.325};
}


void ResultInteger::Show(int number) {
    for (int i = 0; i < 3; i++) {
        _number[i] = number%10;
        number /= 10;
    }
    for (int i = 0; i < 3; i++) {
        _numberborad[i]->UpdateImage(_number[i]);
    }

    for(int i = 0; i < 3; i++) {
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
