//
// Created by tfboy on 2025/3/21.
//
#include "Catcher.h"
#include "Util/Image.hpp"

Catcher::Catcher(): myImage("../Resources/Image/game_sources/fruit-ryuuta.png") {
    position = glm::vec3(0.0f, -0.7f, 0.0f);
    matrices.m_Model = glm::translate(glm::mat4(1.0f), position);
    matrices.m_Model = glm::scale(matrices.m_Model, glm::vec3(0.3f, 0.5f, 1.0f));
    matrices.m_Projection = glm::mat4(1.0f);
    moveSpeed = 0.01f;
}

Catcher::~Catcher() {

}


void Catcher::show() {
    myImage.Draw(matrices);
}

void Catcher::moveLeft() {
    position.x -= moveSpeed;
    matrices.m_Model = glm::translate(glm::mat4(1.0f), position) *
                       glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.5f, 1.0f));
}

void Catcher::moveRight() {
    position.x += moveSpeed;
    matrices.m_Model = glm::translate(glm::mat4(1.0f), position) *
                       glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.5f, 1.0f));
}
