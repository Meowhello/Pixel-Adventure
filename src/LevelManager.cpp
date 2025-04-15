//
// Created by x3052 on 2025/4/11.
//
#include "LevelManager.h"

LevelManager::LevelManager() {
    _levelManager.push_back(std::make_shared<Level>("Haruhikage", Level::Difficulty::Easy, "../Resources/music/Haruhikage - CRYCHIC.mp3", "../Resources/music/normal-hitclap.wav", ""));
}

std::shared_ptr<Level> LevelManager::SelectLevel(int n) {
    return _levelManager[n];
}
