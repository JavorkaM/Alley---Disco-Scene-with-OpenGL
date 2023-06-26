//
// Created by madre on 30/11/2022.
//

#ifndef PPGSO_STEVE_H
#define PPGSO_STEVE_H


#include "src/project/Object.h"

class Steve final: public Object {
private:
    glm::vec3 velocity = {3,3,0};
    std::list<std::unique_ptr<Object>> bodyParts;
    bool isStatic = false;
public:
    Steve();
    Steve(bool isStatic);
    void render(Scene &scene);
    bool update(Scene &scene, float time);
    float normalArmScaleY;
    float normalArmPositionY;
    float timePassed;
};


#endif //PPGSO_STEVE_H
