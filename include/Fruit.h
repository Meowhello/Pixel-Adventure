//
// Created by tfboy on 2025/3/21.
//

#ifndef FRUIT_H
#define FRUIT_H
#include <string>
#include "Core/Drawable.hpp"
#include "Util/Image.hpp"
#include "Util/GameObject.hpp"

class Fruit : public Util::GameObject {
public:
    enum class FruitType {
        Apple,
        Bananas,
        Drop,
        Grapes,
        Orange,
        Pear
    };
    Fruit(FruitType type);

private:
    std::shared_ptr<Util::Image> fruitImages;
    std::vector<std::string> fruitImage;

};
#endif //FRUIT_H
