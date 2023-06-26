//
// Created by madre on 3/12/2022.
//

#ifndef PPGSO_PUREPARTICLE_H
#define PPGSO_PUREPARTICLE_H


#include "glm/vec3.hpp"
#include "glm/detail/type_vec4.hpp"
#include "glm/vec2.hpp"
#include "src/project/Object.h"

class PureParticle: public Object {
public:
    glm::vec3 ProjectionMatrix = {1,1,1};
    glm::vec3 ViewMatrix = {1,1,1};
    glm::mat4 ModelMatrix{1};

    glm::vec3 Position = {0,0,0};
    glm::vec3 Velocity = {4,2,3};
    glm::vec4 Color = { 128,128,128, 1};
    float     Life;

    PureParticle(glm::vec3 position, glm::vec3 velocity, glm::vec4 color, float life);
    PureParticle();

    void render(Scene &scene) override;
    bool update(Scene &scene, float dt) override;
};


#endif //PPGSO_PUREPARTICLE_H
