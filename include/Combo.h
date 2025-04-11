//
// Created by x3052 on 2025/4/9.
//

#ifndef COMBO_H
#define COMBO_H

#include "Util/Image.hpp"
#include "Util/GameObject.hpp"
#include "Number.h"

class Combo: public Util::GameObject {
public:
    Combo();
    ~Combo() = default;

    void Show();
    void AddCombo(int);
    void ResetCombo();
    void UpdateCombo();
    void SetVisible(bool visible);
    int GetCombo();

private:
    std::shared_ptr<Util::Image> _comboImage;
    std::vector<int> _combo = std::vector<int>(3, 0);
    std::vector<std::shared_ptr<Number>> _comboborad  = std::vector<std::shared_ptr<Number>>();
    int _x, _y,conum;
};

#endif //COMBO_H
