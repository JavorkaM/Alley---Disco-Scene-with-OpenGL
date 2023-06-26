//
// Created by madre on 30/11/2022.
//

#include "Particle.h"

Particle::Particle(const std::string &modelName1, const std::string &textureName1, double timeToLiveInSeconds) : Model(modelName1, textureName1) {
    ttl = timeToLiveInSeconds;
}

bool Particle::update(Scene &scene, float dt) {
    generateModelMatrix();

    ttl -= dt;

    return ttl > 0;
}