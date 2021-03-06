/*
 * @file
 * @author Vsevolod (Seva) Ivanov
*/

#pragma once

//! Abstract class made to facilitate & uniformalize the integration of Meshes
class Mesh
{
    public:
        virtual GLenum getRenderMode() const = 0;

        virtual void setRenderMode(const GLenum renderMode) = 0;

        virtual void render(const Window* window,
                            const Camera* camera,
                            const glm::mat4 view,
                            const glm::mat4 projection) = 0;

        virtual void rotate(const glm::vec3 spin) = 0;
};
