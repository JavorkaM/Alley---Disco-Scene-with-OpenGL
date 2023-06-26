//
// Created by madrent on 29/11/2022.
//

#include "SceneManager.h"
#include "Scene.h"
#include "src/project/scenes/AlleyScene.h"
#include "src/project/scenes/DiscoScene.h"

std::list<std::unique_ptr<Object>>* SceneManager::getSceneObjects(std::string sceneName) {
    auto selectedScene = SceneManager::getScene(sceneName);
    return (*selectedScene)->getObjects();
}

std::list<std::unique_ptr<LightSource>>* SceneManager::getSceneLights(std::string sceneName) {
    auto selectedScene = SceneManager::getScene(sceneName);
    return (*selectedScene)->getLights();
}


std::unique_ptr<GeneralScene> *SceneManager::getScene(std::string sceneName) {
    auto temp = &scenes.find(sceneName)->second;
    return temp;
}

SceneManager::SceneManager() {
    //Init scenes
    auto alleyScene = std::make_unique<AlleyScene>();
    auto discoScene = std::make_unique<DiscoScene>();


    //Add scenes to available space
    scenes.insert({"disco", std::move(discoScene)});
    scenes.insert({"alley", std::move(alleyScene)});
}

glm::vec3 SceneManager::getCameraPosition(std::string sceneName) {
    auto selectedScene = SceneManager::getScene(sceneName);
    return (*selectedScene)->defaultCameraPos;
}

glm::vec3 SceneManager::getCameraLookAtPosition(std::string sceneName) {
    auto selectedScene = SceneManager::getScene(sceneName);
    return (*selectedScene)->defaultCameraLookAtPos;
}

void SceneManager::init(){
    //TODO init
}
