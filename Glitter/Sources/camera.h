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
// Bit-twiddling!!!
enum direction_t {
    NONE       = 0x00,
    FORWARDS   = 0x01,
    BACKWARDS  = 0x02,
    LEFT       = 0x04,
    RIGHT      = 0x08,
    UP         = 0x10,
    DOWN       = 0x20,
    ROLL_LEFT  = 0x40,
    ROLL_RIGHT = 0x80
};

// Viewport projection types
enum view_t {
    ORTHOGRAPHIC,
    PERSPECTIVE
};

//Type-safe default constants
const float PITCH =   0.0f;
const float ROLL  =   0.0f;
const float YAW   = -90.0f;
const float SPEED =   2.5f;
const float SENSE =   0.5f;
const float ZOOM  =  45.0f;

const float MIN_ZOOM =  1.0f;
const float MAX_ZOOM = 45.0f;


class Camera
{
public:
    Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up  = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = YAW, float pitch = PITCH) : roll(ROLL),
                                                   speed(SPEED),
                                                   sensitivity(SENSE),
                                                   zoom(ZOOM),
                                                   front(glm::vec3(0.0f, 0.0f, 1.0f))
    {
        this->pos       = pos;
        this->global_up = up;
        this->yaw       = yaw;
        this->pitch     = pitch;

        // Properly update everything
        update_vectors();
    }

    glm::mat4 get_view(view_t projection);
    glm::mat4 get_view()
    {
        return this->get_view(this->view);
    }



    void set_fov(float field)
    {
        this->fov = field;
    }

    void set_render(view_t type)
    {
        this->view = type;
    }
    void update_window(int w, int h)
    {
        this->width  = (float) w;
        this->height = (float) h;
    }

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
    float fov;

    view_t view;

    // Locational attributes
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 local_up;
    glm::vec3 local_right;
    glm::vec3 global_up;

    // Window attributes
    float width;
    float height;

    void update_vectors(void);
};

