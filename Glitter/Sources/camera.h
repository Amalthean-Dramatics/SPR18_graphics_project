/**
 * Name: Riley Myers
 * File Name: camera.h
 * Synopsis: This file contains a class declaration for a camera class.
 */

#pragma once
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#include <fstream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> 
// glm::translate, glm::rotate, glm::scale, glm::perspective

// Oooohhh, input-method independent directions!
enum direction_t {
    FORWARDS,
    BACKWARDS,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    ROLL_LEFT,
    ROLL_RIGHT
};

//Type-safe default constants
const float PITCH =   0.0f;
const float ROLL  =   0.0f;
const float YAW   = -90.0f;
const float SPEED =   2.5f;
const float SENSE =   0.1f;
const float ZOOM  =  45.0f;

const float MIN_ZOOM =  1.0f;
const float MAX_ZOOM = 45.0f;


class Camera
{
public:
    Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up  = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = YAW, float pitch = PITCH) : roll(PITCH),
                                                   speed(SPEED),
                                                   zoom(ZOOM),
                                                   sensitivity(SENSE),
                                                   front(glm::vec3(0.0f, 0.0f, 0.0f))
    {
        //TODO
    }

    Camera(float pos_x, float pos_y, float pos_z,
           float up_x,  float up_y,  float up_z,
           float yaw,   float pitch)  :  roll(PITCH),
                                         speed(SPEED),
                                         zoom(ZOOM),
                                         sensitivity(SENSE),
                                         front(glm::vec3(0.0f, 0.0f, 0.0f))
    {
        //TODO
    }

    glm::mat4 get_view(void);

    void process_kbd(direction_t dir, float dt);
    void process_mouse(float x_off, float y_off, bool lock_pitch=true);
    void process_scroll(float y_off);

private:
    // Camera Euler Angles
    float pitch;
    float roll;
    float yaw;

    // Camera options
    float speed;
    float rot;
    float sensitivity;
    float zoom;

    // Locational attributes
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 local_up;
    glm::vec3 local_right;
    glm::vec3 global_up;

    void update_vectors(void);
};

