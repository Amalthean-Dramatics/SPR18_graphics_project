/**
 * Name: Riley Myers
 * File Name: camera.cpp
 * Synopsis: This file contains method defintitions for the camera class.
 *
 * TODO: account for different local_up vectors and add roll calculations
 */

#include <algorithm>


#include "camera.h"
#include "warning.h"

#ifndef NDEBUG
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#endif





glm::mat4 Camera::get_view(view_t projection)
{
    // Create a matrix to represent our current position
    glm::mat4 loc = glm::translate(glm::mat4(1.0f), pos);
    glm::mat4 project;

    // Then create a projection matrix
    if (projection == ORTHOGRAPHIC) {
        //Create an orthographic matrix ...
        project = glm::ortho(0.0f,     // left edge x-coord
                             width,    // right edge x-coord
                             0.0f,     // bottom edge y-coord
                             height  , // top edge y-coord
                             0.01f,    // Location of close plane
                             100.0f); // Location of far plane
    } else {
        // ... or create a perspective matrix
        project = glm::perspective(glm::radians(fov), // field of view
                                   width / height,    // aspect ratio
                                   0.01f,             // Location of close plane
                                   1000.0f);          // Location of far plane
    }

#ifndef NDEBUG
    std::cout << BBLUE << "project is :" << ENDCOL << glm::to_string(project) << std::endl;
    std::cout << BBLUE << "position vector is :" << ENDCOL << glm::to_string(pos) << std::endl;
    std::cout << BBLUE << "Front vector is :" << ENDCOL << glm::to_string(front) << std::endl;
    std::cout << BBLUE << "up vector is :" << ENDCOL << glm::to_string(local_up) << std::endl;
#endif
    // Return the projection * facing * position
    return project * glm::lookAt(pos, pos + front, local_up); //* loc;
}

//TODO - Have different speeds for different axes?
void Camera::process_kbd(direction_t dir, float dt)
{
    float v = speed * dt; // Linear velocity
    float w = rot * dt;   // Rotational velocity

    if (dir & FORWARDS)  pos += front * v;
    if (dir & BACKWARDS) pos -= front * v;
    if (dir & LEFT)      pos -= local_right * v;
    if (dir & RIGHT)     pos += local_right * v;
    if (dir & UP)        pos += local_up * v;
    if (dir & DOWN)      pos -= local_up * v;
    if (dir & ROLL_LEFT)
        w = w; //TODO - not implemented yet
    if (dir & ROLL_RIGHT)
        w = w;//TODO - not implemented yet
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


