#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM header file
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

enum CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;

    // euler Angles
    float yaw;
    float pitch;

    float movement_speed;
    float mouse_sensitivity;
    float zoom;

    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    glm::mat4 get_view_matrix();
    void process_keyboard(CameraMovement direction, float delta_time);
    void process_mouse_movement(float xoffset, float yoffset, GLboolean constrain_pitch = true);
    void process_mouse_scroll(float yoffset);
private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void update_camera_vectors(); 
};