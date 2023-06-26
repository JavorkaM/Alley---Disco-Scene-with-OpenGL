#include "Duck.h"
#include "src/project/Scene.h"

#include "cmake-build-debug/shaders/diffuse_vert_glsl.h"
#include "cmake-build-debug/shaders/diffuse_frag_glsl.h"

// shared resources
std::unique_ptr<ppgso::Mesh> Duck::mesh;
std::unique_ptr<ppgso::Texture> Duck::texture;
std::unique_ptr<ppgso::Shader> Duck::shader;

Duck::Duck() {
    // Scale the default model
    //scale *= 3.0f;
    //rotation.x = 180;
    //rotation.y = 90;

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("rubberDuck.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("rubberDuck.obj");
}

bool Duck::update(Scene &scene, float dt) {
    moveDelay += dt;


    /*if(scene.keyboard[GLFW_KEY_X] && moveDelay > moveRate) {
        rotation.x += 90;
        moveDelay = 0;
    }
    if(scene.keyboard[GLFW_KEY_Y] && moveDelay > moveRate) {
        rotation.y += 90;
        moveDelay = 0;
    }
    if(scene.keyboard[GLFW_KEY_Z] && moveDelay > moveRate) {
        rotation.z += 90;
        moveDelay = 0;
    }*/

    // Keyboard controls
    /*if(scene.keyboard[GLFW_KEY_LEFT]) {
        position.x += 10 * dt;
        rotation.z = -ppgso::PI/4.0f;
    } else if(scene.keyboard[GLFW_KEY_RIGHT]) {
        position.x -= 10 * dt;
        rotation.z = ppgso::PI/4.0f;
    } else {
        rotation.z = 0;
    }*/

    generateModelMatrix();
    return true;
}

void Duck::render(Scene &scene) {
    shader->use();

    // Set up light
    shader->setUniform("LightDirection", scene.lightDirection);

    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    mesh->render();
}

void Duck::onClick(Scene &scene) {
    std::cout << "Duck has been clicked!" << std::endl;
}
