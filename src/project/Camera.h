#pragma once
#include <memory>

#include <glm/glm.hpp>
#include <ppgso/ppgso.h>

/*!
 * Simple camera object that keeps track of viewMatrix and projectionMatrix
 * the projectionMatrix is by default constructed as perspective projection
 * the viewMatrix is generated from up, position and back vectors on update
 */

enum CAM_MODE{
    WASD,
    TRANSITIONING,
    STATIONARY,
    BEZIER
};


class Camera {
public:
    glm::vec3 up{.0f,1.0f,.0f};
    glm::vec3 position{.0f,.0f,.0f};
    glm::vec3 back{.0f,.0f,.0f};
    glm::vec3 lookAtPos{-5.0f,-10.0f,4.0f};
    glm::vec3 lookAtVec{.0f,.0f,-1.0f};

    float yaw = -90.0f;
    float pitch = 0.0f;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    CAM_MODE mode = WASD;

    // Transition stuff
    float currentStep;
    float steps;
    glm::vec3 startPosition;
    glm::vec3 startLookAt;
    glm::vec3 endPosition;
    glm::vec3 endLookAt;

    std::vector<glm::vec3> points;


    /*!
     * Create new Camera that will generate viewMatrix and projectionMatrix based on its position, up and back vectors
     * @param fow - Field of view in degrees
     * @param ratio - Viewport screen ratio (usually width/height of the render window)
     * @param near - Distance to the near frustum plane
     * @param far - Distance to the far frustum plane
     */
    Camera(float fow = 45.0f, float ratio = 1.0f, float near = 0.1f, float far = 10.0f);

    /*!
     * Update Camera viewMatrix based on up, position and back vectors
     */
    void update();

    /*!
     * Get direction vector in world coordinates through camera projection plane
     * @param u - camera projection plane horizontal coordinate [-1,1]
     * @param v - camera projection plane vertical coordinate [-1,1]
     * @return Normalized vector from camera position to position on the camera projection plane
     */
    //glm::vec3 cast(double u, double v);
    void moveForward();
    void moveBack();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void mouseUpdate(const glm::vec2& newMousePosition);
    void transitionTo(glm::vec3 startPosition, glm::vec3 startLookAt, glm::vec3 endPosition, glm::vec3 endLookAt, float numberOfSteps);
    void setToStationary(glm::vec3 setToPosition, glm::vec3 setToLookAt);
    void setToWASD(glm::vec3 setToPosition, glm::vec3 setToLookAt);

    float binomialCoefficient(int n, int i);
    glm::vec3 bezierCurve(const std::vector<glm::vec3>& points, float t);
    void transitionToBezier(const std::vector<glm::vec3>& points, glm::vec3 startLookAt, glm::vec3 endLookAt, float numberOfSteps);



};
