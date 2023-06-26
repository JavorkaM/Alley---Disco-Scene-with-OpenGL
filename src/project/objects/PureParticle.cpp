//
// Created by madre on 3/12/2022.
//

#include <iostream>
#include "PureParticle.h"

PureParticle::PureParticle(glm::vec3 position, glm::vec3 velocity, glm::vec4 color, float life) {
    this->Position = position;
    this->Velocity = velocity;
    this->Color = color;
    this->Life = life;
    generateModelMatrix();
}

PureParticle::PureParticle() {
    this->Position = { 0, 0, 0};
    this->Velocity = {0,0,0};
    this->Color = {128,128,128,1};
    this->Life = 1;
    generateModelMatrix();
}

bool PureParticle::update(Scene &scene, float dt) {
    generateModelMatrix();

    //std::cout << rotation.x << "/" << rotation.y << "/" << rotation.z << std::endl;

    return true;
}

void PureParticle::render(Scene &scene) {

}


