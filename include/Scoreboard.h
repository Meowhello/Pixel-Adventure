//
// Created by x3052 on 2025/4/4.
//

#ifndef SCOREBORAD_H
#define SCOREBORAD_H
#include "Number.h"

class Scoreboard: public Util::GameObject {
public:
    Scoreboard(int, int);
    ~Scoreboard() = default;

    void Show();
    void SetScore(int);
    void AddScore(int);
    void SetVisible(bool visible);
    void ResetScore();
    int GetScore();

private:
    void UpdateScoreboard();
    std::vector<int> _score = std::vector<int>(8, 0);
    std::vector<std::shared_ptr<Number>> _scoreborad  = std::vector<std::shared_ptr<Number>>();
};

#endif //SCOREBORAD_H
