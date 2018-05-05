/**
 * Name: Riley Myers
 * File Name: camera.cpp
 * Synopsis: This file contains method defintitions for the camera class.
 *
 * TODO: accound for differend local_up vectors and add roll calculations
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

    switch (dir) {
    case FORWARDS:  pos += front * v; break;
    case BACKWARDS: pos -= front * v; break;
    case LEFT:      pos -= local_right * v; break;
    case RIGHT:     pos += local_right * v; break;
    case UP:        pos += local_up * v; break;
    case DOWN:      pos -= local_up * v; break;
    case ROLL_LEFT:
    case ROLL_RIGHT:
    default:
        //TODO - not implemented yet
        break;
    }
}

void Camera::process_mouse(float x_off, float y_off, bool lock_pitch)
{
    // Correct for sensitivity
    x_off *= sensitivity;
    y_off *= sensitivity;

    yaw   += x_off;
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
    tmp.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    tmp.y = sin(glm::radians(pitch));
    tmp.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(tmp);


    // Also re-calculate local vectors from the current facing
    local_right = glm::normalize(glm::cross(front, global_up)); 
    local_up    = glm::normalize(glm::cross(local_right, front));
}


