//
// Created by madre on 29/11/2022.
//

#include "DiscoScene.h"
#include "src/project/characters/Steve.h"
#include "src/project/objects/Duck.h"
#include "src/project/objects/Particle.h"
#include "src/project/ParticleGenerator.h"
#include "src/project/objects/ParticleSystem.h"
#include "src/project/objects/Cube.h"
#include "src/project/objects/Drip.h"
#include "src/project/objects/Floor.h"

DiscoScene::DiscoScene() {
    /*===ReflectorLights===*/
    auto leftRecflectorLight_obj = std::make_unique<LightSource>( glm::vec3(18, 4.2, -18),2.3,glm::vec3(1,0,0), .5);
    objects.push_back(std::move(leftRecflectorLight_obj));
    auto leftRecflectorLight = std::make_unique<LightSource>( glm::vec3(18, 4.2, -18),2.3,glm::vec3(1,0,0), .5);
    lights.push_back(std::move(leftRecflectorLight));
    auto leftRecflectorLightSpot = std::make_unique<LightSource>( glm::vec3(18, 4.2, -18), glm::vec3( -1,-1,1 ), 2.3 ,glm::vec3(1,0,0), 3);
    lights.push_back(std::move(leftRecflectorLightSpot));

    auto rightRecflectorLight_obj = std::make_unique<LightSource>( glm::vec3(-18, 4.2, -18),2.3,glm::vec3(0,1,0), .5);
    objects.push_back(std::move(rightRecflectorLight_obj));
    auto rightRecflectorLight = std::make_unique<LightSource>( glm::vec3(-18, 4.2, -18),2.3,glm::vec3(0,1,0), .5);
    lights.push_back(std::move(rightRecflectorLight));
    auto rightRecflectorLightSpot = std::make_unique<LightSource>( glm::vec3(-18, 4.2, -18), glm::vec3( 1,-1,1 ), 2.3 ,glm::vec3(0,1,0), 3);
    lights.push_back(std::move(rightRecflectorLightSpot));

    auto middleRecflectorLight_obj = std::make_unique<LightSource>( glm::vec3(0, 4.4, 20.5),2.3,glm::vec3(0,0,1), .5);
    objects.push_back(std::move(middleRecflectorLight_obj));
    auto middleRecflectorLight = std::make_unique<LightSource>( glm::vec3(0, 4.4, 20.5),2.3,glm::vec3(0,0,1), .5);
    lights.push_back(std::move(middleRecflectorLight));
    auto middleRecflectorLightSpot = std::make_unique<LightSource>( glm::vec3(0, 4.4, 20.5), glm::vec3( 0,-1 * 0.9,-1 ), 2.3 ,glm::vec3(0,0,1), 3);
    lights.push_back(std::move(middleRecflectorLightSpot));

    auto man1 = std::make_unique<Model>("benceParty.obj","benceParty.bmp");

    man1->position.x += -21.4321;
    man1->position.y += -19;
    man1->position.z += -3.19529;

    man1->rotation.z += - ppgso::PI /2;

    man1->scale *= 1;

    objects.push_back(move(man1));

    auto bartender = std::make_unique<Model>("barman.obj","barman.bmp");

    bartender->position = {22.3,-19,5};

    bartender->rotation.z += + ppgso::PI /2;

    bartender->scale *= 10 * 0.6;

    objects.push_back(move(bartender));


    /*===House structure===*/
    auto floor = std::make_unique<Model>("cube.obj", "woodenFloor.bmp");
    floor->scale = {50,1,50};
    floor->position = {0, -20, 0};
    objects.push_back(std::move(floor));

    auto backWall = std::make_unique<Model>("cube.obj", "whiteBrickWall.bmp");
    backWall->scale = {50,50,1};
    backWall->position = {0, 5, -25};
    objects.push_back(std::move(backWall));

    auto frontWall = std::make_unique<Model>("cube.obj", "whiteBrickWall.bmp");
    frontWall->scale = {50,50,1};
    frontWall->position = {0, 5, 25};
    objects.push_back(std::move(frontWall));

    auto leftWall = std::make_unique<Model>("cube.obj", "whiteBrickWall.bmp");
    leftWall->scale = {1,50,50};
    leftWall->position = {-25, 5, 0};
    objects.push_back(std::move(leftWall));


    auto rightWall = std::make_unique<Model>("cube.obj", "whiteBrickWall.bmp");
    rightWall->scale = {1,50,50};
    rightWall->position = {25, 5, 0};
    objects.push_back(std::move(rightWall));

    auto topLeft = std::make_unique<Model>("cube.obj", "garbageBin.bmp");
    topLeft->scale = {50,1,50};
    topLeft->position = {-12, 18, 0};
    topLeft->rotation.y = ppgso::PI/4;
    objects.push_back(std::move(topLeft));

    auto topRight = std::make_unique<Model>("cube.obj", "garbageBin.bmp");
    topRight->scale = {50,1,50};
    topRight->position = {12, 18, 0};
    topRight->rotation.y = -(ppgso::PI/4);
    objects.push_back(std::move(topRight));

    /*===Reflectors===*/
    auto rightRecflectorPole = std::make_unique<Model>("cube.obj", "garbageBin.bmp");
    rightRecflectorPole->scale = {1,30,1};
    rightRecflectorPole->position = {-20, -10, -20};
    objects.push_back(std::move(rightRecflectorPole));
    auto rightRecflector = std::make_unique<Model>("reflector.obj", "reflector.bmp");
    rightRecflector->scale = {15,15,15};
    rightRecflector->position = {-20, 2, -20};
    rightRecflector->rotation.z = ppgso::PI/4;
    rightRecflector->rotation.x = ppgso::PI/4;
    objects.push_back(std::move(rightRecflector));

    auto leftRecflectorPole = std::make_unique<Model>("cube.obj", "garbageBin.bmp");
    leftRecflectorPole->scale = {1,30,1};
    leftRecflectorPole->position = {20, -10, -20};
    objects.push_back(std::move(leftRecflectorPole));
    auto leftReflector = std::make_unique<Model>("reflector.obj", "reflector.bmp");
    leftReflector->scale = {15,15,15};
    leftReflector->position = {20, 2, -20};
    leftReflector->rotation.z = - ppgso::PI/4;
    leftReflector->rotation.x = ppgso::PI/4;
    objects.push_back(std::move(leftReflector));

    auto middleRecflectorPole = std::make_unique<Model>("cube.obj", "garbageBin.bmp");
    middleRecflectorPole->scale = {1,30,1};
    middleRecflectorPole->position = {0, -10, 22};
    objects.push_back(std::move(middleRecflectorPole));
    auto middleReflector = std::make_unique<Model>("reflector.obj", "reflector.bmp");
    middleReflector->scale = {15,15,15};
    middleReflector->position = {0, 2, 23};
    middleReflector->rotation.z = - ppgso::PI;
    middleReflector->rotation.x = (ppgso::PI/4) * 0.9f;
    objects.push_back(std::move(middleReflector));


    /*===Characters===*/
    auto steve = std::make_unique<Steve>();
    steve->position = {10,0,-10};
    steve->scale = {2,2,2};
    steve->rotation.z = ppgso::PI / 4;
    objects.push_back(std::move(steve));

    auto steve2 = std::make_unique<Steve>();
    steve2->position = {-5,0,-10};
    steve2->scale = {2.5,2.5,2.5};
    steve2->rotation.z = ppgso::PI / 3;
    objects.push_back(std::move(steve2));



    /*===Speakers===*/
    auto speaker = std::make_unique<Model>("speaker.obj","speaker.bmp");
    speaker->position = {-22,-10,-22};
    speaker->scale = {0.02,0.02,0.02};
    speaker->rotation.z = ppgso::PI / 4;
    objects.push_back(std::move(speaker));

    auto spaker2 = std::make_unique<Model>("speaker.obj","speaker.bmp");
    spaker2->position = {22,-10,-22};
    spaker2->scale = {0.02,0.02,0.02};
    spaker2->rotation.z = -ppgso::PI / 4;
    objects.push_back(std::move(spaker2));

    /*===Bar===*/
    auto bar = std::make_unique<Model>("bar.obj","wood2.bmp");
    bar->position = {17,-16,5};
    bar->scale = {2.5,2.5,2.5};
    bar->rotation.z = -1.5;
    objects.push_back(std::move(bar));

    /*===Objects===*/
    /*auto bottle = std::make_unique<Model>("bottle.obj","stars.bmp");
    bottle->position = {17,-13,7.4};
    bottle->scale = {0.08,0.1,0.08};
    objects.push_back(std::move(bottle));*/

    auto dripBottle = std::make_unique<Drip>(true, glm::vec3{0,2,4}, false);
    dripBottle->position = {17,-13, 10.1};
    objects.push_back(std::move(dripBottle));


    auto cup = std::make_unique<Model>("cup.obj","cup.bmp");
    cup->position = {15.5,-12.5,4.4};
    cup->scale = {0.1,0.2,0.1};
    cup->rotation.z = -1.5;
    objects.push_back(std::move(cup));
}