//
// Created by madre on 8/12/2022.
//

#include "ThrowedItemGenerator.h"
#include "src/project/objects/Drip.h"
#include "Scene.h"

ThrowedItemGenerator::ThrowedItemGenerator(std::vector<glm::vec4> startingPositions) {
    this->coordinatesToThrowFrom = startingPositions;
}

bool ThrowedItemGenerator::update(Scene &scene, float dt) {
    int spawnPoint = rand()% coordinatesToThrowFrom.size();

    generateModelMatrix();

    // Accumulate time
    lastSpawnedAgo += dt;

    // Add object to scene when time reaches certain level
    if (lastSpawnedAgo > spawnThreshold) {
            glm::vec3 initialVelocity;
        if(coordinatesToThrowFrom[spawnPoint].w == 1)
            initialVelocity = {startingVelocity.x, startingVelocity.y, startingVelocity.z};
        else
            initialVelocity = {-startingVelocity.x, startingVelocity.y, startingVelocity.z};

        auto obj = std::make_unique<Drip>(true, initialVelocity);
        obj->position = {coordinatesToThrowFrom[spawnPoint].x,coordinatesToThrowFrom[spawnPoint].y,coordinatesToThrowFrom[spawnPoint].z};

        scene.objects->push_back(move(obj));

        lastSpawnedAgo = 0;
        spawnThreshold = (rand() % (maxst - minst)) + minst;
    }

    return true;
}

void ThrowedItemGenerator::render(Scene &scene) {}
