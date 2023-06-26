//
// Created by madre on 8/12/2022.
//

#ifndef PPGSO_THROWEDITEMGENERATOR_H
#define PPGSO_THROWEDITEMGENERATOR_H


#include <vector>
#include "Object.h"

class ThrowedItemGenerator: public Object {
protected:
    std::vector<glm::vec4> coordinatesToThrowFrom; //x,y,z and last is throw direction FROM left (1) or right (-1)
    const float gravity = -9.81;
    glm::vec3 startingVelocity = {2,3,0};

    int minst = 0;
    int maxst = 5;
    double spawnThreshold = 3;

    double lastSpawnedAgo = 0;
public:
    explicit ThrowedItemGenerator(std::vector<glm::vec4> startingPositions);
    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;
};


#endif //PPGSO_THROWEDITEMGENERATOR_H
