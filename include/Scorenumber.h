//
// Created by x3052 on 2025/3/28.
//

#ifndef SCOREBSOARD_H
#define SCOREBSOARD_H

#include "Util/Image.hpp"
#include "Util/GameObject.hpp"

class Scorenumber : public Util::GameObject  {
public:
    Scorenumber();
    ~Scorenumber() = default;

    void Show();
    void UpdateImage(int);
    void SetPosition(int, int);
private:
    std::shared_ptr<Util::Image> _scoreImage;
    int _x, _y;
};


#endif //SCOREBSOARD_H
