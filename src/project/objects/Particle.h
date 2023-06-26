//
// Created by madre on 30/11/2022.
//

#ifndef PPGSO_PARTICLE_H
#define PPGSO_PARTICLE_H


#include "src/project/Model.h"

class Particle final: public Model {
private:
    double ttl = 0;
public:
    Particle(const std::string &modelName1, const std::string &textureName1, double timeToLive);
    bool update(Scene &scene, float dt) override;
};


#endif //PPGSO_PARTICLE_H
