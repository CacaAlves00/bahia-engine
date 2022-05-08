#include "../include/Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : front(glm::vec3(0.0f, 0.0f, -1.0f)), movement_speed(SPEED), mouse_sensitivity(SENSITIVITY),
      zoom(ZOOM), position(position), world_up(up), yaw(yay), pitch(pitch)
{
    update_camera_vectors();
}

glm::mat4 Camera::get_view_matrix()
{
    return glm::lookAt(position, position + front, up);
}

void Camera::process_keyboard(CameraMovement direction, float delta_time)
{
    float velocity = movement_speed * delta_time;
    if (direction == FORWARD)
        position += front * velocity;
    if (direction == BACKWARD)
        position -= front * velocity;
    if (direction == LEFT)
        position -= right * velocity;
    if (direction == RIGHT)
        position += right * velocity;
}

void Camera::process_mouse_movement(float xoffset, float yoffset, GLboolean constrain_pitch)
{
    xoffset *= mouse_sensitivity;
    yoffset *= mouse_sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::process_mouse_scroll(float yoffset)
{
    zoom -= (float)yoffset;
    if (zoom < 1.0f)
        zoom = 1.0f;
    if (zoom > 45.0f)
        zoom = 45.0f;
}

void Camera::update_camera_vectors()
{
    glm::vec3 new_front_vector;
    new_front_vector.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    new_front_vector.y = sin(glm::radians(pitch));
    new_front_vector.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(new_front_vector);

    // Re-calculates the Right and Up vector
    right = glm::normalize(glm::cross(front, world_up)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up = glm::normalize(glm::cross(right, front));
}