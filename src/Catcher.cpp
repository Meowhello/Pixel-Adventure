//
// Created by tfboy on 2025/3/21.
//
#include "Catcher.h"
#include "Util/Image.hpp"
#include "Util/Input.hpp"

Catcher::Catcher()/*: myImage("../Resources/Image/game_sources/fruit-ryuuta.png") */{
    // position = glm::vec3(0.0f, -0.7f, 0.0f);
    // matrices.m_Model = glm::translate(glm::mat4(1.0f), position);
    // matrices.m_Model = glm::scale(matrices.m_Model, glm::vec3(0.3f, 0.5f, 1.0f));
    // matrices.m_Projection = glm::mat4(1.0f);
    moveSpeed = 15;
    direction = true;
    m_Drawable=std::make_shared<Util::Image>(RESOURCE_DIR "/Image/game_sources/fruit-ryuuta.png");
    m_Transform.scale={0.8,0.8};
    m_Transform.translation={0,-230};
    m_ZIndex=2;
}

void Catcher::moveLeft() {
    if(direction) {
        m_Transform.scale ={-0.8,0.8};
        direction = false;
    }
    if(Util::Input::IsKeyPressed(Util::Keycode::LSHIFT))
        m_Transform.translation.x -= moveSpeed * 2;
    else
        m_Transform.translation.x -= moveSpeed;
}

void Catcher::moveRight() {
    if(!direction) {
        m_Transform.scale ={0.8,0.8};
        direction = true;
    }

    if(Util::Input::IsKeyPressed(Util::Keycode::LSHIFT))
        m_Transform.translation.x += moveSpeed * 2;
    else
        m_Transform.translation.x += moveSpeed;
}
