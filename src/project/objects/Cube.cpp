#include "Cube.h"
#include "src/project/Scene.h"

#include "cmake-build-debug/shaders/color_vert_glsl.h"
#include "cmake-build-debug/shaders/color_frag_glsl.h"

#include "cmake-build-debug/shaders/diffuse_vert_glsl.h"
#include "cmake-build-debug/shaders/diffuse_frag_glsl.h"


#include <shaders/phong_vert_glsl_glsl.h>
#include <shaders/phong_frag_glsl_glsl.h>

// shared resources
std::unique_ptr<ppgso::Mesh> Cube::mesh;
std::unique_ptr<ppgso::Shader> Cube::shader;
std::unique_ptr<ppgso::Texture> Cube::texture;

Cube::Cube(int r, int g, int b) {
    color = {r, g, b};

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("cube.obj");
}

Cube::Cube(int r, int g, int b, std::string textureName) {
    color = {r, g, b};

    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(phong_vert_glsl_glsl, phong_frag_glsl_glsl);
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("cube.obj");
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP(textureName));
}

bool Cube::update(Scene &scene, float dt) {
    generateModelMatrix();
    return true;
}

void Cube::render(Scene &scene) {
    shader->use();

    // Set up light
    shader->setUniform("LightDirection", scene.lightDirection);

    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("ViewPosition", scene.camera->position);

    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);

    shader->setUniform("Lights_count", (float) scene.lights->size());

    shader->setUniform("materialShininess", (float) this->materialProperties.x);
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
    }
    mesh->render();
}

void Cube::onClick(Scene &scene) {
    std::cout << "Player has been clicked!" << std::endl;
}
