//
// Created by tfboy on 2025/3/21.
//
#include "Fruit.h"

#include <iostream>
#include <ostream>

#include "Util/Image.hpp"
#include <stdlib.h>
#include <time.h>

Fruit::Fruit(FruitType type){
    std::string filepath;
    switch (type) {
        case FruitType::Apple:
            filepath = (RESOURCE_DIR "/Image/game_sources/fruit-apple-overlay.png");
        break;
        case FruitType::Bananas:
            filepath = (RESOURCE_DIR "/Image/game_sources/fruit-bananas-overlay.png");
        break;
        case FruitType::Drop:
            filepath = (RESOURCE_DIR "/Image/game_sources/fruit-drop-overlay.png");
        break;
        case FruitType::Grapes:
            filepath = (RESOURCE_DIR "/Image/game_sources/fruit-grapes-overlay.png");
        break;
        case FruitType::Orange:
            filepath = (RESOURCE_DIR "/Image/game_sources/fruit-orange-overlay.png");
        break;
        case FruitType::Pear:
            filepath = (RESOURCE_DIR "/Image/game_sources/fruit-pear-overlay.png");
        break;
    }
    m_Drawable = std::make_shared<Util::Image>(filepath);
    auto randx=rand()%(801)-500;
    // std::cout << randx << std::endl;
    m_Transform.translation = {randx, 400}; //畫面頂部
    m_ZIndex=1;
};