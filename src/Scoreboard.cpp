//
// Created by x3052 on 2025/4/4.
//
#include "Scoreboard.h"

Scoreboard::Scoreboard(){
    for (int i = 0; i < 8; i++) {
        auto number = std::make_shared<Scorenumber>();
        number->SetPosition(610 - 35 * i, 320);
        _scoreborad.push_back(number);
        AddChild(number);
    }
}

Scoreboard::~Scoreboard() {
}


void Scoreboard::Show() {
    for(int i = 0; i < 8; i++) {
        _scoreborad[i]->Show();
    }
}

void Scoreboard::AddScore(int delta) {
    int carry = delta;
    for (int i = 0; i < 8 && carry > 0; i++) {
        int sum = _score[i] + carry;
        _score[i] = sum % 10;
        carry = sum / 10;
    }
}

void Scoreboard::UpdateScoreboard() {
    for (int i = 0; i < 8; i++) {
        _scoreborad[i]->UpdateImage(_score[i]);
    }
}
