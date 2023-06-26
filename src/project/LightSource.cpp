//
// Created by majav on 01/12/2022.
//
#include "LightSource.h"
#include "Scene.h"

#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>

std::string COLORS[] = {"RED",
                   "ORANGE",
                   "YELLOW",
                   "LIME",
                   "GREEN",
                   "CYAN",
                   "BLUE",
                   "NAVY",
                   "PURPLE",
                   "PINK",
                   "BLACK",
                   "WHITE"
};
int colorCount = 12;


// shared resources
LightSource::LightSource(glm::vec3 position,float scale, glm::vec3 color, float brightness) {
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("sphere.obj");
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("white.bmp"));

    this->type = 0;
    this->position = position;
    this->scale *= scale;
    this->color = color;
    this->brightness = brightness;
}
LightSource::LightSource(glm::vec3 position,glm::vec3 direction,float scale, glm::vec3 color, float brightness) {
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("sphere.obj");
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("white.bmp"));

    this->type = 1;
    this->position = position;
    this->direction = direction;
    this->scale *= scale;
    this->color = color;
    this->brightness = brightness;
}

bool LightSource::update(Scene &scene, float dt) {
    generateModelMatrix();
    return true;
}

void LightSource::render(Scene &scene) {
    shader->use();

    // Set up light
    shader->setUniform("LightDirection", scene.lightDirection);

    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);

    shader->setUniform("OverallColor", color);

    mesh->render();
}


void LightSource::setColor(const std::string& colorName) {
    this->color = returnColor(colorName);
}
void LightSource::setColor(glm::vec3 colorName) {
    this->color = colorName;
}
void LightSource::randomizeColor() {
    setColor(randomColor());
}

glm::vec3 LightSource::returnColor(const std::string& colorName){
    if(colorName == "RED" || colorName == "red" || colorName == "Red" ){
        return {1,0,0};
    }
    if(colorName == "ORANGE" || colorName == "orange" || colorName == "Orange" ){
        return {1,0.5,0};
    }
    if(colorName == "YELLOW" || colorName == "yellow" || colorName == "Yellow" ){
        return {1,1,0};
    }
    if(colorName == "LIME" || colorName == "lime" || colorName == "Lime" ){
        return {.5,1,0};
    }
    if(colorName == "GREEN" || colorName == "green" || colorName == "Green" ){
        return {0,1,0};
    }
    if(colorName == "CYAN" || colorName == "cyan" || colorName == "Cyan" ){
        return {0,1,1};
    }
    if(colorName == "BLUE" || colorName == "blue" || colorName == "Blue" ){
        return {0,0,1};
    }
    if(colorName == "NAVY" || colorName == "navy" || colorName == "Navy" ){
        return {0,.5,1};
    }
    if(colorName == "PURPLE" || colorName == "purple" || colorName == "Purple" ){
        return {.5,0,1};
    }
    if(colorName == "PINK" || colorName == "pink" || colorName == "Pink" ){
        return {1,0,1};
    }
    if(colorName == "BLACK" || colorName == "black" || colorName == "Black" ){
        return {0,0,0};
    }
    if(colorName == "WHITE" || colorName == "white" || colorName == "White" ){
        return {1,1,1};
    }

}

glm::vec3 LightSource::randomColor(){
    return returnColor(COLORS[rand() % colorCount]);
}