//
// Created by x3052 on 2025/4/11.
//

#ifndef LEVEL_H
#define LEVEL_H

#include "pch.hpp" // IWYU pragma: export
#include "Catcher.h"
#include "Fruit.h"
#include "Scoreboard.h"
#include "Util/Renderer.hpp"
#include "Background.h"
#include "Combo.h"
#include "HP.h"
#include "OsuParser.h"
#include "Button/ContinueButton.h"
#include "Button/RetryButton.h"
#include "Button/BackButton.h"
#include "Util/BGM.hpp"
#include "Util/SFX.hpp"
#include "Finish.h"
#include "OsuParser.h"
#include "../PTSD/example/include/App.hpp"

class Level: public Util::GameObject {
public:
    Level(std::string, const std::string&, const std::string&, const std::string&, std::string );
    ~Level() = default;

    void Initial();
    float Gethp();
    std::string GetBgPaht();
    void Update();
    int  Pause();
    int GameOver();
    Finish::ResultData Finish();
    void End();
    void HandleInput();
    void UpdateFruitSpawning();
    void UpdateFruits();
    void ResumeBGM();
    void ClearState();

    float GetStartTime(){return  _startTimeMs;}
private:
    void SetOverButton(bool);
    void SetPauseButton(bool);
    void UpdateHighestCombo();
    std::string _name;
    std::string _comfigPath;
    std::string _bgPath;

    LevelData       _levelData;
    float           _startTimeMs       = 0;
    float           _runTimeMs         = 0;
    float           _pauseStartTimeMs  = 0;
    float           _totalPauseTimeMs  = 0;
    size_t          _nextIndex         = 0;     // 下一顆水果 index
    int             _approachMs        = 1800;  // 提前量 (可依 AR 動態計算)
    int             _spawnStartY       = 540; // 螢幕最上方以外
    float           _scaleX            = 1.f;   // 座標轉換
    float           _scaleY            = 1.f;
    bool            _isBgmPlay         = false;
    size_t          _catchFruits       = 0;
    size_t          _highestCombo      = 0;

    std::shared_ptr<Util::BGM> _bgm;
    std::shared_ptr<Util::SFX> _sfx;
    std::shared_ptr<OsuParser> _osuParser;

    std::shared_ptr<Catcher> _catcher;
    std::shared_ptr<HP> _hp;
    std::vector<std::shared_ptr<Fruit>> fruits;
    std::shared_ptr<Background> _background;
    std::shared_ptr<Scoreboard> _scoreboard;
    std::shared_ptr<Combo> _combo;
    std::shared_ptr<ContinueButton> _continueButton;
    std::shared_ptr<RetryButton> _retryButton;
    std::shared_ptr<BackButton> _backButton;
};

#endif //LEVEL_H
