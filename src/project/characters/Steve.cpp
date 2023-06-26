//
// Created by madre on 30/11/2022.
//

#include "Steve.h"
#include "src/project/objects/Cube.h"
#include "src/project/Model.h"

Steve::Steve() {
    auto body = std::make_unique<Model>("cube.obj", "stars.bmp");
    auto left_leg = std::make_unique<Model>("cube.obj", "grass.bmp");
    auto right_leg = std::make_unique<Model>("cube.obj","grass.bmp");
    auto left_arm = std::make_unique<Model>("cube.obj","metal.bmp");
    auto right_arm = std::make_unique<Model>("cube.obj","metal.bmp");
    auto head = std::make_unique<Model>("trump.obj", "trump.bmp");

    //z width
    //y height
    //x depth

    body->scale.x /= 2;
    body->scale.y *= 2.2;
    body->scale.z *= 1.5;
    body->position.x = 0;
    body->position.y = 0;
    body->position.z = 0;

    left_leg->scale.x /= 2;
    left_leg->scale.z /= 2;
    left_leg->position.x = 0;
    left_leg->position.y -= 1.5;
    left_leg->position.z -= 0.25;

    right_leg->scale.x /= 2;
    right_leg->scale.z /= 2;
    right_leg->position.x = 0;
    right_leg->position.y -= 1.5;
    right_leg->position.z += 0.25;

    left_arm->scale.x /= 2;
    left_arm->scale.z /= 2;
    left_arm->scale.y *= 1.7;
    left_arm->position.x = 0;
    left_arm->position.y = 0.2;
    left_arm->position.z -= 1.1;

    right_arm->scale.x /= 2;
    right_arm->scale.z /= 2;
    right_arm->scale.y *= 1.7;
    right_arm->position.x = 0;
    right_arm->position.y = 0.2;
    right_arm->position.z += 1.1;

    normalArmScaleY = right_arm->scale.y;
    normalArmPositionY = right_arm->position.y;
    timePassed = 0;

    head->scale.x /= 2;
    head->scale.z /= 2;
    head->scale.y /= 2;
    head->position.y = 1;
    head->rotation.z = - (ppgso::PI / 2);


    bodyParts.push_back(move(body));
    bodyParts.push_back(move(left_leg));
    bodyParts.push_back(move(right_leg));
    bodyParts.push_back(move(left_arm));
    bodyParts.push_back(move(right_arm));
    bodyParts.push_back(move(head));
}

Steve::Steve(bool isStatic):Steve() {
    this->isStatic = isStatic;
}

void Steve::render(Scene &scene) {
    for ( auto& obj : bodyParts )
        obj->render(scene);
}

bool Steve::update(Scene &scene, float dt) {
    //rotation.z += dt/2;
    if(!isStatic){
        position.y += velocity.y * dt * 10;
        //position.x += velocity.x * dt * 10;
        velocity.y -= dt * 10;
        //velocity.x -= dt * 10;


        if(position.y < -15)
            velocity = {3,3,0};
    }
    timePassed += dt*10;
    int x = 0;
    for ( auto& obj : bodyParts ){
        obj->update(scene, dt);
        obj->modelMatrix = modelMatrix * obj->modelMatrix;
        if(x == 3 || x == 4){
            std::cout << dt << std::endl;
            obj->scale.y =  normalArmScaleY * (sin(timePassed) + 2) / 2;
            obj->position.y =  normalArmPositionY * (sin(timePassed) + 2);
            // std::cout << obj->scale.y << std::endl;
        }
        x++;
    }

    generateModelMatrix();

    return true;
}
