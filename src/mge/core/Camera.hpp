#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include "mge/core/GameObject.hpp"

/**
 * Camera is just a GameObject with an additional projection matrix.
 * The camera's own transform is used to generate a world to view matrix by taking the inverse of the camera transform
 * (see renderer).
 */
class Camera : public GameObject
{
private:
    glm::mat4 m_projection;
public:
    Camera(
            std::string p_name = "camera",
            glm::vec3 p_position = glm::vec3(0.0f, 3.0f, 5.0f),
            glm::mat4 p_projection = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 1000.0f)
    );

    virtual ~Camera();

    glm::mat4& getProjection();
};

#endif // CAMERA_H
