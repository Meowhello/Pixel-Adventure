//
// Created by x3052 on 2025/4/11.
//

#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H
#include "Background.h"
#include "Level.h"
#include "Util/GameObject.hpp"

class LevelManager: public Util::GameObject {
public:
    LevelManager();
    ~LevelManager() = default;

    std::shared_ptr<Level> SelectLevel(int);
private:
    std::vector<std::shared_ptr<Level>> _levelManager;
    std::shared_ptr<Level> _currentPlay;
};

#endif //LEVELMANAGER_H
