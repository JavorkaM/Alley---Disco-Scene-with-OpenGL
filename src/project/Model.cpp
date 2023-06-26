#include "Model.h"
#include "Scene.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

#include <shaders/phong_vert_glsl_glsl.h>
#include <shaders/phong_frag_glsl_glsl.h>

// shared resources
Model::Model(const std::string& modelName, const std::string& textureName) {
    // Initialize static resources if needed
    if (!shader) shader = std::make_unique<ppgso::Shader>(phong_vert_glsl_glsl, phong_frag_glsl_glsl);
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>(modelName);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP(textureName));
}

bool Model::update(Scene &scene, float dt) {
    if(transitioning && currentStep < steps){
        if(bezier){
            position = bezierCurve(points,  currentStep / steps);
            rotation = glm::lerp(startRotation, endRotation, currentStep / steps);
            currentStep++;
        }
        else {
            position = glm::lerp(startPosition, endPosition, currentStep / steps);
            rotation = glm::lerp(startRotation, endRotation, currentStep / steps);
            currentStep++;
        }
    }
    generateModelMatrix();
    return true;
}

void Model::render(Scene &scene) {
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

    //std::cout << scene.lights->size() << std::endl;

    shader->setUniform("materialShininess", this->materialProperties.x);
    shader->setUniform("materialDiffuse", this->materialProperties.y);
    shader->setUniform("materialSpecular", this->materialProperties.z);

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

void Model::transitionTo(glm::vec3 startPosition, glm::vec3 startLookAt, glm::vec3 endPosition, glm::vec3 endLookAt,
                         float numberOfSteps) {
    transitioning = true;

    steps = numberOfSteps;
    currentStep = 0;

    this->startPosition = startPosition;
    this->startRotation = startLookAt;
    this->endPosition = endPosition;
    this->endRotation = endLookAt;
}

void Model::transitionToBezier(const std::vector<glm::vec3>& points, glm::vec3 startLookAt, glm::vec3 endLookAt, float numberOfSteps) {
    transitioning = true;
    bezier = true;

    this->points = points;

    this->startRotation = startLookAt;
    this->endRotation = endLookAt;

    steps = numberOfSteps;
    currentStep = 0;

}


glm::vec3 Model::bezierCurve(const std::vector<glm::vec3>& points, float t)
{
    std::vector<double> coefficients;
    for (int i = 0; i < points.size(); i++) {
        coefficients.push_back(binomialCoefficient(points.size() - 1, i));
    }

    double x = 0, z = 0;
    for (int j = 0; j < points.size(); j++) {
        x += coefficients[j] * pow(1 - t, points.size() - 1 - j) * pow(t, j) * points[j].x;
        z += coefficients[j] * pow(1 - t, points.size() - 1 - j) * pow(t, j) * points[j].z;
    }
    return {x,position.y,z};
}


float Model::binomialCoefficient(int n, int k) {
    int result = 1;
    if (k > n - k) k = n - k;
    for (int i = 0; i < k; ++i) {
        result *= (n - i);
        result /= (i + 1);
    }
    return result;
}
