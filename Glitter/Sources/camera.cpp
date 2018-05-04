/**
 * Name: Riley Myers
 * File Name: camera.cpp
 * Synopsis: This file contains method defintitions for the camera class.
 */

#include <algorithm>


#include "camera.h"
#include "warning.h"






glm::mat4 Camera::get_view(void)
{
    return glm::lookAt(pos, pos + front, local_up);
}

//TODO - Have different speeds for different axes?
void Camera::process_kbd(direction_t dir, float dt)
{
    float v = speed * dt; // Linear velocity
    float w = rot * dt;   // Rotational velocity

    switch (direction) {
    case FORWARD:
        pos += front * v;
    case BACKWARD:
        pos -= front * v;
    case LEFT:
        pos -= local_right * v;
    case RIGHT:
        pos += local_right * v;
    case UP:
        pos += local_up * v;
    case DOWN:
        pos -= local_up * v;
    case ROLL_LEFT:
    case ROLL_RIGHT:
    default:
        //TODO - not implemented yet
    }
}

void Camera::process_mouse(float x_off, float y_off, bool lock_pitch=true)
{
    // Correct for sensitivity
    x_off *= sensitivity;
    y_off *= sensitivity;

    yaw += x_off;
    pitch += y_off;

    // We don't all have necks made of rubber!
    if (lock_pitch) {
        pitch = std::max(std::min(pitch, 89.0f), -89.0f);
    }

    update_vectors();
}

void Camera::process_scroll(float y_off)
{
    zoom = std::max(std::min(zoom - y_off, MAX_ZOOM), MIN_ZOOM);
}


/******** Private members **********/
/******************************************************************************
    update_vectors
    purpose: updates the internal vectors that the camera uses to keep track of
        its position
    --------------------------------------------------------------------------
******************************************************************************/
void Camera::update_vectors(void)
{
    glm::vec3 tmp;
    tmp.x = cos(glm::radians(yaw));
    //TODO!!!
}


