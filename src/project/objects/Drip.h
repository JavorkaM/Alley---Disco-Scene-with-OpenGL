//
// Created by madre on 4/12/2022.
//

#ifndef PPGSO_DRIP_H
#define PPGSO_DRIP_H

#include <ppgso/ppgso.h>
#include "src/project/Object.h"

class Drip: public Object {
private:
    std::unique_ptr<ppgso::Mesh> mesh;
    std::unique_ptr<ppgso::Shader> shader;
    std::unique_ptr<ppgso::Texture> texture;

    const float gravity = -9.81;
    glm::vec3 velocity = {0,3,0};
    glm::vec3 color = {0.0001, 0.189, 0.145};
    bool shouldBounce = false;
    bool shouldMove = true;
public:
    Drip(bool shouldBounce);
    Drip(bool shouldBounce, glm::vec3 initialVelocity);
    Drip(bool shouldBounce, glm::vec3 initialVelocity, bool shouldMove);
    void render(Scene &scene) override;
    bool update(Scene &scene, float dt) override;

    void makeItMove();
};


#endif //PPGSO_DRIP_H
