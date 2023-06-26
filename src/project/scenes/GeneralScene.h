//
// Created by madrent on 29/11/2022.
//

#ifndef PPGSO_GENERALSCENE_H
#define PPGSO_GENERALSCENE_H

#include "src/project/Object.h"
#include "src/project/LightSource.h."

class GeneralScene {
protected:
    std::list< std::unique_ptr<Object>> objects;

    std::list< std::unique_ptr<LightSource>> lights;
public:
    glm::vec3 defaultCameraPos{-5, 5, 0};
    glm::vec3 defaultCameraLookAtPos{0, 0, 0};
    std::list< std::unique_ptr<Object>>* getObjects();
    std::list< std::unique_ptr<LightSource>>* getLights();
};

#endif //PPGSO_GENERALSCENE_H
