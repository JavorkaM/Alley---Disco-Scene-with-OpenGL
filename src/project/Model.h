#pragma once
#include <ppgso/ppgso.h>

#include "Object.h"

/*!
 * Simple object representing the player
 * Reads keyboard status and manipulates its own position
 * On Update checks collisions with Asteroid objects in the scene
 */
class Model : public Object {
private:
    bool transitioning = false;
    bool bezier = false;
    glm::vec3 startPosition;
    glm::vec3 startRotation;
    glm::vec3 endPosition;
    glm::vec3 endRotation;
    float steps;
    float currentStep = 0;

    std::vector<glm::vec3> points;

protected:
    // Static resources (Shared between instances)
    std::unique_ptr<ppgso::Mesh> mesh;
    std::unique_ptr<ppgso::Shader> shader;
    std::unique_ptr<ppgso::Texture> texture;

    glm::vec3 color = {0, 0, 1};

public:
    /*!
     * Create a new player
     */
    Model(const std::string& modelName, const std::string& textureName);

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

    void transitionTo(glm::vec3 startPosition, glm::vec3 startLookAt, glm::vec3 endPosition, glm::vec3 endLookAt, float numberOfSteps);
    float binomialCoefficient(int n, int i);
    glm::vec3 bezierCurve(const std::vector<glm::vec3>& points, float t);
    void transitionToBezier(const std::vector<glm::vec3>& points, glm::vec3 startLookAt, glm::vec3 endLookAt, float numberOfSteps);
};

