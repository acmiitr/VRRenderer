#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
#include "../include/glm/gtx/rotate_vector.hpp"
#include "../include/glm/gtx/vector_angle.hpp"
#include "../headers/shaderClass.h"

class Camera{
    public:
        glm::vec3 camPosition;
        glm::vec3 orientation = glm::vec3 (0.0f, 0.0f, -3.0f);  // front
        glm::vec3 up = glm::vec3 (0.0f, 1.0f, 0.0f);
        glm::mat4 cameraMatrix = glm::mat4(1.0f);
        float fov;

        int width, height;
        float lastX, lastY;
        float speed = 0.05f;
        float sensitivity = 100.0f;
        bool firstClick = true;

        Camera(int width, int height, glm::vec3 position);

        void UpdateMatrix(float FOV, float nearPlane, float farPlane);
        void Matrix(Shader& shader, const char* uniform);
        void KeyInputs(GLFWwindow* window);
        void MouseInputs(GLFWwindow* window);
        static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};
#endif //CAMERA_H
