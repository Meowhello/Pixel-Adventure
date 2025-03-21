//
// Created by tfboy on 2025/3/21.
//
#include "Fruit.h"
#include "Util/Image.hpp"

Fruit::Fruit(FruitType type){
    std::string filepath;
    switch (type) {
        case FruitType::Apple:
            filepath = (RESOURCE_DIR "/Image/game_sources/fruit-apple.png");
        break;
        case FruitType::Bananas:
            filepath = (RESOURCE_DIR "/Image/game_sources/fruit-bananas.png");
        break;
        case FruitType::Drop:
            filepath = (RESOURCE_DIR "/Image/game_sources/fruit-drop.png");
        break;
        case FruitType::Grapes:
            filepath = (RESOURCE_DIR "/Image/game_sources/fruit-grapes.png");
        break;
        case FruitType::Orange:
            filepath = (RESOURCE_DIR "/Image/game_sources/fruit-orange.png");
        break;
        case FruitType::Pear:
            filepath = (RESOURCE_DIR "/Image/game_sources/fruit-pear.png");
        break;
    }

    m_Drawable = std::make_shared<Util::Image>(filepath);
    m_Transform.translation = {0, 400}; //畫面頂部
};

