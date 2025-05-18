//
// Created by x3052 on 2025/4/9.
//
//
// Created by x3052 on 2025/4/4.
//
#include "Combo.h"

#include <iostream>

Combo::Combo(): _x(560), _y(-330){
    for (int i = 0; i < 3; i++) {
        auto number = std::make_shared<Number>();
        number->SetPosition(460 - 35 * i, -330);
        _comboborad.push_back(number);
        AddChild(number);
    }
    m_Drawable = std::make_shared<Util::Image>("../Resources/Image/game_sources/default-combo.png");
    m_Transform.translation = {_x, _y};
    m_Transform.scale = {0.325, 0.5};
}


void Combo::Show() {
    for(int i = 0; i < 3; i++) {
        _comboborad[i]->Show();
    }
}

void Combo::AddCombo(int delta) {
    // conum+=delta;
    int carry = delta;
    for (int i = 0; i < 3 && carry > 0; i++) {
        int sum = _combo[i] + carry;
        _combo[i] = sum % 10;
        carry = sum / 10;
    }
}

void Combo::ResetCombo() {
    // conum=0;
    for (int i = 0; i < 3; i++) {
        _combo[i] = 0;
    }
}


void Combo::UpdateCombo() {
    for (int i = 0; i < 3; i++) {
        _comboborad[i]->UpdateImage(_combo[i]);
    }

    if (_comboborad.empty())
        return;

    int highestIdx = -1;
    for (int i = static_cast<int>(_comboborad.size()) - 1; i > 0; --i)
    {
        if (!_comboborad[i])
            continue;

        if (i > highestIdx)
        {
            if(_combo[i] != 0) {
                if (highestIdx == -1)
                    highestIdx = i;
                _comboborad[i]->SetVisible(true);
            }
            else
                _comboborad[i]->SetVisible(false);
        }
    }
    _comboborad[0]->SetVisible(true);
}


int Combo::GetCombo() {
    conum=0;
    for (int i = 0; i < 3; i++) {
        conum+=_combo[i]*pow(10,i);
    }
    return conum;
}
