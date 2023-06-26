//
// Created by madrent on 29/11/2022.
//

#ifndef PPGSO_SCENEMANAGER_H
#define PPGSO_SCENEMANAGER_H

#include <vector>
#include "src/project/scenes/GeneralScene.h"

class SceneManager{
private:
    std::map<std::string, std::unique_ptr<GeneralScene>> scenes;
public:
    SceneManager();
    void init();

    std::list<std::unique_ptr<Object>>* getSceneObjects(std::string sceneName);
    std::list<std::unique_ptr<LightSource>>* getSceneLights(std::string sceneName);

    glm::vec3 getCameraPosition(std::string sceneName);
    glm::vec3 getCameraLookAtPosition(std::string sceneName);

    std::unique_ptr<GeneralScene>* getScene(std::string sceneName);
};

#endif //PPGSO_SCENEMANAGER_H
