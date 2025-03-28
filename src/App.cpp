#include "App.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <typeinfo>
#include "Catcher.h"
#include "Util/Time.hpp"
#include "Fruit.h"
#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");
    // m_Fruit = std::make_shared<Fruit>(Fruit::FruitType::Apple);
    // m_Root.AddChild(m_Fruit);
    m_Catcher = (std::make_shared<Catcher>());
    m_Root.AddChild(m_Catcher);//人物加入m_Root一起畫出來
    m_Background = (std::make_shared<Background>(Background::level::level_1));
    m_Root.AddChild(m_Background);//畫背景
    m_CurrentState = State::UPDATE;
}

void App::Update() {
    
    //TODO: do your things here and delete this line <3

    // m_Root.AddChild(m_Catcher); //人物加入m_Root一起畫出來
    // catcher.show();
    if(Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
        m_Catcher->moveLeft();
    }
    if(Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
        m_Catcher->moveRight();
    }

    // std::vector<std::shared_ptr<Fruit>> fruits; //存放很多水果
    // for (int i = 0; i < 10; i++) {
    static auto lastDrop = Util::Time::GetElapsedTimeMs();
    LOG_DEBUG("{}", Util::Time::GetElapsedTimeMs());
    if(Util::Time::GetElapsedTimeMs() - lastDrop > 1000) { //一秒一個水果
        lastDrop = Util::Time::GetElapsedTimeMs();
        auto rand_num = rand()%6; //隨機水果
        switch (rand_num) {
            case 0:
                fruits.push_back(std::make_shared<Fruit>(Fruit::FruitType::Apple));
            break;
            case 1:
                fruits.push_back(std::make_shared<Fruit>(Fruit::FruitType::Bananas));
            break;
            case 2:
                fruits.push_back(std::make_shared<Fruit>(Fruit::FruitType::Drop));
            break;
            case 3:
                fruits.push_back(std::make_shared<Fruit>(Fruit::FruitType::Grapes));
            break;
            case 4:
                fruits.push_back(std::make_shared<Fruit>(Fruit::FruitType::Orange));
            break;
            case 5:
                fruits.push_back(std::make_shared<Fruit>(Fruit::FruitType::Pear));
            break;
        }
    }

    for (const auto &fruit : fruits) { //水果++
        m_Root.AddChild(fruit);
    }

    static auto combo=0;
    for (int i = 0; i < fruits.size(); i++) { //一起控制所有的水果
        auto position = fruits[i]->m_Transform.translation; //控制 x 和 y
        auto catcherpos=m_Catcher->m_Transform.translation; //人物
        position.y -= 10 ; // 水果下墜
        fruits[i]->m_Transform.translation.y = position.y;
        // std::cout<<"person: ("<<catcherpos.x<<" , "<<catcherpos.y<<")"<<std::endl
        //         <<"fruit: ("<<position.x<<" , "<<position.y<<")"<<std::endl;

        std::cout<<"combo: "<<combo<<std::endl;
        if(abs(position.x-catcherpos.x)<100 && position.y<=-130&& position.y>-220) { //判斷水果觸碰
            fruits[i]->SetVisible(false);
            fruits.erase(fruits.begin());
            combo++;
        }
        else if(position.y<-400) { //判斷水果落地
            fruits[i]->SetVisible(false);
            fruits.erase(fruits.begin());
            combo=0;
        }
    }

    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        // bglevel=std::make_shared<Background>(Background::level::pause);
        m_CurrentState = State::END;
    }
    // if(m_Level==level::pause) {
    //
    // }
    m_Root.Update();
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
