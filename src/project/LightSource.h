//
// Created by majav on 01/12/2022.
//
#pragma once
#include <ppgso/ppgso.h>

#include "Object.h"
#ifndef PPGSO_LIGHTSOURCE_H
#define PPGSO_LIGHTSOURCE_H

#endif //PPGSO_LIGHTSOURCE_H

class LightSource : public Object {
private:
    // Static resources (Shared between instances)
    std::unique_ptr<ppgso::Mesh> mesh;
    std::unique_ptr<ppgso::Shader> shader;
    std::unique_ptr<ppgso::Texture> texture;



public:
    float type;
    glm::vec3 color = {1, 1, 1};
    glm::vec3 direction = {0, 0, 0};
    float brightness = 3.0f;
    /*!
     * Create a new player
     */
    LightSource(glm::vec3 position, float scale, glm::vec3 color, float brightness);
    LightSource(glm::vec3 position, glm::vec3 direction,  float scale, glm::vec3 color, float brightness);
    void randomizeColor();
    void setColor(const std::string& colorName);
    void setColor(glm::vec3 colorName);
    glm::vec3 returnColor(const std::string& colorName);
    glm::vec3 randomColor();
    /*!
     * Update player position considering keyboard inputs
     * @param scene Scene to update
     * @param dt Time delta
     * @return true to delete the object
     */
    bool update(Scene &scene, float dt) override;

    /*!
     * Render player
     * @param scene Scene to render in
     */
    void render(Scene &scene) override;
};
