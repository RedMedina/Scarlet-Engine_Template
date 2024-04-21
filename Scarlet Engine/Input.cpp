#include "Input.h"

    GLFWwindow* Input::window = nullptr;
    double Input::Mouse_PosX = 0;
    double Input::Mouse_PosY = 0;
    float Input::Screen_lastX = 0;
    float Input::Screen_lastY = 0;

    bool Input::GetKeyDown(int key) {
        int state = glfwGetKey(window, key);
        return state == GLFW_PRESS;
    }

    bool Input::GetKey(int key) {
        int state = glfwGetKey(window, key);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::GetKeyUp(int key) {
        int state = glfwGetKey(window, key);
        return state == GLFW_RELEASE;
    }