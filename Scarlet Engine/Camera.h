#ifndef __Camera
#define __Camera

#include "Component.h"
#include "Input.h"
#include "Debug.h"
#include "Time.h"
#include "CameraMatrix.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>

class Camera : public Component {
public:
    enum Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float SPEED = 2.5f;
    const float SENSITIVITY = 0.1f;
    const float ZOOM = 45.0f;

    glm::vec3* Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    float Aspect;
    float Near;
    float Far;
    bool MainCamera = false;

    Camera(glm::vec3* position, glm::vec3 up, float yaw, float pitch, glm::vec3 front, float speed, float Sensitivity, float zoom, float aspect, float near, float far, bool main_cam);
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();

    void ProcessKeyboard(Camera_Movement direction, float deltaTime, bool isDebugMode);
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch, bool isDebugMode);
    void ProcessMouseScroll(float yoffset, bool isDebugMode);

    void Update() override;
    void Draw() override;

private:
    void updateCameraVectors();
    bool locked = true;
};

#endif