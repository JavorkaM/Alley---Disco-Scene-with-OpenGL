//
// Created by madre on 4/12/2022.
//

#include "Drip.h"
#include "src/project/Scene.h"
#include "Floor.h"
#include <shaders/phong_vert_glsl_glsl.h>
#include <shaders/phong_frag_glsl_glsl.h>
#include <shaders/color_frag_glsl.h>
#include <shaders/color_vert_glsl.h>

Drip::Drip(bool shouldBounce) {
    this->shouldBounce = shouldBounce;

    //if (!shader) shader = std::make_unique<ppgso::Shader>(phong_vert_glsl_glsl, phong_frag_glsl_glsl);
    if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("sphere.obj");
    if (this->shouldBounce) mesh = std::make_unique<ppgso::Mesh>("bottle.obj");
    //if (!mesh) mesh = std::make_unique<ppgso::Mesh>("waterDrop.obj");
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("water.bmp"));
    //if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("waterDrop.bmp"));

    scale = {2,2,2};
    if (this->shouldBounce)
        scale = {0.1,0.1,0.1};
}

bool Drip::update(Scene &scene, float dt) {
    if(shouldMove){
        this->position.x += this->velocity.x * dt;
        this->position.z += this->velocity.z * dt;
        this->position.y += this->velocity.y * dt;
        this->velocity.y += dt * gravity;
    }

    generateModelMatrix();

    bool hitFloor = false;
    float floorAt = -20;
    /*for ( auto& obj : *scene.objects ) {
        // Ignore self in scene
        if (obj.get() == this)
            continue;

        // We only need to collide with asteroids, ignore other objects
        auto floor = dynamic_cast<Floor*>(obj.get());
        if (!floor) continue;
        floorAt = floor->position.y;

        if (position.y < floor->position.y) {
            hitFloor = true;
            break;
        }
    }*/
    if(position.y < floorAt)
        hitFloor = true;

    if(hitFloor && shouldBounce){
        int newDripParticleCount = rand() % 3 + 2;

        for(int i = 0; i < newDripParticleCount; i++){
            int randXVelocity = rand() % 10 - 5;
            int randZVelocity = rand() % 10 - 5;
            auto newDrop = std::make_unique<Drip>(false);
            newDrop->position = position;
            newDrop->position.y = floorAt + 0.5; //spawn it just above the world floor //TODO change it to the collided object y Coordinate
            newDrop->velocity = { randXVelocity,8,randZVelocity};
            //newDrop1->scale = {0.02,0.02,0.02};
            newDrop->scale = {1,1,1};

            scene.objects->push_back(move(newDrop));
        }
        /*auto newDrop1 = std::make_unique<Drip>(false);
        newDrop1->position = position;
        newDrop1->position.y = floorAt + 0.5; //spawn it just above the world floor //TODO change it to the collided object y Coordinate
        newDrop1->velocity = { 6,8,6};
        //newDrop1->scale = {0.02,0.02,0.02};
        newDrop1->scale = {1,1,1};

        auto newDrop2 = std::make_unique<Drip>(false);
        newDrop2->position = position;
        newDrop2->position.y = floorAt + 0.5;
        newDrop2->velocity = { -6,8,-6};
        //newDrop2->scale = {0.02,0.02,0.02};
        newDrop2->scale = {1,1,1};

        scene.objects->push_back(move(newDrop1));
        scene.objects->push_back(move(newDrop2));
*/
        return false;
    }else if(hitFloor && !shouldBounce)
        return false;

    return true;
}

void Drip::render(Scene &scene) {
    shader->use();

    // Set up light
    //shader->setUniform("LightDirection", scene.lightDirection);

    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("ViewPosition", scene.camera->position);

    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    //shader->setUniform("Texture", *texture);

    shader->setUniform("OverallColor", this->color);

    //shader->setUniform("Lights_count", (float) scene.lights->size());

/*    shader->setUniform("materialShininess", (float) this->materialProperties.x);
    shader->setUniform("materialDiffuse", (float) this->materialProperties.y);
    shader->setUniform("materialSpecular", (float) this->materialProperties.z);

    std::list<std::unique_ptr<LightSource>>::iterator it;
    int i = 0;
    for (it = scene.lights->begin(); it != scene.lights->end(); ++it){
        shader->setUniform("lights[" + std::to_string(i) + "].type", (*it)->type);
        shader->setUniform("lights[" + std::to_string(i) + "].position", (*it)->position);
        shader->setUniform("lights[" + std::to_string(i) + "].color", (*it)->color);
        shader->setUniform("lights[" + std::to_string(i) + "].brightness", (*it)->brightness);
        if((*it)->type == 1) {
            shader->setUniform("lights[" + std::to_string(i) + "].direction", (*it)->direction);
        }
        i++;
    }*/

    mesh->render();
}

Drip::Drip(bool shouldBounce, glm::vec3 initialVelocity): Drip(shouldBounce) {
    this->velocity = initialVelocity;
}

Drip::Drip(bool shouldBounce, glm::vec3 initialVelocity, bool shouldMove): Drip(shouldBounce)  {
    this->velocity = initialVelocity;
    this->shouldMove = shouldMove;
}

void Drip::makeItMove() {
    this->shouldMove = true;
}
