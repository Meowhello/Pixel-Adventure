//
// Created by x3052 on 2025/4/4.
//
#include "Scoreboard.h"

Scoreboard::Scoreboard(int x, int y){
    for (int i = 0; i < 8; i++) {
        auto number = std::make_shared<Number>();
        number->SetPosition(x - 35 * i, y);
        _scoreborad.push_back(number);
        AddChild(number);
    }
}


void Scoreboard::Show() {
    for(int i = 0; i < 8; i++) {
        _scoreborad[i]->Show();
    }
}

void Scoreboard::SetScore(int n) {
    for (int i = 0; i < 8  && n >= 0; i++) {
        _score[i] = n % 10;
        n = n / 10;
    }
    UpdateScoreboard();
}


void Scoreboard::AddScore(int delta) {
    int carry = delta;
    for (int i = 0; i < 8 && carry > 0; i++) {
        int sum = _score[i] + carry;
        _score[i] = sum % 10;
        carry = sum / 10;
    }
    UpdateScoreboard();
}

void Scoreboard::UpdateScoreboard() {
    for (int i = 0; i < 8; i++) {
        _scoreborad[i]->UpdateImage(_score[i]);
    }
}

void Scoreboard::SetVisible(bool visible) {
    for (auto& digit : _scoreborad) {
        digit->SetVisible(visible);
    }
}

void Scoreboard::ResetScore() {
    for (int i = 0; i < 8; i++) {
        _score[i] = 0;
    }
    UpdateScoreboard();
}

int Scoreboard::GetScore() {
    int score = 0;
    for (int i = 0; i < 8; i++) {
        score += _score[i] * static_cast<int>(std::pow(10, i));;
    }
    return score;
}

