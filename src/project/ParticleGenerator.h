//
// Created by madre on 30/11/2022.
//

#ifndef PPGSO_PARTICLEGENERATOR_H
#define PPGSO_PARTICLEGENERATOR_H


#include "glm/vec3.hpp"
#include "Object.h"

class ParticleGenerator final: public Object {
private:
    glm::vec3 tbl = {-100,-100,-100};
    glm::vec3 bcr = {100,100,100};
    int minst = 0;
    int maxst = 5;
    double spawnThreshold = 3;

    double lastSpawnedAgo = 0;

    std::string particleObj;
    std::string particleText;

public:
    ParticleGenerator(glm::vec3 topBackLeft, glm::vec3 bottomCloseRight, int minSpawnTime, int maxSpawnTime,
                      std::string particleObject, std::string particleTexture);

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};


#endif //PPGSO_PARTICLEGENERATOR_H
