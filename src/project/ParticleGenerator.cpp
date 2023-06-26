//
// Created by madre on 30/11/2022.
//

#include <string>
#include <utility>
#include "ParticleGenerator.h"
#include "Scene.h"
#include "src/project/objects/Particle.h"

ParticleGenerator::ParticleGenerator(glm::vec3 topBackLeft, glm::vec3 bottomCloseRight, int minSpawnTime,
                                     int maxSpawnTime, std::string particleObject, std::string particleTexture) {
    tbl = topBackLeft;
    bcr = bottomCloseRight;
    minst = minSpawnTime;
    maxst = maxSpawnTime;
    particleObj = std::move(particleObject);
    particleText = std::move(particleTexture);

    spawnThreshold = (rand() % (maxst- minst)) + minst;
}

bool ParticleGenerator::update(Scene &scene, float dt) {
    generateModelMatrix();

    // Accumulate time
    lastSpawnedAgo += dt;

    // Add object to scene when time reaches certain level
    if (lastSpawnedAgo > spawnThreshold) {
        auto obj = std::make_unique<Particle>(particleObj, particleText, 1); //TODO maybe be able to change how much a particle can live for
        obj->position = position;
        obj->position.x += glm::linearRand(-20.0f, 20.0f);

        scene.objects->push_back(move(obj));

        lastSpawnedAgo = 0;
        spawnThreshold = (rand() % (maxst- minst)) + minst;
    }

    return true;
}

void ParticleGenerator::render(Scene &scene) {
    //this Object is not rendered
}