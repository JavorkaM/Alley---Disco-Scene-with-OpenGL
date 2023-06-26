//
// Created by madre on 16/11/2022.
//

#ifndef PPGSO_PROJECT_H
#define PPGSO_PROJECT_H

#include <iostream>
#include <map>
#include <list>


#include <ppgso/ppgso.h>

#include "Scene.h"
#include "src/project/objects/Duck.h"
#include "src/project/objects/Cube.h"
#include "Model.h"
#include "SceneManager.h"
#include "src/project/objects/Drip.h"

#include <shaders/framebuffer_vert_glsl.h>
#include <shaders/framebuffer_frag_glsl.h>

const unsigned int SIZE = 1500;

/*!
 * Custom windows for our simple game
 */
class SceneWindow : public ppgso::Window {
private:
    std::unique_ptr<ppgso::Shader> shader;
    unsigned int fbo;
    unsigned int textureColorbuffer;
    unsigned int rbo;
    unsigned int quadVAO, quadVBO;
    std::string currScene;
    SceneManager scm;
    bool animate = true;
    bool framebufferFilter = false;
    bool lightTimer = false;
    float elapsedTime = 0;


    void initScene() {
        float quadVertices[] = {
                // positions   // texCoords
                -1.0f,  1.0f,  0.0f, 1.0f,
                -1.0f, -1.0f,  0.0f, 0.0f,
                1.0f, -1.0f,  1.0f, 0.0f,

                -1.0f,  1.0f,  0.0f, 1.0f,
                1.0f, -1.0f,  1.0f, 0.0f,
                1.0f,  1.0f,  1.0f, 1.0f
        };

        //Create framebuffer
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        //setup rendering into a texture attached to the framebuffer
        glGenTextures(1, &textureColorbuffer);
        glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SIZE, SIZE/4*3, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

        //create render buffer
        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SIZE, SIZE/4*3);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);


        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);


        // screen quad VAO
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

        scm.init();
        if(scene.objects != nullptr || scene.lights != nullptr) {
            //scene.objects->clear();
            //scene.lights->clear();
        }

        // Create a camera
        auto camera = std::make_unique<Camera>(60.0f, 1.0f, 0.1f, 500.0f);
        camera->position.z = 5.0f;
        camera->position.y = -10.0f;
        camera->position.x = -5.0f;

        scene.camera = move(camera);


        std::string startingScene = "alley"; // Set starting scene here


        scene.lights = (scm.getSceneLights(startingScene));
        scene.objects = (scm.getSceneObjects(startingScene));
        currScene = startingScene;



        //scene.camera->position = scm.getCameraPosition("disco");
        //scene.camera->lookAtPos = scm.getCameraLookAtPosition("disco"); //TODO no idea how to set camera angles
    }

public:
    Scene scene;

    SceneWindow() : Window{"Project screen", SIZE, SIZE/4*3} {
    //SceneWindow() : Window{"Project screen", 1, 1} { //TODO change to this line for fullscreen
        //hideCursor();
        glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

        // Initialize OpenGL state
        // Enable Z-buffer
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        // Enable polygon culling
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        initScene();

        if (!shader) shader = std::make_unique<ppgso::Shader>(framebuffer_vert_glsl, framebuffer_frag_glsl);
        shader->setUniform("Filter", 0.0f);

    }

    void onKey(int key, int scanCode, int action, int mods) override {
        scene.keyboard[key] = action;
        static auto time = (float) glfwGetTime();
        float dt = (float) glfwGetTime() - time;
        time = (float) glfwGetTime();
        // Reset
        if (key == GLFW_KEY_R && action == GLFW_PRESS) {
            initScene();
        }

        // Pause
        if (key == GLFW_KEY_P && action == GLFW_PRESS) {
            animate = !animate;
        }
        if (key == GLFW_KEY_T && action == GLFW_PRESS) {
            if(framebufferFilter) {
                shader->setUniform("Filter", 0.0f);
                framebufferFilter = false;
            }
            else{
                shader->setUniform("Filter", 1.0f);
                framebufferFilter = true;
            }
        }
        if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
                currScene = "alley";
                scene.lights = scm.getSceneLights(currScene);
                scene.objects = scm.getSceneObjects(currScene);
                scene.camera->setToWASD(glm::vec3(5,-10,-5), glm::vec3(5,-10,-6)  );
            }
        if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
                currScene = "disco";
                scene.lights = scm.getSceneLights(currScene);
                scene.objects = scm.getSceneObjects(currScene);
                scene.camera->setToWASD(glm::vec3(-5,-10,5), glm::vec3(-5,-10,4)  );
        }
        if (key == GLFW_KEY_F && action == GLFW_PRESS) {
            if(currScene == "disco"){
                LightSource* model = nullptr;
                LightSource* pointLight = nullptr;
                LightSource* spotLight = nullptr;
                glm::vec3 tempColor = {0,0,0};
                int x = 0;
                int y = 0;
                for (auto it = scene.lights->begin(); it != scene.lights->end(); ++it) {
                    pointLight = dynamic_cast<LightSource*>(it->get());
                    ++it;
                    spotLight = dynamic_cast<LightSource*>(it->get());

                    if (spotLight != nullptr || pointLight != nullptr){
                        tempColor = spotLight->randomColor();

                        spotLight->setColor(tempColor);
                        pointLight->setColor(tempColor);
                        y = 0;
                        for (auto it_o = scene.objects->begin(); it_o != scene.objects->end(); ++it_o) {
                            if(y == (x / 2) ){
                                model = dynamic_cast<LightSource*>(it_o->get());
                                model->color = tempColor;
                            }
                            y++;
                        }

                    }
                    else{
                        std::cout << "Light pointer NULL" << std::endl;
                        exit(5);
                    }
                    x += 2;
                }

            }
        }
        if (key == GLFW_KEY_C && action == GLFW_PRESS) {
            if(currScene == "alley") {

            }
            else {
                if (lightTimer)
                    lightTimer = false;
                else {
                    lightTimer = true;
                }
            }
        }
        if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
            if(currScene == "alley") {
                scene.camera->transitionTo(glm::vec3(2.73634, 82.3505, -324.54), glm::vec3(2.73634, 82.3505, -324.54),
                                           glm::vec3(2.73634, 82.3505, -60.1613), glm::vec3(2.73634, 81.3507, -60.1787),
                                           750);
                int x = 0;
                Model *model = nullptr;
                for (auto it = scene.objects->begin(); it != scene.objects->end(); ++it) {
                    if (x == 1) {
                        model = dynamic_cast<Model *>(it->get());
                        break;
                    }
                    x++;
                }
                if (model != nullptr) {
                    //model->transitionTo(model->position,model->rotation, glm::vec3(model->position.x + 75,model->position.y,model->position.z), glm::vec3(model->rotation.x,model->rotation.y,model->rotation.z - ppgso::PI/2), 100);
                    model->transitionToBezier({
                                                      model->position,
                                                      glm::vec3(-6.66388, model->position.y, -338.536),
                                                      glm::vec3(13.3932, model->position.y, -292.195),
                                                      glm::vec3(9.51575, model->position.y, -197.374),
                                                      glm::vec3(8.82586, model->position.y, -4.41018),
                                              }, glm::vec3(model->rotation.x, model->rotation.y,
                                                           model->rotation.z - (ppgso::PI / 2) * 0.3),
                                              glm::vec3(model->rotation.x, model->rotation.y,
                                                        model->rotation.z - ppgso::PI / 2),
                                              600);

                }
            } else if(currScene == "disco"){
                scene.camera->transitionToBezier(
                        {
                                {-22,  7.5, 3},
                                {-30,  7.5,  -30},
                                {35 , 7.5,  -35},
                                {35 , 7.5 , 35},
                                {-30 , 7.5,  30},
                                {-22,  7.5, 3},
                        }, glm::vec3(-1.56879, 1.18085, 1.9211), glm::vec3(-1.56879, 1.18085, 1.9211), 1200
                );
            }
        }
        if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
            if (currScene == "alley") {
                scene.camera->setToStationary(glm::vec3(10, 0, -80), glm::vec3(-10, -5, -110));
                int x = 0;
                Model *model = nullptr;
                for (auto it = scene.objects->begin(); it != scene.objects->end(); ++it) {
                    if (x == 3) {
                        model = dynamic_cast<Model *>(it->get());
                        break;
                    }
                    x++;
                }
                if (model != nullptr) {
                    //model->transitionTo(model->position,model->rotation, glm::vec3(model->position.x + 75,model->position.y,model->position.z), glm::vec3(model->rotation.x,model->rotation.y,model->rotation.z - ppgso::PI/2), 100);
                    model->transitionToBezier({
                                                      model->position,
                                                      glm::vec3(-29.573, model->position.y, -127.344),
                                                      glm::vec3(15.7186, model->position.y, -131.13),
                                                      glm::vec3(17.6656, model->position.y, -107.093),
                                                      glm::vec3(5, model->position.y, -100),
                                              }, glm::vec3(model->rotation.x, model->rotation.y, 3 * ppgso::PI / 2),
                                              glm::vec3(model->rotation.x, model->rotation.y, ppgso::PI / 2),
                                              250);

                }
            } else if (currScene == "disco") {
                scene.camera->setToStationary(glm::vec3(-22.3104, -10, 17.9578), glm::vec3(-21.7954, -10.0175, 17.1008));
            }
        }
        if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
            if(currScene == "alley") {
            scene.camera->transitionTo(scene.camera->position, scene.camera->lookAtPos, glm::vec3(scene.camera->position.x, scene.camera->position.y, scene.camera->position.z - 200 ), glm::vec3(scene.camera->position.x, scene.camera->position.y, scene.camera->position.z - 500 ), 450);
            } else if(currScene == "disco"){
                scene.camera->transitionTo(scene.camera->position, scene.camera->lookAtPos,glm::vec3(7.24375, scene.camera->position.y, 16.3793),glm::vec3(7.9354, scene.camera->position.y,15.6877), 800);
            }
        }
        if (key == GLFW_KEY_6 && action == GLFW_PRESS) {
            if(currScene == "alley") {
                scene.camera->setToStationary(glm::vec3(33.7666, 2, -275.592), glm::vec3(33.1623, 1.80919, -274.819) );
            } else if(currScene == "disco"){
                scene.camera->setToStationary(glm::vec3(24.3108, -10, 18.1034),glm::vec3(23.7027, -10.1564, 17.3251));
                int x = 0;
                Model *model = nullptr;
                for (auto it = scene.objects->begin(); it != scene.objects->end(); ++it) {
                    if (x == 3) {
                        model = dynamic_cast<Model *>(it->get());
                        break;
                    }
                    x++;
                }
                if (model != nullptr) {
                    model->transitionTo( glm::vec3(-23.4321, model->position.y,-3.19529), model->rotation, glm::vec3(12.7645, model->position.y, 4.53337), model->rotation, 600);
                }
            }
        }
        if (key == GLFW_KEY_7 && action == GLFW_PRESS) {
            if(currScene == "alley") {
                scene.camera->transitionToBezier(

                        {
                                {1.80677,  -10, -18.3552},
                                {26.5264,  -10, -95.1943},
                                {-14.6378, -10, -207.106},
                                {4.31743,  -16, -309.589}
                        }, glm::vec3(4.3, -16.0523, -300), glm::vec3(4.3, -16.0523, -310.587), 450
                );
            } else if(currScene == "disco"){
                int x = 0;
                Drip *drip = nullptr;
                for (auto it = scene.objects->begin(); it != scene.objects->end(); ++it) {
                    if (x == 23) {
                        drip = dynamic_cast<Drip *>(it->get());
                        break;
                    }
                    x++;
                }
                if (drip != nullptr) {
                    drip->makeItMove();
                }
            }
        }

        if (key == GLFW_KEY_8 && action == GLFW_PRESS) {
            if(currScene == "alley") {
                scene.camera->setToStationary(glm::vec3(6.79578, 2, -305.328),glm::vec3(6.71745, 2.43837, -306.223));
            } else if(currScene == "disco"){
                int x = 0;
                Model *model = nullptr;
                for (auto it = scene.objects->begin(); it != scene.objects->end(); ++it) {
                    if (x == 3) {
                        model = dynamic_cast<Model *>(it->get());
                        break;
                    }
                    x++;
                }
                if (model != nullptr) {
                    model->transitionToBezier(
                            {
                                glm::vec3(model->position.x, model->position.y,model->position.z),
                                glm::vec3(12.5376, model->position.y, -6.0998),
                                glm::vec3(22.1044, model->position.y, -6.47918),
                                glm::vec3(22.1321, model->position.y, 0.5),
                            },
                            model->rotation, glm::vec3(model->rotation.x,model->rotation.y,model->rotation.z - ppgso::PI/2), 600);
                }
                //--------------------
                x = 0;
                model = nullptr;
                for (auto it = scene.objects->begin(); it != scene.objects->end(); ++it) {
                    if (x == 4) {
                        model = dynamic_cast<Model *>(it->get());
                        break;
                    }
                    x++;
                }
                if (model != nullptr) {
                    model->transitionTo(
                        model->position,
                        model->rotation,
                        model->position,
                        glm::vec3(model->rotation.x,model->rotation.y,model->rotation.z - ppgso::PI/2),
                        300);
                }

            }
        }
        if (key == GLFW_KEY_9 && action == GLFW_PRESS) {
            if(currScene == "alley") {
                scene.camera->transitionTo(glm::vec3(6.79578, 2, -305.328),glm::vec3(6.71745, 2.43837, -306.223),glm::vec3(-46.0399, -4, -317.23), glm::vec3(-46.8055, -4.0349, -317.872 ), 200);
            } else if(currScene == "disco"){
                scene.camera->setToStationary(glm::vec3(5.02367, -10, 3.60963), glm::vec3(6.02123, -10.0698, 3.60963));
            }
        }
        if (key == GLFW_KEY_0 && action == GLFW_PRESS) {
            if(currScene == "alley") {
                scene.camera->transitionTo(glm::vec3(-46.0399, -4, -317.23), glm::vec3(-46.8055, -4.0349, -317.872 ),glm::vec3(-73.1067, -4, -323.819), glm::vec3(-74.0272, -4, -324.209 ), 150);
            } else if(currScene == "disco"){
                int x = 0;
                Model* model = nullptr;
                for (auto it = scene.objects->begin(); it != scene.objects->end(); ++it) {
                    if (x == 4) {
                        model = dynamic_cast<Model *>(it->get());
                        break;
                    }
                    x++;
                }
                if (model != nullptr) {
                    model->transitionTo(
                            model->position,
                            model->rotation,
                            model->position,
                            glm::vec3(model->rotation.x + ppgso::PI/2,model->rotation.y,model->rotation.z),
                            300);
                }
            }
        }
        if (key == GLFW_KEY_MINUS && action == GLFW_PRESS) {
            if(currScene == "alley") {

            } else if(currScene == "disco"){
                scene.camera->transitionTo(glm::vec3(21.8722, 8, 15.9886),glm::vec3(21.8722, 7.00015, 16.0061),glm::vec3(21.8722, -16, 15.9886),glm::vec3(21.8725, -16.9998, 16.0061),1000);
            }
        }

        if (key == GLFW_KEY_W && (action == GLFW_PRESS || GLFW_REPEAT) && scene.camera->mode == WASD){
            scene.camera->moveForward();
        }
        if (key == GLFW_KEY_S &&  (action == GLFW_PRESS || GLFW_REPEAT) && scene.camera->mode == WASD){
            scene.camera->moveBack();
        }
        if (key == GLFW_KEY_A &&  (action == GLFW_PRESS || GLFW_REPEAT) && scene.camera->mode == WASD){
            scene.camera->moveLeft();
        }
        if (key == GLFW_KEY_D &&  (action == GLFW_PRESS || GLFW_REPEAT) && scene.camera->mode == WASD){
            scene.camera->moveRight();
        }
        if (key == GLFW_KEY_SPACE &&  (action == GLFW_PRESS || GLFW_REPEAT) && scene.camera->mode == WASD){
            scene.camera->moveUp();
        }
        if (key == GLFW_KEY_LEFT_SHIFT &&  (action == GLFW_PRESS || GLFW_REPEAT) && scene.camera->mode == WASD){
            scene.camera->moveDown();
        }
        if (key == GLFW_KEY_G &&  (action == GLFW_PRESS || GLFW_REPEAT)){
            auto drip = std::make_unique<Drip>(true);
            drip->position = {5,0,-70};
            scene.objects->push_back(move(drip));
        }
    }

    /*!
   * Window update implementation that will be called automatically from pollEvents
   */
    void onIdle() override {
        // Track time
        static auto time = (float) glfwGetTime();

        // Compute time delta
        float dt = animate ? (float) glfwGetTime() - time : 0;

        time = (float) glfwGetTime();

        // Set gray background
        glClearColor(.5f, .5f, .5f, 0);
        // Clear depth and color buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double xtemp = 0;
        double ytemp = 0;

        double* xpos = &xtemp;
        double* ypos = &ytemp;
        glfwGetCursorPos(window, xpos, ypos);
        scene.camera->mouseUpdate(glm::vec2(*xpos,*ypos));


        if (lightTimer){
            elapsedTime += dt;
            if(elapsedTime > .6){
                elapsedTime = 0;
                if(currScene == "disco"){
                    LightSource* model = nullptr;
                    LightSource* pointLight = nullptr;
                    LightSource* spotLight = nullptr;
                    glm::vec3 tempColor = {0,0,0};
                    int x = 0;
                    int y = 0;
                    for (auto it = scene.lights->begin(); it != scene.lights->end(); ++it) {
                        pointLight = dynamic_cast<LightSource*>(it->get());
                        ++it;
                        spotLight = dynamic_cast<LightSource*>(it->get());

                        if (spotLight != nullptr || pointLight != nullptr){
                            tempColor = spotLight->randomColor();

                            spotLight->setColor(tempColor);
                            pointLight->setColor(tempColor);
                            y = 0;
                            for (auto it_o = scene.objects->begin(); it_o != scene.objects->end(); ++it_o) {
                                if(y == (x / 2) ){
                                    model = dynamic_cast<LightSource*>(it_o->get());
                                    model->color = tempColor;
                                }
                                y++;
                            }

                        }
                        else{
                            std::cout << "Light pointer NULL" << std::endl;
                            exit(5);
                        }
                        x += 2;
                    }

                }
            }
        }


        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

//        glEnable(GL_CULL_FACE);
//        glFrontFace(GL_CCW);
//        glCullFace(GL_BACK);
        glViewport(0, 0, SIZE, SIZE/4*3);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        glClearColor(.5f, .5f, .5f, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // Update and render all objects
        scene.update(dt);
        scene.render();

        resetViewport();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClearColor(.5f, .5f, .5f, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDisable(GL_DEPTH_TEST);
        shader->use();

        //scene.render();
        glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
        glClearColor(.5f, .5f, .5f, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(quadVAO);
        glDisable(GL_DEPTH_TEST);
        glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
};

int main() {
    // Initialize our window
    SceneWindow window;

    // Main execution loop
    while (window.pollEvents()) {}

    return EXIT_SUCCESS;
};

#endif
