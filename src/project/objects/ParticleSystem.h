//
// Created by madre on 3/12/2022.
//

#ifndef PPGSO_PARTICLESYSTEM_H
#define PPGSO_PARTICLESYSTEM_H


#include "src/project/Object.h"
#include "Particle.h"
#include "PureParticle.h"

class ParticleSystem: public Object {
protected:
    std::unique_ptr<ppgso::Texture> texture;
    std::unique_ptr<ppgso::Shader> shader;

    float dragPower = 5;
public:
    ParticleSystem();
    std::vector<PureParticle> particles;

    bool update(Scene &scene, float dt) override;
    void render(Scene &scene) override;
    GLuint VAO, VBO;
    int amount = 10000;


    void respawnParticle(PureParticle &particle, glm::vec3 offset);
    glm::vec3 position = {0,0,0};
    unsigned int firstUnusedParticle();
};


#endif //PPGSO_PARTICLESYSTEM_H
