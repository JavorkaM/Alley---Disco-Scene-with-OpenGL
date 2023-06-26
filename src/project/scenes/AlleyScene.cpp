//
// Created by madre on 29/11/2022.
//

#include "AlleyScene.h"
#include "src/project/Model.h"
#include "src/project/objects/Cube.h"
#include "src/project/LightSource.h"
#include "src/project/objects/Floor.h"
#include "src/project/ThrowedItemGenerator.h"
#include "src/project/objects/ParticleSystem.h"

AlleyScene::AlleyScene() {

    auto benceBouncer = std::make_unique<Model>("benceBouncer.obj","benceBouncer.bmp");

    benceBouncer->position.x += -65;
    benceBouncer->position.y += -20;
    benceBouncer->position.z += -333;

    benceBouncer->rotation.z += ppgso::PI /2 - ppgso::PI*0.15f;

    benceBouncer->scale *= 10;

    objects.push_back(move(benceBouncer));

    auto benceMoving = std::make_unique<Model>("marci.obj","marci.bmp");

    benceMoving->position.x += -65;
    benceMoving->position.y += -20;
    benceMoving->position.z += -333;

    benceMoving->rotation.z += 3*ppgso::PI /2;

    benceMoving->scale *= 10;

    objects.push_back(move(benceMoving));


    auto fire1 = std::make_unique<Model>("fire.obj","fire.bmp");

    fire1->position.x += 0;
    fire1->position.y += -20;
    fire1->position.z += -110;

    fire1->rotation.z += - ppgso::PI*0.1f;

    fire1->scale *= 10;

    objects.push_back(move(fire1));

    auto fire2 = std::make_unique<Model>("marci.obj","marci.bmp");

    fire2->position.x += -29.57;
    fire2->position.y += -20;
    fire2->position.z += -127.244;

    fire2->rotation.z += ppgso::PI/2;

    fire2->scale *= 10;

    objects.push_back(move(fire2));

    auto group1 = std::make_unique<Model>("marci.obj","marci.bmp");

    group1->position.x += 17;
    group1->position.y += -20;
    group1->position.z += -247.616;

    //group1->rotation.z += ppgso::PI;

    group1->scale *= 10;

    objects.push_back(move(group1));

    auto group2 = std::make_unique<Model>("emma.obj","emma2.bmp");

    group2->position.x += 10;
    group2->position.y += -20;
    group2->position.z += -256.616;

    group2->rotation.z += ppgso::PI /2;

    group2->scale *= 10 * 1.2;

    objects.push_back(move(group2));


    auto group3 = std::make_unique<Model>("benceCasual.obj","benceCasual.bmp");

    group3->position.x += 17;
    group3->position.y += -20;
    group3->position.z += -265.616;

    group3->rotation.z += ppgso::PI/2 ;

    group3->scale *= 10.2;

    objects.push_back(move(group3));


    // Add garbage bin
    //needs 24bit depth texture, garbageBin.bmp is that, but it doesn't accept it
    auto garbageBin = std::make_unique<Model>("garbageBin.obj", "brass2.bmp");
    garbageBin->position.x = -3;
    garbageBin->scale *= 0.17;
    garbageBin->scale.x *= 0.7;
    garbageBin->scale.y *= 0.9;
    garbageBin->scale.z *= 0.7;


    garbageBin->position.x += 0;
    garbageBin->position.y += -20;
    garbageBin->position.z += -100;

    objects.push_back(move(garbageBin));

    auto ps1 = std::make_unique<ParticleSystem>();
    ps1->position = {-4, -11, -101};
    objects.push_back(move(ps1));

    auto garbageBin2 = std::make_unique<Model>("garbageBin.obj", "brass2.bmp");
    garbageBin2->scale *= 0.17;
    garbageBin2->scale.x *= 0.7;
    garbageBin2->scale.y *= 0.9;
    garbageBin2->scale.z *= 0.7;

    garbageBin2->position.x += -65;
    garbageBin2->position.y += -20;
    garbageBin2->position.z += -342;
    objects.push_back(move(garbageBin2));

    // Add alleyHouse1
    auto alleyHouse = std::make_unique<Model>("alleyHouse1.obj", "alleyHouse1.bmp");
    alleyHouse->scale /= 2;
    alleyHouse->position.x += -53;
    alleyHouse->position.y += -20;
    alleyHouse->position.z += -100;

    alleyHouse->rotation.x = 0;
    alleyHouse->rotation.y = 0;
    alleyHouse->rotation.z = ppgso::PI;

    objects.push_back(move(alleyHouse));

    // Add alleyHouse
    auto alleyHouse_2 = std::make_unique<Model>("alleyHouse1.obj", "alleyHouse1.bmp");
    alleyHouse_2->scale /= 2;
    alleyHouse_2->position.x += 40;
    alleyHouse_2->position.y += -20;
    alleyHouse_2->position.z += 0;

    alleyHouse_2->rotation.x = 0;
    alleyHouse_2->rotation.y = 0;
    alleyHouse_2->rotation.z = 3* ppgso::PI /2;

    alleyHouse_2->position.z = -100;
    objects.push_back(move(alleyHouse_2));

    // Add alleyHouse
    auto alleyHouse_3 = std::make_unique<Model>("alleyHouse1.obj", "alleyHouse1.bmp");
    alleyHouse_3->scale /= 2;
    alleyHouse_3->position.x += -53;
    alleyHouse_3->position.y += -20;
    alleyHouse_3->position.z += -170;

    alleyHouse_3->rotation.x = 0;
    alleyHouse_3->rotation.y = 0;
    alleyHouse_3->rotation.z = 3* ppgso::PI /2;

    objects.push_back(move(alleyHouse_3));

    // Add alleyHouse
    auto alleyHouse_4 = std::make_unique<Model>("alleyHouse1.obj", "alleyHouse1.bmp");
    alleyHouse_4->scale /= 2;
    alleyHouse_4->position.x += 40;
    alleyHouse_4->position.y += -20;
    alleyHouse_4->position.z += -200;

    alleyHouse_4->rotation.x = 0;
    alleyHouse_4->rotation.y = 0;
    alleyHouse_4->rotation.z = 3* ppgso::PI /2;

    objects.push_back(move(alleyHouse_4));

    // Add alleyHouse
    auto alleyHouse_5 = std::make_unique<Model>("alleyHouse1.obj", "alleyHouse1.bmp");
    alleyHouse_5->scale /= 2;
    alleyHouse_5->position.x += -53;
    alleyHouse_5->position.y += -20;
    alleyHouse_5->position.z += -270;

    alleyHouse_5->rotation.x = 0;
    alleyHouse_5->rotation.y = 0;
    alleyHouse_5->rotation.z = 3* ppgso::PI /2;

    objects.push_back(move(alleyHouse_5));

    auto alleyHouse_6 = std::make_unique<Model>("alleyHouse1.obj", "alleyHouse1.bmp");
    alleyHouse_6->scale /= 2;
    alleyHouse_6->position.x += 57.3;
    alleyHouse_6->position.y += -20;
    alleyHouse_6->position.z += -320;

    alleyHouse_6->rotation.x = 0;
    alleyHouse_6->rotation.y = 0;
    alleyHouse_6->rotation.z = ppgso::PI;

    objects.push_back(move(alleyHouse_6));


    auto alleyHouse_7 = std::make_unique<Model>("alleyHouse1.obj", "alleyHouse1.bmp");
    alleyHouse_7->scale /= 2;
    alleyHouse_7->position.x += -15;
    alleyHouse_7->position.y += -20;
    alleyHouse_7->position.z += -359;

    alleyHouse_7->rotation.x = 0;
    alleyHouse_7->rotation.y = 0;
    //alleyHouse_7->rotation.z = - ppgso::PI/2;
    objects.push_back(move(alleyHouse_7));

    auto arrow = std::make_unique<Model>("arrow.obj", "red.bmp");

    arrow->scale /= 2;
    arrow->position.x += 10;
    arrow->position.y += 25;
    arrow->position.z += -340;

    arrow->rotation.x = ppgso::PI/2;

    arrow->materialProperties.x = 128;
    arrow->materialProperties.y = 2;
    arrow->materialProperties.z = 10;
    objects.push_back(move(arrow));

    /*auto light_neon1 = std::make_unique<LightSource>( glm::vec3(12,25,-339),8,glm::vec3(1,.19,.19), 1);
    lights.push_back(std::move(light_neon1));
    auto light_neon2 = std::make_unique<LightSource>( glm::vec3(0,25,-339),8,glm::vec3(1,.19,.19), 1);
    lights.push_back(std::move(light_neon2));*/

    auto light_neon1 = std::make_unique<LightSource>( glm::vec3(12,25,-339),8,glm::vec3(0,1,1), 1);
    lights.push_back(std::move(light_neon1));
    auto light_neon2 = std::make_unique<LightSource>( glm::vec3(0,25,-339),8,glm::vec3(0,1,1), 1);
    lights.push_back(std::move(light_neon2));


    auto container = std::make_unique<Model>("container.obj", "container.bmp");
    container->position = glm::vec3(-105,-25,-330);
    container -> scale *= 0.2;
    container -> scale.y *= 2;

    container->materialProperties.x = 16;
    container->materialProperties.y *= 0.5;
    container->materialProperties.z *= 0.5;

    container->rotation.z = ppgso::PI /2;

    objects.push_back(move(container));

    auto door = std::make_unique<Floor>("cube.obj","door.bmp");
    door->position.x += -68;
    door->position.y += -9;
    door->position.z += -316;

    door->scale *= 10;

    door->scale.x *= 0.05;
    door->scale.y *= 4;
    door->scale.z *= 1.8;

    door->rotation.z = ppgso::PI /2.4f;
    objects.push_back(move(door));


    auto doorway = std::make_unique<Floor>("cube.obj","doorway.bmp");
    doorway->position.x += -74.8;
    doorway->position.y += -9;
    doorway->position.z += -323;

    doorway->scale *= 10;

    doorway->scale.x *= 0.05;
    doorway->scale.y *= 4;
    doorway->scale.z *= 1.3;


    objects.push_back(move(doorway));


    auto barrier1 = std::make_unique<Model>("barrier.obj", "metal.bmp");
    barrier1->scale *= 1.6 ;
    barrier1->position.x += 23;
    barrier1->position.y += -11;
    barrier1->position.z += -143;

    barrier1->materialProperties.x *= 2;
    barrier1->materialProperties.z *= 2;

    objects.push_back(move(barrier1));

    auto barrier2 = std::make_unique<Model>("barrier.obj", "metal.bmp");
    barrier2 ->scale *= 1.15 ;
    barrier2 ->position.x += -15;
    barrier2 ->position.y += -13.2;
    barrier2 ->position.z += -119.4;

    barrier2 ->materialProperties.x *= 2;
    barrier2 ->materialProperties.z *= 2;

    objects.push_back(move(barrier2 ));


    auto barrier3 = std::make_unique<Model>("barrier.obj", "metal.bmp");
    barrier3 ->scale *= 2 ;
    barrier3 ->position.x += -30;
    barrier3 ->position.y += -8.8;
    barrier3 ->position.z += -235;

    barrier3 ->materialProperties.x *= 2;
    barrier3 ->materialProperties.z *= 2;

    objects.push_back(move(barrier3 ));


    auto barrier4 = std::make_unique<Model>("barrier.obj", "metal.bmp");
    barrier4 ->scale *= 1.5 ;
    barrier4->position.x += 27;
    barrier4->position.y += -11.5;
    barrier4->position.z += -261.5;

    barrier4 ->materialProperties.x *= 2;
    barrier4 ->materialProperties.z *= 2;

    objects.push_back(move(barrier4 ));





    auto pavement = std::make_unique<Floor>("cube.obj","pavingstoneLong.bmp");
    pavement->position.x += 0;
    pavement->position.y += -20;
    pavement->position.z += -200;

    pavement->scale.x *= 50;
    pavement->scale.y /= 20;
    pavement->scale.z *= 400;

    //pavement->setMaterialProperties(256,2,2);

    //pavement->rotation.x = - ppgso::PI /2;    // PITCH
    //pavement->rotation.y = ppgso::PI /2;    // vertical - ROLL
    //pavement->rotation.z = ppgso::PI /2;  // horizontal - YAW
    objects.push_back(move(pavement));

    auto pavement2 = std::make_unique<Floor>("cube.obj","pavingstoneLong.bmp");
    pavement2->position.x += 50;
    pavement2->position.y -= 20;
    pavement2->position.z += -200;

    pavement2->scale.x *= 50;
    pavement2->scale.y /= 20;
    pavement2->scale.z *= 400;

    objects.push_back(move(pavement2));

    auto pavement3 = std::make_unique<Floor>("cube.obj","pavingstoneLong.bmp");
    pavement3->position.x += -50;
    pavement3->position.y -= 20;
    pavement3->position.z += -200;

    pavement3->scale.x *= 50;
    pavement3->scale.y /= 20;
    pavement3->scale.z *= 400;

    objects.push_back(move(pavement3));

    std::vector<glm::vec4> spawnPoints;
    spawnPoints.emplace_back(-7,40,-85,1);
    spawnPoints.emplace_back(-7,38,-106,1);
    spawnPoints.emplace_back(-7,38,-183,1);
    auto throwedItemgenerator = std::make_unique<ThrowedItemGenerator>(spawnPoints);
    objects.push_back(move(throwedItemgenerator));

    auto light_fire = std::make_unique<LightSource>( glm::vec3(-3,-11,-100),5,glm::vec3(.88,.34,.13), 1);
    auto light_fire_obj = std::make_unique<LightSource>(glm::vec3(-3,-11,-100),4.5,glm::vec3(.88,.34,.13), 1);
    objects.push_back((std::move(light_fire_obj)));
    lights.push_back(std::move(light_fire));


    auto lightPole1 = std::make_unique<Model>("LightPole.obj", "LightPole.bmp");
    lightPole1->scale *= 2;
    lightPole1->position.x += 30;
    lightPole1->position.y += 4;
    lightPole1->position.z += -150;
    lightPole1->rotation.z = ppgso::PI /2;
    objects.push_back(move(lightPole1));

    auto light_lightPole1_point = std::make_unique<LightSource>( glm::vec3(20,28,-150),1,glm::vec3(1,.9,.57), 1);
    auto light_lightPole1_spot = std::make_unique<LightSource>( glm::vec3(20,28,-150), glm::vec3(0,-1,0), 1, glm::vec3(1,.9,.57),5);
    auto light_lightPole1_obj = std::make_unique<LightSource>( glm::vec3(20,28,-150),1,glm::vec3(1,.9,.57), 1);
    lights.push_back(std::move(light_lightPole1_point));
    lights.push_back(std::move(light_lightPole1_spot));
    objects.push_back((std::move(light_lightPole1_obj)));


    auto lightPole2 = std::make_unique<Model>("LightPole.obj", "LightPole.bmp");
    lightPole2->scale *= 2;
    lightPole2->position.x += 30;
    lightPole2->position.y += 4;
    lightPole2->position.z += -260;
    lightPole2->rotation.z = ppgso::PI /2;
    objects.push_back(move(lightPole2));

    auto light_lightPole2_point = std::make_unique<LightSource>( glm::vec3(20,28,-260),2,glm::vec3(1,.9,.57), 1);
    auto light_lightPole2_spot = std::make_unique<LightSource>( glm::vec3(20,28,-260), glm::vec3(0,-1,0), 1, glm::vec3(1,.9,.57),5);
    auto light_lightPole2_obj = std::make_unique<LightSource>( glm::vec3(20,28,-260),1,glm::vec3(1,.9,.57), 1);
    lights.push_back(std::move(light_lightPole2_point));
    lights.push_back(std::move(light_lightPole2_spot));
    objects.push_back((std::move(light_lightPole2_obj)));


    auto lightPole3 = std::make_unique<Model>("LightPole.obj", "LightPole.bmp");
    lightPole3->scale *= 2;
    lightPole3->position.x += -22;
    lightPole3->position.y += 4;
    lightPole3->position.z += -222;
    lightPole3->rotation.z = - ppgso::PI / 2;
    objects.push_back(move(lightPole3));

    auto light_lightPole3_point = std::make_unique<LightSource>( glm::vec3(-22,28,-222),2,glm::vec3(1,.9,.57), 1);
    auto light_lightPole3_spot = std::make_unique<LightSource>( glm::vec3(-22,28,-222), glm::vec3(0,-1,0), 1, glm::vec3(1,.9,.57),5);
    auto light_lightPole3_obj = std::make_unique<LightSource>( glm::vec3(-22,28,-222),1,glm::vec3(1,.9,.57), 1);
    lights.push_back(std::move(light_lightPole3_point));
    lights.push_back(std::move(light_lightPole3_spot));
    objects.push_back((std::move(light_lightPole3_obj)));

    auto lightPole4 = std::make_unique<Model>("LightPole.obj", "LightPole.bmp");
    lightPole4->scale *= 2;
    lightPole4->position.x += -65;
    lightPole4->position.y += 4;
    lightPole4->position.z += -350;

    lightPole4->rotation.z = - ppgso::PI;

    objects.push_back(move(lightPole4));

    auto light_lightPole4_point = std::make_unique<LightSource>( glm::vec3(-65,28,-339),1,glm::vec3(1,.9,.57), 1);
    auto light_lightPole4_spot = std::make_unique<LightSource>( glm::vec3(-65,28,-339), glm::vec3(0,-1,0), 6, glm::vec3(1,.9,.57),5);
    auto light_lightPole4_obj = std::make_unique<LightSource>( glm::vec3(-65,28,-339),1,glm::vec3(1,.9,.57), 1);
    lights.push_back(std::move(light_lightPole4_point));
    lights.push_back(std::move(light_lightPole4_spot));
    objects.push_back((std::move(light_lightPole4_obj)));

}
