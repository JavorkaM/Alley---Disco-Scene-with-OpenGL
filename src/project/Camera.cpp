#include <glm/glm.hpp>

#include "Camera.h"

double lastCurPosX;
double lastCurPosY;
bool firstCurPos = true;

const float SPEED = 3.0f;
const float SENS = 1.0f;

Camera::Camera(float fow, float ratio, float near, float far) {
    float fowInRad = (ppgso::PI/180.0f) * fow;
    projectionMatrix = glm::perspective(fowInRad, ratio, near, far);
}

void Camera::update() {
    if((mode == TRANSITIONING || mode == BEZIER) && currentStep < steps){
        if(mode == BEZIER){
            position = bezierCurve(points,  currentStep / steps);
            lookAtPos = glm::lerp(startLookAt, endLookAt, currentStep / steps);
            currentStep++;
        }
        else {
            position = glm::lerp(startPosition, endPosition, currentStep / steps);
            lookAtPos = glm::lerp(startLookAt, endLookAt, currentStep / steps);
            currentStep++;
        }
    }

    viewMatrix = lookAt(position, lookAtPos, up);

    //std::cout << "Cam Position:" << position.x << " " << position.y << " " << position.z << " "  << std::endl;
    //std::cout << "Cam lookAtPos:" << lookAtPos.x << " " << lookAtPos.y << " " << lookAtPos.z << " "  << std::endl;
}

void Camera::moveForward(){
    float temp = position.y;
    position += SPEED * lookAtVec;
    position.y = temp;
    lookAtPos = position + lookAtVec;
}

void Camera::moveBack(){
    float temp = position.y;
    position -= SPEED * lookAtVec;
    position.y = temp;
    lookAtPos = position + lookAtVec;
}

void Camera::moveLeft(){
    float temp = position.y;
    glm::vec3 rotateTowards = glm::normalize(glm::cross(lookAtVec, up));
    position -= SPEED * rotateTowards;
    position.y = temp;
    lookAtPos = position + lookAtVec;
}

void Camera::moveRight(){
    float temp = position.y;
    glm::vec3 rotateTowards = glm::normalize(glm::cross(lookAtVec, up));
    position += SPEED * rotateTowards;
    position.y = temp;
    lookAtPos = position + lookAtVec;
}

void Camera::moveUp(){
    position += SPEED * up;
    lookAtPos = position + lookAtVec;
}

void Camera::moveDown(){
    position -= SPEED * up;
    lookAtPos = position + lookAtVec;
}

void Camera::mouseUpdate(const glm::vec2 &newMousePosition) {
    double xpos = newMousePosition[0];
    double ypos = newMousePosition[1];
    if(firstCurPos){
        lastCurPosX = xpos;
        lastCurPosY = ypos;
        firstCurPos = false;
        return;
    }
    if(lastCurPosX == xpos && lastCurPosY == ypos)
        return;

    float xoffset = xpos - lastCurPosX;
    float yoffset = lastCurPosY - ypos;

    xoffset *= SENS;
    yoffset *= SENS;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    front.y = glm::sin(glm::radians(pitch));
    front.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    lookAtVec = front;


    lookAtPos = position + front;

    lastCurPosX = xpos;
    lastCurPosY = ypos;
}

void Camera::transitionTo(glm::vec3 startPosition_n, glm::vec3 startLookAt_n, glm::vec3 endPosition_n, glm::vec3 endLookAt_n, float numberOfSteps) {

    mode = TRANSITIONING;

    steps = numberOfSteps;
    currentStep = 0;

    this->startPosition = startPosition_n;
    this->startLookAt = startLookAt_n;
    this->endPosition = endPosition_n;
    this->endLookAt = endLookAt_n;

}

void Camera::setToStationary(glm::vec3 setToPosition, glm::vec3 setToLookAt) {
    mode = STATIONARY;
    position = setToPosition;
    lookAtPos = setToLookAt;
}

void Camera::setToWASD(glm::vec3 setToPosition, glm::vec3 setToLookAt) {
    mode = WASD;
    position = setToPosition;
    lookAtVec = {.0f,.0f,-1.0f};
    lookAtPos = position + lookAtVec;
}


void Camera::transitionToBezier(const std::vector<glm::vec3>& points, glm::vec3 startLookAt, glm::vec3 endLookAt, float numberOfSteps) {
    mode = BEZIER;

    this->points = points;

    this->startLookAt = startLookAt;
    this->endLookAt = endLookAt;

    steps = numberOfSteps;
    currentStep = 0;

}


glm::vec3 Camera::bezierCurve(const std::vector<glm::vec3>& points, float t)
{
    std::vector<double> coefficients;
    for (int i = 0; i < points.size(); i++) {
        coefficients.push_back(binomialCoefficient(points.size() - 1, i));
    }

    double x = 0,y = 0, z = 0;
    for (int j = 0; j < points.size(); j++) {
        x += coefficients[j] * pow(1 - t, points.size() - 1 - j) * pow(t, j) * points[j].x;
        y += coefficients[j] * pow(1 - t, points.size() - 1 - j) * pow(t, j) * points[j].y;
        z += coefficients[j] * pow(1 - t, points.size() - 1 - j) * pow(t, j) * points[j].z;
    }
    return {x,y,z};
}


float Camera::binomialCoefficient(int n, int k) {
    int result = 1;
    if (k > n - k) k = n - k;
    for (int i = 0; i < k; ++i) {
        result *= (n - i);
        result /= (i + 1);
    }
    return result;
}

