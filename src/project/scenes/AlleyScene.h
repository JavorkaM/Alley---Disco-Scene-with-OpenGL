//
// Created by madre on 29/11/2022.
//

#ifndef PPGSO_ALLEYSCENE_H
#define PPGSO_ALLEYSCENE_H


#include "GeneralScene.h"

class AlleyScene : public GeneralScene {
protected:
    glm::vec3 defaultCameraPos{-5, -10, 5};
public:
    AlleyScene();
};


#endif //PPGSO_ALLEYSCENE_H
