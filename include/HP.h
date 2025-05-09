//
// Created by x3052 on 2025/4/25.
//

#ifndef HP_H
#define HP_H
#include "Util/GameObject.hpp"
#include "OsuParser.h"

class HP : public Util::GameObject{
public:
    HP();
    ~HP() = default;
    void hpdrain(int level);
    void restart();
    float Gethp();

    // std::shared_ptr<OsuParser> _osuParser;

private:

};

#endif //HP_H
