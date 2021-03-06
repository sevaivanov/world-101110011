/*
 * @file
 * @author Vsevolod (Seva) Ivanov
*/

#pragma once

#include <stdio.h>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//! Camera class for the Homogeneous coordinates system
class Camera
{
    public:
        Camera();
        ~Camera();

        //! View matrice to analyse camera in real-time
        glm::mat4 getView() const;
        glm::vec3 getEye() const;
        glm::vec3 getAt() const;

        void setEye(glm::vec3 _eye);
        void setAt(glm::vec3 _at);

        void moveUp();
        void moveRight();
        void moveDown();
        void moveLeft();

        void moveForward();
        void moveBackward();

        void printView() const;
        void printEyePos() const;

    private:
        //! Camera position.
        glm::vec3 eye;
        //! Point being observed. 
        glm::vec3 at;
        //! Up direction of camera.
        glm::vec3 up;
        //! Motions speed
        GLfloat speed;
};
