//
// Created by x3052 on 2025/4/16.
//

#ifndef SELECTLEVEL_H
#define SELECTLEVEL_H
#include <memory>

#include "Button/LevelButton.h"
#include "Level.h"

class SelectLevel : public Util::GameObject {
public:
    SelectLevel();
    ~SelectLevel() = default;

    std::shared_ptr<Level> Updtate();
private:
    std::vector<std::shared_ptr<Level>> _levelVector;
    std::vector<std::shared_ptr<LevelButton>> _levelButtonVector;
};

#endif //SELECTLEVEL_H
