#include "Camera.h"

Camera::Camera(glm::vec3* position, glm::vec3 up, float yaw, float pitch, glm::vec3 front, float speed, float Sensitivity, float zoom, float aspect, float near, float far, bool main_cam)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    Front = front;
    MovementSpeed = speed;
    MouseSensitivity = Sensitivity;
    Zoom = zoom;
    Aspect = aspect;
    Near = near;
    Far = far;
    MainCamera = main_cam;
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(*Position, *Position + Front, Up);
}

glm::mat4 Camera::GetProjectionMatrix()
{
    //FOV, Aspect = 4.0f / 3.0f, Near = 0.1f, Far = 2000.0f
    return glm::perspective(glm::radians(Zoom), Aspect, Near, Far);
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));  
    Up = glm::normalize(glm::cross(Right, Front));
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime, bool isDebugMode)
{
    if (!isDebugMode)
        return;

    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        *Position += Front * velocity;
    if (direction == BACKWARD)
        *Position -= Front * velocity;
    if (direction == LEFT)
        *Position -= Right * velocity;
    if (direction == RIGHT)
        *Position += Right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch, bool isDebugMode)
{
    if (!isDebugMode)
        return;

    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset, bool isDebugMode)
{
    if (!isDebugMode)
        return;

    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

void Camera::Update()
{
    //---
}

void Camera::Draw()
{
    if (MainCamera)
    {
        if(Input::GetKeyDown(InputKey::W))
        {
            ProcessKeyboard(FORWARD, Time::deltatime, Debug::GetDebugMode());
        }
        if (Input::GetKeyDown(InputKey::A))
        {
            ProcessKeyboard(LEFT, Time::deltatime, Debug::GetDebugMode());
        }
        if (Input::GetKeyDown(InputKey::S))
        {
            ProcessKeyboard(BACKWARD, Time::deltatime, Debug::GetDebugMode());
        }
        if (Input::GetKeyDown(InputKey::D))
        {
            ProcessKeyboard(RIGHT, Time::deltatime, Debug::GetDebugMode());
        }
        if(Input::GetKeyDown(InputKey::Enter))
        {
            if(locked && Debug::GetDebugMode())
            {
                glfwSetInputMode(Input::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                glfwSetCursorPos(Input::window, 1300 / 2, 950 / 2);
                locked = false;
            }
        }
        if(Input::GetKeyDown(InputKey::End))
        {
            if (!locked && Debug::GetDebugMode())
            {
                glfwSetInputMode(Input::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                locked = true;
            }
        }


        //Mouse process
        float xpos = static_cast<float>(Input::Mouse_PosX);
        float ypos = static_cast<float>(Input::Mouse_PosY);

        float xoffset = xpos - Input::Screen_lastX;
        float yoffset = Input::Screen_lastY - ypos;

        Input::Screen_lastX = xpos;
        Input::Screen_lastY = ypos;

        if(!locked && Debug::GetDebugMode())
        {
            ProcessMouseMovement(xoffset, yoffset, true, Debug::GetDebugMode());
        }

        CameraMatrix::ViewMatrix = GetViewMatrix();
        CameraMatrix::ProyectionMatrix = GetProjectionMatrix();
        CameraMatrix::CameraPosition = Position;
    }
}