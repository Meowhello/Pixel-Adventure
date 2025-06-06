//
// Created by tfboy on 2025/5/9.
//

#ifndef FINISH_H
#define FINISH_H
#include "HP.h"
#include "Util/GameObject.hpp"
#include "ResultFloat.h"
#include "ResultInteger.h"
#include "Scoreboard.h"
#include "Button/RetryButton.h"
#include "Button/BackButton.h"
class Ranking : public  Util::GameObject {
public:
    Ranking(){};
    ~Ranking() = default;

    void SetRanking(float accuracy) {

        if (accuracy >= 0.9f) {
            m_Drawable = std::make_shared<Util::Image>(
                (RESOURCE_DIR "/Image/game_sources/ranking-S.png"));
        } else if (accuracy >= 0.8f) {
            m_Drawable = std::make_shared<Util::Image>(
                (RESOURCE_DIR "/Image/game_sources/ranking-A.png"));
        } else if (accuracy >= 0.7f) {
            m_Drawable = std::make_shared<Util::Image>(
                (RESOURCE_DIR "/Image/game_sources/ranking-B.png"));
        } else if (accuracy >= 0.6f) {
            m_Drawable = std::make_shared<Util::Image>(
                (RESOURCE_DIR "/Image/game_sources/ranking-C.png"));
        } else {
            m_Drawable = std::make_shared<Util::Image>(
                (RESOURCE_DIR "/Image/game_sources/ranking-D.png"));
        }
        m_Transform.translation = {430 , 10};
        m_Transform.scale = {0.7, 0.7};
        m_ZIndex = 5;
    }
};

class EndPage : public Util::GameObject {
public:
    EndPage() {
        m_Drawable=std::make_shared<Util::Image>((RESOURCE_DIR "/Image/game_sources/end_page.png"));
        m_Transform.scale = {0.6666667, 0.6666667};
        m_ZIndex=-4;
    }
    ~EndPage() = default;
};

class Finish : public Util::GameObject {
    public:
    struct ResultData {
        size_t score, catchFruits, unCatchFruits, combo;
        float accuracy;
    };
    Finish(std::string);
    ~Finish() = default;

    void SetResult(ResultData);
    int IsButtonClick();

private:
    std::shared_ptr<Scoreboard> _scoreboard;
    std::shared_ptr<ResultInteger> _catchFruit;
    std::shared_ptr<ResultInteger> _unCatchFruit;
    std::shared_ptr<ResultInteger> _combo;
    std::shared_ptr<ResultFloat> _accuracy;
    std::shared_ptr<RetryButton> _retryButton;
    std::shared_ptr<BackButton> _backButton;
    std::shared_ptr<EndPage> _endPage;
    std::shared_ptr<Ranking> _ranking;
};

#endif //FINISH_H
