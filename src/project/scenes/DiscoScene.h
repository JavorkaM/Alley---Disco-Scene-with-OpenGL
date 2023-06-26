//
// Created by madre on 29/11/2022.
//

#ifndef PPGSO_DISCOSCENE_H
#define PPGSO_DISCOSCENE_H


#include "GeneralScene.h"

class DiscoScene: public GeneralScene {
protected:
    glm::vec3 defaultCameraPos{-5, -10, 5}; //TODO make it look where it is supposed to
public:
    DiscoScene();
};


#endif //PPGSO_DISCOSCENE_H
