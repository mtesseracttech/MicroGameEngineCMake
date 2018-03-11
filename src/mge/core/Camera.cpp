#include <iostream>

using namespace std;

#include <glm.hpp>
#include "mge/core/Camera.hpp"

Camera::Camera(std::string p_name, glm::vec3 p_position, glm::mat4 p_projection)
        : GameObject(p_name, p_position), m_projection(p_projection)
{
}

Camera::~Camera()
{
    //dtor
}

glm::mat4& Camera::getProjection()
{
    return m_projection;
}

